/// @author M. A. Serebrennikov
#include "Record.h"
#include "RecordContent.h"
#include "RecordsMaster.h"
#include "Storage.h"
#include "Tools.h"
#include "sqlite3.h"
#include "TextNote.h"

#include <QDebug>

using namespace sp;

RecordsMaster &RecordsMaster::instance()
{
    static RecordsMaster master;
    return master;
}

//------------------------------------------------------------------------------
QVector<RecordPtr> RecordsMaster::get(const QString &tag, int limit, int offset)
{
    QVector<RecordPtr> result;

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(StorageI.db(),
                       "SELECT `id`, `type`, `contentId`, `date` from `Records`", -1, &stmt, NULL);

    for(;;) {
        int res = sqlite3_step (stmt);

        if (res == SQLITE_ROW) {
            const void* buf = sqlite3_column_blob(stmt, 0);
            int bufsize = sqlite3_column_bytes(stmt, 0);
            // Debug!!! 38 - количество символов в человеческом представлении UUid
            // if (bufsize != sizeof (QUuid)) {
            if (bufsize != 38) {
                qCritical() << "Error of loading id of record, bufsize =" << bufsize;
                Q_ASSERT(false);
                continue;
            }
            QUuid id = QUuid(QByteArray(reinterpret_cast<char *>(const_cast<void*>(buf)), bufsize));

            auto type = static_cast<Record::Type>(sqlite3_column_int(stmt, 1));
            auto contentId = sqlite3_column_int(stmt, 2);
            auto date = QDateTime::fromTime_t(sqlite3_column_int64(stmt, 3));

            RecordPtr record(new Record(id,type,loadContent(type, contentId), date));
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
void RecordsMaster::addRecord(const RecordPtr &record)
{
    Q_ASSERT(record->content());
    Q_ASSERT(record->content()->rowid() > 0);

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(StorageI.db(),
                       "INSERT INTO `Records` (`id`, `type`, `contentId`, `date`) "
                       "VALUES (?1, ?2, ?3, ?4);", -1, &stmt, NULL);

    // TODO На момент отладки принимаются человеческое представление UUID. Потом раскоментировать
    // sqlite3_bind_blob(stmt, 1, &record->id(), sizeof(QUuid), SQLITE_STATIC);
    QByteArray buf = record->id().toByteArray();
    sqlite3_bind_blob(stmt, 1, buf.data(), buf.size(), SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, record->type());
    sqlite3_bind_int(stmt, 3, record->content()->rowid());
    sqlite3_bind_int(stmt, 4, record->date().toMSecsSinceEpoch());

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        printf("ERROR inserting data: %s\n", sqlite3_errmsg(StorageI.db()));
        return;
    } else {
        qDebug() << "record inserted";
    }

    sqlite3_finalize(stmt);
}

//------------------------------------------------------------------------------
void RecordsMaster::remove(const RecordPtr &record)
{
}

//------------------------------------------------------------------------------
void RecordsMaster::remove(const QVector<RecordPtr> &records)
{

}

//------------------------------------------------------------------------------
void RecordsMaster::remove(const QVector<QUuid> &records)
{

}

//------------------------------------------------------------------------------
RecordContentPtr RecordsMaster::loadContent(Record::Type type, int rowid)
{
    switch(type) {
        case Record::TextType: {
            return TextNoteMaster::load(rowid);
        }
    }

    return  {};
}
