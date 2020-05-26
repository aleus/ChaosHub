/// @author M. A. Serebrennikov
#include "TagMaster.h"
#include "Tag.h"
#include "sqlite3.h"
#include "Storage.h"
#include "Tools.h"
#include "Defer.h"
#include "RecordMaster.h"

#include <QDebug>

using namespace sp;

TagMaster &TagMaster::instance()
{
    static TagMaster result;
    return result;
}

//------------------------------------------------------------------------------
QVector<TagPtr> TagMaster::get()
{
    QVector<TagPtr> result;
    sqlite3_stmt *stmt;
    defer(sqlite3_finalize(stmt));

    QString query = "SELECT `name`, `id`, from `" + _tableName + "` "
                    "ORDER BY `date` DESC";
    sqlite3_prepare_v2(StorageI.db(), query.toUtf8().data(), -1, &stmt, nullptr);

    for(;;) {
        int res = sqlite3_step (stmt);

        if (res == SQLITE_ROW) {
            auto name = Storage::getString(stmt, 0);
            auto id   = Storage::getId(stmt, 1); if (!id) { continue; }
            auto tag  = TagPtr::create(*id);

            tag->setName(name);
            result.append(tag);
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
void TagMaster::append(const TagPtr &tag)
{
    Q_ASSERT(tag);

    sqlite3_stmt *stmt;
    defer(sqlite3_finalize(stmt));

    QString query = "INSERT INTO `" + _tableName + "` (`name`, `id`) "
                    "VALUES (?1, ?2, ?3)";
    sqlite3_prepare_v2(StorageI.db(), query.toUtf8().data(), -1, &stmt, nullptr);

    // TODO На момент отладки принимаются человеческое представление UUID. Потом раскоментировать
    // sqlite3_bind_blob(stmt, 1, &record->id(), sizeof(QUuid), SQLITE_STATIC);
    QByteArray buf = tag->name().toUtf8();
    sqlite3_bind_text(stmt, 2, buf.data(), buf.size(), SQLITE_STATIC);
    buf = tag->id().toByteArray();
    sqlite3_bind_blob(stmt, 2, buf.data(), buf.size(), SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        printf("ERROR inserting data: %s\n", sqlite3_errmsg(StorageI.db()));
        return;
    }

    emit tagCreated(tag);
}

//------------------------------------------------------------------------------
void TagMaster::remove(const TagPtr &tag)
{

}

//------------------------------------------------------------------------------
void TagMaster::remove(const QVector<TagPtr> &tags)
{

}

//------------------------------------------------------------------------------
void TagMaster::remove(const QVector<QUuid> &tags)
{

}

//------------------------------------------------------------------------------
void TagMaster::prepareStorage() const
{
    auto createTable = [](const QString &query) {
        char *zErrMsg = nullptr;
        int error = sqlite3_exec(StorageI.db(), query.toUtf8().data(), nullptr, nullptr, &zErrMsg);
        if (error) {
            qCritical() << "Can't create table: " << sqlite3_errmsg(StorageI.db()) << endl;
        }
    };

    // Теги
    createTable("CREATE TABLE IF NOT EXISTS `" + _tableName + "`("
                    "`name` TEXT"
                    ",`id` BLOB NOT NULL PRIMARY KEY"
                ") WITHOUT ROWID;"

                "CREATE INDEX IF NOT EXISTS `index_id` ON `Tags`(`id`);");

    // Заметки-Теги
    createTable("CREATE TABLE IF NOT EXISTS `" + _tableNameMath + "`("
                    "`noteId` BLOB NOT NULL REFERENCES `" + RecordMasterI.tableName() + "` (`id`) ON DELETE CASCADE"
                    ",`tagId` BLOB NOT NULL REFERENCES `" + _tableName + "` (`id`) ON DELETE CASCADE"
                ");"

                "CREATE INDEX IF NOT EXISTS `index_noteId` ON `" + _tableNameMath + "`(`noteId`);"
                "CREATE INDEX IF NOT EXISTS `index_tagId` ON `" + _tableNameMath + "`(`tagId`);");
}

//------------------------------------------------------------------------------
void TagMaster::remove(Tag *tagRaw)
{
    if (!tagRaw) {
        Q_ASSERT(false);
        return;
    }

    auto tag = tagRaw->sharedFromThis();
    sqlite3_stmt *stmt;
    defer(sqlite3_finalize(stmt));

    QString query = "DELETE FROM `" + _tableName + "` WHERE `id`=?1";
    sqlite3_prepare_v2(StorageI.db(), query.toUtf8().data(), -1, &stmt, nullptr);

    // TODO На момент отладки принимаются человеческое представление UUID. Потом раскоментировать
    // sqlite3_bind_blob(stmt, 1, &record->id(), sizeof(QUuid), SQLITE_STATIC);
    QByteArray buf = tag->id().toByteArray();
    sqlite3_bind_blob(stmt, 1, buf.data(), buf.size(), SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        qCritical("Error of removing record: %s\n", sqlite3_errmsg(StorageI.db()));
        return;
    }

    emit tagRemoved(tag);
}
