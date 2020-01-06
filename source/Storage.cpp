/// @author M. A. Serebrennikov
#include "Storage.h"
#include "sqlite3.h"

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

    char *zErrMsg = 0;
    // "'id' BLOB NOT NULL PRIMARY KEY"
    // ",'type' INTEGER NOT NULL"
    // ",'contentId' INTEGER NOT NULL"
    // ",'date' INTEGER"
    // if ( error ) {
    //     qDebug() << "Can't insert data to table: " << sqlite3_errmsg(_db);
    // }

    // sqlite3_stmt *stmt;
    // sqlite3_prepare_v2(_db, "INSERT INTO 'Records' ('id', 'type', 'contentId', 'date') VALUES (?1, ?2, ?3, ?4);", -1, &stmt, NULL);       /* 1 */

    // QUuid debugId;
    // sqlite3_bind_blob(stmt, 1, "Susan", -1, SQLITE_TRANSIENT);                                         /* 2 */
    // sqlite3_bind_text(stmt, 1, "Susan", -1, SQLITE_STATIC);                                         /* 2 */
    // sqlite3_bind_int(stmt, 2, 21);                                                                  /* 3 */

    // int rc = sqlite3_step(stmt);
    // if (rc != SQLITE_DONE) {
    //     printf("ERROR inserting data: %s\n", sqlite3_errmsg(_db));
    //     return;
    // }

    // sqlite3_finalize(stmt);
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
    createTable("CREATE TABLE IF NOT EXISTS 'Records'("
                    "'id' BLOB NOT NULL PRIMARY KEY"
                    ",'type' INTEGER NOT NULL"
                    ",'contentId' INTEGER NOT NULL"
                    ",'date' INTEGER"
                ") WITHOUT ROWID;"

                "CREATE INDEX IF NOT EXISTS 'index_id' ON 'Records'('id');"
                "CREATE INDEX IF NOT EXISTS 'index_contentId' ON 'Records'('contentId');" );

    // Теги
    createTable("CREATE TABLE IF NOT EXISTS 'Tags'("
                    "'id' BLOB NOT NULL PRIMARY KEY"
                    ",'name' TEXT"
                    ",'parentId' BLOB"
                ") WITHOUT ROWID;"

                "CREATE INDEX IF NOT EXISTS 'index_id' ON 'Tags'('id');"
                "CREATE INDEX IF NOT EXISTS 'index_parentId' ON 'Tags'('parentId');");

    // Заметки-Теги
    createTable("CREATE TABLE IF NOT EXISTS 'RecordsTags'("
                    "'noteId' BLOB NOT NULL REFERENCES 'Records' ('id') ON DELETE CASCADE"
                    ",'tagId' BLOB NOT NULL REFERENCES 'Tags' ('id') ON DELETE CASCADE"
                ");"

                "CREATE INDEX IF NOT EXISTS 'index_noteId' ON 'RecordsTags'('noteId');"
                "CREATE INDEX IF NOT EXISTS 'index_tagId' ON 'RecordsTags'('tagId');");

    // Текстовые заметки
    createTable("CREATE VIRTUAL TABLE IF NOT EXISTS 'TextNotes' USING FTS5('text')");
}

//------------------------------------------------------------------------------
void Storage::debug()
{
    const char *db_name = "test.db";
    sqlite3 *db;
    char *zErrMsg = 0;
    int error;

    //------------------------------
    //Создание или открытие БД
    //------------------------------
    error = sqlite3_open(db_name, &db);
    if (error) {
        qDebug()<<"Can't open database: "<<sqlite3_errmsg(db);
        sqlite3_close(db);
        return;
    }

    //------------------------------
    //Создание таблицы
    //------------------------------
    //Если таблица уже создана, то эта конструкция будет выдавать ошибку!
    error = sqlite3_exec(db, "CREATE VIRTUAL TABLE table1 USING fts5(field1);", NULL, 0, &zErrMsg);
    if (error) {
        qDebug()<<"Can't create table: " << sqlite3_errmsg(db) << endl;
        // sqlite3_close(db);
    } else {
        //------------------------------
        //Ввод данных в таблицу
        //------------------------------
        error = sqlite3_exec(db, "INSERT INTO table1(field1) VALUES ('Суппер');", NULL, 0, &zErrMsg);
        if ( error ) {
            qDebug()<<"Can't insert data to table: "<<sqlite3_errmsg(db);
        }
        error = sqlite3_exec(db, "INSERT INTO table1(field1) VALUES ('Орех');", NULL, 0, &zErrMsg);
        error = sqlite3_exec(db, "INSERT INTO table1(field1) VALUES ('Яблоко');", NULL, 0, &zErrMsg);
        error = sqlite3_exec(db, "INSERT INTO table1(field1) VALUES ('Пер');", NULL, 0, &zErrMsg);
    }

    //------------------------------
    //Выборка данных из базы
    //------------------------------
    sqlite3_stmt *res;
    const char   *tail;

    error = sqlite3_prepare_v2(db,"SELECT field1 FROM table1 WHERE table1 = 'ор*'", 1000, &res, &tail);
    if (error) {
        qDebug()<<"Can't select data: "<<sqlite3_errmsg(db)<<endl;
        sqlite3_close(db);
    }

    //Отображаем на экране
    qDebug() << "Display result from table1" << endl;
    int rec_count = 0;
    while (sqlite3_step(res) == SQLITE_ROW) {
        qDebug() << QString::fromUtf8(reinterpret_cast<const char*>(sqlite3_column_text(res, 0)));
        rec_count++;
    }

    //------------------------------
    //Корректное завершение работы с БД
    //------------------------------
    sqlite3_close(db);
}
