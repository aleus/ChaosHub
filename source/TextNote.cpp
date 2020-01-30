/// @author M. A. Serebrennikov
#include "Colors.h"
#include "Record.h"
#include "TextNote.h"
#include "sqlite3.h"
#include "Defer.h"
#include "Storage.h"

#include <QRegExp>
#include <QStringBuilder>
#include <QDebug>
#include <QQuickTextDocument>
#include <QTextDocument>

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

//------------------------------------------------------------------------------
bool TextNote::remove()
{
    // TODO Перенести в TextNoteMaster
    sqlite3_stmt *stmt;
    defer(sqlite3_finalize(stmt));

    // TODO Вынести название таблицы в константы
    const char *query = "DELETE FROM `TextNotes` WHERE `rowid`=?1";
    sqlite3_prepare_v2(StorageI.db(), query, -1, &stmt, NULL);

    sqlite3_bind_int(stmt, 1, rowid());

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        qCritical("Error of removing text note: %s\n", sqlite3_errmsg(StorageI.db()));
        return false;
    }

    return true;
}
