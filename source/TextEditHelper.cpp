/// @author M. A. Serebrennikov
#include "TextEditHelper.h"

#include <QQuickTextDocument>
#include <QStringBuilder>
#include <QTextDocument>

using namespace sp;

void TextEditHelper::setTextDocument(QQuickTextDocument *textDocument)
{
    Q_ASSERT_X(!_textDocument, "TextEditHelper", "Changing of textDocument is not supported");
    _textDocument = textDocument;

    if (!_css.isEmpty()) {
        _textDocument->textDocument()->setDefaultStyleSheet(_css);
    }

    format();
}

//------------------------------------------------------------------------------
void TextEditHelper::setText(const QString &text)
{
    if (_text != text) {
        _text = text;
        format();
        emit textChanged();
    }
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
            _textDocument->textDocument()->setDefaultStyleSheet(_css);
        }
        format();
        emit cssChanged();
    }

}

//------------------------------------------------------------------------------
void TextEditHelper::format()
{
    if (!_textDocument) {
        return;
    }

    QString htmlText(_text);

    // Ссылка на сайт
    QRegExp rx("\\b((?:https?:\\/\\/|www\\d{0,3}[.]|[a-z0-9.\\-]+[.][a-z]{1,4}|localhost\\/?)(?:.?[^\\s()<>.]+|\\((?:[^\\s()<>]+|(?:\\([^\\s()<>]+\\)))*\\))+)");
    for (int pos = 0, shift = 0
         ; (pos = rx.indexIn(_text, pos)) != -1
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

    updateCss();
    _textDocument->textDocument()->setHtml("<html><body>" + htmlText + "</body><html>");
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
        _textDocument->textDocument()->setDefaultStyleSheet(
                    QString("body { line-height: %1 } \n"
                            "a { text-decoration: none; color: %2}")
                    .arg(_lineHeight)
                    .arg(_linkColor.name()));
    } // Иначе стиль устанавливается в setCss
}
