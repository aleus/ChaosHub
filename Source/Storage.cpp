/// @author M. A. Serebrennikov
#include "Storage.h"
#include "Tools.h"
#include "sqlite3.h"
#include "TagMaster.h"
#include "RecordMaster.h"
#include "TextNoteMaster.h"

#include <QDebug>

using namespace sp;

// static ----------------------------------------------------------------------
Storage &Storage::instance()
{
    static Storage storage;
    return storage;
}

// static ----------------------------------------------------------------------
std::optional<QUuid> Storage::getId(sqlite3_stmt *stmt, int columnNumber)
{
    const void* buf = sqlite3_column_blob(stmt, columnNumber);
    int bufsize = sqlite3_column_bytes(stmt, columnNumber);

    switch(bufsize) {
        case 38: // количество символов в человеческом представлении UUID
            return QUuid(QByteArray(reinterpret_cast<char *>(const_cast<void*>(buf)), bufsize));

        case sizeof(QUuid):
            return QUuid::fromRfc4122(QByteArray(reinterpret_cast<char *>(const_cast<void*>(buf)), bufsize));

        default:
            qCritical() << "Error of loading id of record, bufsize =" << bufsize;
            Q_ASSERT(false);
            return {};
    }
}

// static ----------------------------------------------------------------------
QString Storage::getString(sqlite3_stmt *stmt, int columnNumber)
{
    const uchar* textRaw = sqlite3_column_text(stmt, columnNumber);
    int textsize = sqlite3_column_bytes(stmt, columnNumber);

    if (textsize > 0) {
        return QString::fromUtf8(QByteArray(reinterpret_cast<const char*>(textRaw), textsize));
    } else {
        // qCritical() << "Error of getting text in query, column =" << columnNumber;
        // Q_ASSERT(false);
        return {};
    }
}

// static ----------------------------------------------------------------------
int Storage::getInt(sqlite3_stmt *stmt, int columnNumber)
{
    return sqlite3_column_int(stmt, columnNumber);
}

// static ----------------------------------------------------------------------
QDateTime Storage::getDate(sqlite3_stmt *stmt, int columnNumber)
{
    return QDateTime::fromMSecsSinceEpoch(sqlite3_column_int64(stmt, columnNumber));
}

//------------------------------------------------------------------------------
Storage::Storage()
{
}

//------------------------------------------------------------------------------
Storage::~Storage()
{
    if (_db) {
        sqlite3_close(_db);
    }
}

//------------------------------------------------------------------------------
void Storage::openDb(const QString &filePath)
{
    int error = sqlite3_open(filePath.toUtf8().data(), &_db);
    sqlite3_enable_load_extension(_db, 1);
    if (error) {
        qCritical() << "Can't open database: " << sqlite3_errmsg(_db);
        sqlite3_close(_db);
    }
}

//------------------------------------------------------------------------------
void Storage::createTable(const QString &query) {
    char *zErrMsg = nullptr;
    int error = sqlite3_exec(StorageI.db(), query.toUtf8().data(), nullptr, nullptr, &zErrMsg);
    if (error) {
        qCritical() << "Can't create table: " << sqlite3_errmsg(StorageI.db()) << endl;
    }
}

//------------------------------------------------------------------------------
void Storage::prepareStorage()
{
    RecordMasterI.prepareStorage();
    TextNoteMasterI.prepareStorage();
    TagMasterI.prepareStorage();
}
