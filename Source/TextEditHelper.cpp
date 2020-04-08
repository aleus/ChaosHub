/// @author M. A. Serebrennikov
#include "TextEditHelper.h"

#include <QQuickTextDocument>
#include <QTextDocument>
#include <QStringBuilder>
#include <QTextDocument>
#include <QDebug>

using namespace sp;

void TextEditHelper::classBegin()
{

}

//------------------------------------------------------------------------------
void TextEditHelper::componentComplete()
{
    _ready = true;
    Q_ASSERT(_textDocument);
    format();

    connect(_textDocument, &QTextDocument::contentsChanged, this, [this]() {
        // Debug!!!
        setRawText(_textDocument->toRawText());
    });
}

//------------------------------------------------------------------------------
void TextEditHelper::setRawText(const QString &text)
{
    if (_rawText != text) {
        _rawText = text;
        format();
        emit rawTextChanged();
    }
}

//------------------------------------------------------------------------------
void TextEditHelper::setTextDocument(QQuickTextDocument *textDocument)
{
    Q_ASSERT_X(!_textDocument, "TextEditHelper", "Changing of textDocument is not supported");
    _textDocument = textDocument->textDocument();

    if (!_css.isEmpty()) {
        _textDocument->setDefaultStyleSheet(_css);
    }

    format();
}

//------------------------------------------------------------------------------
void TextEditHelper::setLineHeight(double lineHeight)
{
    if (!qFuzzyCompare(_lineHeight, lineHeight)) {
        _lineHeight = lineHeight;
        format();
        emit lineHeightChanged();
    }
}

//------------------------------------------------------------------------------
void TextEditHelper::setCss(const QString &css)
{
    if (_css != css) {
        _css = css;
        if (_textDocument) {
            _textDocument->setDefaultStyleSheet(_css);
        }
        format();
        emit cssChanged();
    }

}

//------------------------------------------------------------------------------
void TextEditHelper::format()
{
    if (!_ready || !_textDocument) {
        return;
    }

    QString htmlText(_rawText);

    // Ссылка на сайт
    QRegExp rx("(?:(?:http[s]?:\\/\\/)?\\d+[.]\\d+[.]\\d+[.]\\d+|[-a-zA-Z0-9@:%_\\+.~#?&//=]{2,256}\\.[a-z]{2,4}|http[s]?:\\/\\/localhost)\\b(\\/[-a-zA-Z0-9@:%_\\+.~#?&//=]*)?");
    for (int pos = 0, shift = 0
         ; (pos = rx.indexIn(_rawText, pos)) != -1
         ; pos += rx.matchedLength())
    {
        static QString suffix("</a>");
        QString prefix = "<a href='" % formatUrl(rx.cap(0)) % "'>";

        htmlText.insert(shift + pos + rx.matchedLength(), suffix);
        htmlText.insert(shift + pos, prefix);
        shift += suffix.length() + prefix.length();
    }

    // Перевод строки
    htmlText.replace('\n', QStringLiteral("<BR>\n"));
    qDebug() << "format" << htmlText;

    updateCss();
    _textDocument->setHtml("<html><body>" + htmlText + "</body><html>");
}

//------------------------------------------------------------------------------
void TextEditHelper::setColor(const QColor &linkColor)
{
    if (_linkColor != linkColor) {
        _linkColor = linkColor;
        format();
        emit colorChanged();
    }
}

//------------------------------------------------------------------------------
QString TextEditHelper::formatUrl(const QString &url) const
{
    if (url.startsWith("http://") || url.startsWith("https://")) {
        return url;
    } else {
        // TODO Тут нужна обработка всех кривых случаев составления url'а
        QString result = "https://" + url;
        return result;
    }
}

//---------------------------------------------------------------------------------------
void TextEditHelper::updateCss()
{
    if (_css.isEmpty()) {
        _textDocument->setDefaultStyleSheet(
                    QString("body { line-height: %1 } \n"
                            "a { text-decoration: none; color: %2}")
                    .arg(_lineHeight)
                    .arg(_linkColor.name()));
    } // Иначе стиль устанавливается в setCss
}
