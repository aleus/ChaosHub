/// @author M. A. Serebrennikov
#include "Record.h"
#include "TextNote.h"

#include <QRegExp>
#include <QStringBuilder>

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
QString TextNote::textRendered() const
{
    QString result(_text);

    // Ссылка на сайт
    QRegExp rx("\\b((?:https?:\\/\\/|www\\d{0,3}[.]|[a-z0-9.\\-]+[.][a-z]{1,4}|localhost\\/?)(?:.?[^\\s()<>.]+|\\((?:[^\\s()<>]+|(?:\\([^\\s()<>]+\\)))*\\))+)");
    for (int pos = 0, shift = 0
         ; (pos = rx.indexIn(_text, pos)) != -1
         ; pos += rx.matchedLength())
    {
        static QString suffix("</a>");
        QString prefix = "<a href='" % rx.cap(0) %"' style='text-decoration: none'>";

        result.insert(shift + pos + rx.matchedLength(), suffix);
        result.insert(shift + pos, prefix);
        shift += suffix.length() + prefix.length();
    }

    // Перевод строки
    result.replace(QStringLiteral("\n\n"), QStringLiteral("<BR><BR>\n"));

    return result;
}

//------------------------------------------------------------------------------
void TextNote::setText(QString text)
{
    if (_text != text) {
        _text = text;
        emit textChanged();
    }
}
