/// @author M. A. Serebrennikov
#include "RecordMaster.h"
#include "Storage.h"
#include "TextNoteMaster.h"
#include "TextNote.h"
#include "Tools.h"
#include "sqlite3.h"

#include <QDebug>
#include <QStringBuilder>

using namespace sp;

// static ----------------------------------------------------------------------
TextNoteMaster &TextNoteMaster::instance()
{
    static TextNoteMaster result;
    return result;
}

//------------------------------------------------------------------------------
void TextNoteMaster::create(const QString &text)
{
    // TODO Вставить транзакцию

    // Записываем в БД новую запись
    sqlite3_stmt *stmt;
    defer(sqlite3_finalize(stmt));

    QString query = "INSERT INTO `" % _tableName % "` (`text`) VALUES (?1)";
    sqlite3_prepare_v2(StorageI.db(), query.toUtf8().data(), -1, &stmt, nullptr);
    QByteArray buf = text.trimmed().toUtf8();
    sqlite3_bind_text(stmt, 1, buf.data(), buf.size(), SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        printf("ERROR inserting data: %s\n", sqlite3_errmsg(StorageI.db()));
        return;
    } else {
        // Create record for text note
        // auto *textNote = new RecordContentPtr(new TextNote(text.trimmed())); // There is pointer on pointer for cache
        auto *textNote = new RecordContentPtr(TextNotePtr::create(text.trimmed())); // There is pointer on pointer for cache
        auto record = RecordPtr::create();
        record->type(Record::TextType)
              ->content(*textNote);

        auto rowid = sqlite3_last_insert_rowid(StorageI.db());
        (*textNote)->setRowid(rowid);
        _notes.insert(rowid, textNote);

        RecordMasterI.add(record);
    }
}

//------------------------------------------------------------------------------
RecordContentPtr TextNoteMaster::get(int rowid)
{
    if (_notes.contains(rowid)) {
        return *_notes.object(rowid);
    } else {
        sqlite3_stmt *stmt;
        defer(sqlite3_finalize(stmt));

        QString query = "SELECT `text` from `" % _tableName % "` WHERE rowid = ?1";
        sqlite3_prepare_v2(StorageI.db(), query.toUtf8().data(), -1, &stmt, nullptr);
        sqlite3_bind_int(stmt,1, rowid);

        for(;;) {
            int res = sqlite3_step (stmt);

            if (res == SQLITE_ROW) {
                auto text = Storage::getString(stmt, 0);
                auto *note = new RecordContentPtr(TextNotePtr::create(rowid, text));
                _notes.insert(rowid, note);

                return *note;
            } else if (res == SQLITE_DONE) {
                break;
            } else {
                qCritical() << "Error of record loading";
                break;
            }
        } // for(;;) {

        return {};
    }
}

//------------------------------------------------------------------------------
void TextNoteMaster::prepareStorage() const
{
    StorageI.createTable("CREATE VIRTUAL TABLE IF NOT EXISTS `" % _tableName % "` USING FTS5(`text`)");
}
