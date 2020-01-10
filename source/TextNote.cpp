/// @author M. A. Serebrennikov
#include "Record.h"
#include "RecordsMaster.h"
#include "Storage.h"
#include "TextNote.h"
#include "Tools.h"
#include "sqlite3.h"

#include <QDebug>

using namespace sp;

TextNote::TextNote(const QString &text)
    : _text(text)
{

}

TextNote::TextNote(int rowid, const QString &text)
    : RecordContent(rowid)
    , _text(text)
{

}

//------------------------------------------------------------------------------
void TextNote::setText(QString text)
{
    if (_text != text) {
        _text = text;
        emit textChanged();
    }
}

// static ----------------------------------------------------------------------
void TextNoteMaster::create(const QString &text)
{
    qDebug() << "createRecord";

    // TODO Вставить транзакцию

    // Записываем в БД новую запись
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(StorageI.db(),
                       "INSERT INTO `TextNotes` (`text`) "
                       "VALUES (?1);", -1, &stmt, nullptr);
    QByteArray buf = text.toUtf8();
    sqlite3_bind_text(stmt, 1, buf.data(), buf.size(), SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        printf("ERROR inserting data: %s\n", sqlite3_errmsg(StorageI.db()));
        return;
    } else {
        // Создаём запись для текстовой заметки.
        RecordContentPtr textNote(new TextNote(text));
        RecordPtr record(new Record(Record::TextType, textNote));
        textNote->setRowid(sqlite3_last_insert_rowid(StorageI.db()));

        qDebug() << "Text note created";
        RecordsMasterI.addRecord(record);
    }

    sqlite3_finalize(stmt);
}

// static ----------------------------------------------------------------------
RecordContentPtr TextNoteMaster::load(int rowid)
{
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(StorageI.db(),
                       "SELECT `text` from `TextNotes` WHERE rowid = ?1", -1, &stmt, NULL);
    sqlite3_bind_int(stmt,1, rowid);

    for(;;) {
        int res = sqlite3_step (stmt);

        if (res == SQLITE_ROW) {
            const uchar* textRaw = sqlite3_column_text(stmt, 0);
            int textsize = sqlite3_column_bytes(stmt, 0);
            if (textsize <= 0) {
                qCritical() << "Error of loading text of textNote, textsize =" << textsize << "rowid =" << rowid;
                Q_ASSERT(false);
                continue;
            }
            QString text(QByteArray(reinterpret_cast<const char*>(textRaw), textsize));

            RecordContentPtr content(new TextNote(rowid, text));
            return content;
        } else if (res == SQLITE_DONE) {
            break;
        } else {
            qCritical() << "Error of record loading";
            break;
        }
    } // for(;;) {

    return {};
}
