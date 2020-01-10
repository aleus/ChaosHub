/// @author M. A. Serebrennikov
#include "Storage.h"
#include "Tools.h"
#include "sqlite3.h"

#include "Record.h" // Debug!!!

#include <QDebug>

using namespace sp;

// static ----------------------------------------------------------------------
Storage &Storage::instance()
{
    static Storage storage;
    return storage;
}

//------------------------------------------------------------------------------
Storage::Storage()
{
    // Debug!!!
    openDb(QStringLiteral("Notes.db"));
    prepareDb();
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
    if (error) {
        qCritical() << "Can't open database: " << sqlite3_errmsg(_db);
        sqlite3_close(_db);
    }
}

//------------------------------------------------------------------------------
void Storage::prepareDb()
{
    auto createTable = [this](const char *query) {
        char *zErrMsg = 0;
        int error = sqlite3_exec(_db, query, NULL, 0, &zErrMsg);
        if (error) {
            qCritical() << "Can't create table: " << sqlite3_errmsg(_db) << endl;
        }
    };

    // Записи в хабе
    createTable("CREATE TABLE IF NOT EXISTS `Records`("
                    "`id` BLOB NOT NULL PRIMARY KEY"
                    ",`type` INTEGER NOT NULL"
                    ",`contentId` INTEGER NOT NULL"
                    ",`date` INTEGER"
                ") WITHOUT ROWID;"

                "CREATE INDEX IF NOT EXISTS `index_id` ON `Records`(`id`);"
                "CREATE INDEX IF NOT EXISTS `index_contentId` ON `Records`(`contentId`);" );

    // Теги
    createTable("CREATE TABLE IF NOT EXISTS `Tags`("
                    "`id` BLOB NOT NULL PRIMARY KEY"
                    ",`name` TEXT"
                    ",`parentId` BLOB"
                ") WITHOUT ROWID;"

                "CREATE INDEX IF NOT EXISTS `index_id` ON `Tags`(`id`);"
                "CREATE INDEX IF NOT EXISTS `index_parentId` ON `Tags`(`parentId`);");

    // Заметки-Теги
    createTable("CREATE TABLE IF NOT EXISTS `RecordsTags`("
                    "`noteId` BLOB NOT NULL REFERENCES `Records` (`id`) ON DELETE CASCADE"
                    ",`tagId` BLOB NOT NULL REFERENCES `Tags` (`id`) ON DELETE CASCADE"
                ");"

                "CREATE INDEX IF NOT EXISTS `index_noteId` ON `RecordsTags`(`noteId`);"
                "CREATE INDEX IF NOT EXISTS `index_tagId` ON `RecordsTags`(`tagId`);");

    // Текстовые заметки
    createTable("CREATE VIRTUAL TABLE IF NOT EXISTS `TextNotes` USING FTS5(`text`)");
}
