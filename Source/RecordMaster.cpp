/// @author M. A. Serebrennikov
#include "Record.h"
#include "RecordContent.h"
#include "RecordMaster.h"
#include "Storage.h"
#include "Tools.h"
#include "sqlite3.h"
#include "TextNoteMaster.h"

#include <QDebug>
#include <QStringBuilder>

using namespace sp;

RecordMaster &RecordMaster::instance()
{
    static RecordMaster master;
    return master;
}

//------------------------------------------------------------------------------
QVector<RecordPtr> RecordMaster::get(const QString &tag, int limit, int offset)
{
    QVector<RecordPtr> result;

    sqlite3_stmt *stmt;
    defer(sqlite3_finalize(stmt));

    QString query = "SELECT `id`, `type`, `contentId`, `date` from `" % _tableName % "` "
                    "ORDER BY `date` DESC";
    sqlite3_prepare_v2(StorageI.db(), query.toUtf8().data(), -1, &stmt, NULL);

    for(;;) {
        int res = sqlite3_step (stmt);

        if (res == SQLITE_ROW) {
            auto id        = Storage::getId(stmt, 0);
            auto type      = Storage::getEnum<Record::Type>(stmt, 1);
            auto contentId = Storage::getInt(stmt, 2);
            auto date      = Storage::getDate(stmt, 3);

            RecordPtr record(new Record(*id, type, loadContent(type, contentId), date));
            result.append(record);
        } else if (res == SQLITE_DONE) {
            break;
        } else {
            qCritical() << "Error of record loading";
            break;
        }
    } // for(;;) {
    return result;
}

//------------------------------------------------------------------------------
void RecordMaster::add(const RecordPtr &record)
{
    Q_ASSERT(record->content());
    Q_ASSERT(record->content()->rowid() > 0);

    sqlite3_stmt *stmt;
    defer(sqlite3_finalize(stmt));

    QString query = "INSERT INTO `" % _tableName % "` (`id`, `type`, `contentId`, `date`) "
                        "VALUES (?1, ?2, ?3, ?4)";
    sqlite3_prepare_v2(StorageI.db(), query.toUtf8().data(), -1, &stmt, NULL);

    // TODO На момент отладки принимаются человеческое представление UUID. Потом раскоментировать
    // sqlite3_bind_blob(stmt, 1, &record->id(), sizeof(QUuid), SQLITE_STATIC);
    QByteArray buf = record->id().toByteArray();
    sqlite3_bind_blob(stmt, 1, buf.data(), buf.size(), SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, record->type());
    sqlite3_bind_int(stmt, 3, record->content()->rowid());
    sqlite3_bind_int64(stmt, 4, record->date().toMSecsSinceEpoch());

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        printf("ERROR inserting data: %s\n", sqlite3_errmsg(StorageI.db()));
        return;
    }

    emit recordCreated(record);
}

//------------------------------------------------------------------------------
void RecordMaster::remove(const RecordPtr &record)
{
}

//------------------------------------------------------------------------------
void RecordMaster::remove(const QVector<RecordPtr> &records)
{

}

//------------------------------------------------------------------------------
void RecordMaster::remove(const QVector<QUuid> &records)
{

}

//------------------------------------------------------------------------------
void RecordMaster::prepareStorage() const
{
    QString query =
            "CREATE TABLE IF NOT EXISTS `" % _tableName % "`("
                "`id` BLOB NOT NULL PRIMARY KEY"
                ",`type` INTEGER NOT NULL"
                ",`contentId` INTEGER NOT NULL"
                ",`date` INTEGER"
            ") WITHOUT ROWID;"

            "CREATE INDEX IF NOT EXISTS `index_id` ON `" % _tableName % "`(`id`);"
            "CREATE INDEX IF NOT EXISTS `index_contentId` ON `" % _tableName % "`(`contentId`);";
    StorageI.createTable(query);
}

//------------------------------------------------------------------------------
void RecordMaster::remove(Record *recordRaw)
{
    if (!recordRaw) {
        Q_ASSERT(false);
        return;
    }
    auto record = recordRaw->sharedFromThis();

    if (!record->content()->remove()) {
        return;
    }

    Q_ASSERT(record->content());
    Q_ASSERT(record->content()->rowid() > 0);

    sqlite3_stmt *stmt;
    defer(sqlite3_finalize(stmt));

    const char *query = "DELETE FROM `Records` WHERE `id`=?1";
    sqlite3_prepare_v2(StorageI.db(), query, -1, &stmt, NULL);

    // TODO На момент отладки принимаются человеческое представление UUID. Потом раскоментировать
    // sqlite3_bind_blob(stmt, 1, &record->id(), sizeof(QUuid), SQLITE_STATIC);
    QByteArray buf = record->id().toByteArray();
    sqlite3_bind_blob(stmt, 1, buf.data(), buf.size(), SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        qCritical("Error of removing record: %s\n", sqlite3_errmsg(StorageI.db()));
        return;
    }

    emit recordRemoved(record);
}

//------------------------------------------------------------------------------
RecordContentPtr RecordMaster::loadContent(Record::Type type, int rowid)
{
    switch(type) {
        case Record::TextType: {
            return TextNoteMasterI.get(rowid);
        }
    }

    return  {};
}
