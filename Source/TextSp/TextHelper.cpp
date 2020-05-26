/// @author M. A. Serebrennikov
#include "TextHelper.h"

#include <QAbstractTextDocumentLayout>
#include <QDebug>
#include <QQuickTextDocument>
#include <QStringBuilder>
#include <QTextDocument>
#include <QTextCursor>

using namespace sp;

void TextHelper::classBegin()
{

}

//------------------------------------------------------------------------------
void TextHelper::componentComplete()
{
    Q_ASSERT(_textDocument);
    _ready = true;
    connect(_textDocument, &QTextDocument::contentsChange, this, &TextHelper::onContentsChange);
}

//------------------------------------------------------------------------------
void TextHelper::setTextDocument(QQuickTextDocument *textDocument)
{
    Q_ASSERT_X(!_textDocument, "TextHelper", "Changing of textDocument is not supported");
    _textDocument = textDocument->textDocument();
}

//------------------------------------------------------------------------------
void TextHelper::setLineHeight(double lineHeight)
{
    if (!qFuzzyCompare(_lineHeight, lineHeight)) {
        _lineHeight = lineHeight;
        emit lineHeightChanged();
    }
}

//------------------------------------------------------------------------------
void TextHelper::onContentsChange(int /*position*/, int /*charsRemoved*/, int /*charsAdded*/)
{
    if (!_ready || !_textDocument) {
        return;
    }

    // TODO Optimize with help of variables: position, charsRemoved and charsAdded
    QTextCursor cursor(_textDocument);
    auto text = _textDocument->toRawText();

    // Clear format
    QTextCharFormat normalTextFormat;
    QTextBlockFormat normalBlockFormat;
    normalBlockFormat.setLineHeight(_lineHeight*100, QTextBlockFormat::ProportionalHeight);

    cursor.setPosition(0);
    cursor.setPosition(text.count(), QTextCursor::KeepAnchor);
    cursor.setCharFormat(normalTextFormat);
    cursor.setBlockFormat(normalBlockFormat);

    // Highlight links
    QRegExp rx("(?:(?:http[s]?:\\/\\/)?\\d+[.]\\d+[.]\\d+[.]\\d+|[-a-zA-Z0-9@:%_\\+.~#?&//=]{2,256}\\.[a-z]{2,4}|http[s]?:\\/\\/localhost)\\b(\\/[-a-zA-Z0-9@:%_\\+.~#?&//=]*)?");
    for (int pos = 0
         ; (pos = rx.indexIn(text, pos)) != -1
         ; pos += rx.matchedLength())
    {
        QString url = formatUrl(rx.cap(0));
        QTextCharFormat linkFormat;
        linkFormat.setAnchorHref(url);
        linkFormat.setAnchor(true);
        linkFormat.setForeground({_linkColor});

        cursor.setPosition(pos);
        cursor.setPosition(pos+rx.matchedLength(), QTextCursor::KeepAnchor);
        cursor.setCharFormat(linkFormat);
    }
}

//------------------------------------------------------------------------------
void TextHelper::setColor(const QColor &linkColor)
{
    if (_linkColor != linkColor) {
        _linkColor = linkColor;
        emit colorChanged();
    }
}

//------------------------------------------------------------------------------
QString TextHelper::formatUrl(const QString &url) const
{
    if (url.startsWith("http://") || url.startsWith("https://")) {
        return url;
    } else {
        // TODO Тут нужна обработка всех кривых случаев составления url'а
        QString result = "https://" + url;
        return result;
    }
}
