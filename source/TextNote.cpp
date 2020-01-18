/// @author M. A. Serebrennikov
#include "Colors.h"
#include "Record.h"
#include "TextNote.h"

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
