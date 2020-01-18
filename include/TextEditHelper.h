/// @author M. A. Serebrennikov
#pragma once

#include <QObject>
#include <QColor>

class QQuickTextDocument;

namespace sp {

/*************************************************************************//**
 * @brief Класс со вспомогательным методами для форматирования текста
 * QML-компонента TextEdit.
 *
 * @details Класс позволяет расширить параметры оформления текста, парсит ссылки
 * и др. Для форматирования преобразует текст в HTML-код и CSS. Для
 * работы класса нужно указать свойства textDocument, полученное из TextEdit
 * и text (в TextEdit это поле оставить пустым). Чтобы работал
 *
 * @todo Разделить класс и вынести в библиотеку sp_libs.
 ****************************************************************************/
class TextEditHelper: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QQuickTextDocument* textDocument READ textDocument WRITE setTextDocument NOTIFY textDocumentChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QString css READ css WRITE setCss NOTIFY cssChanged)
    Q_PROPERTY(double lineHeight READ lineHeight WRITE setLineHeight NOTIFY lineHeightChanged)
    Q_PROPERTY(QColor linkColor READ linkColor WRITE setColor NOTIFY colorChanged)

    public:
        //--------------------------------------------------------------------
        // Get
        //--------------------------------------------------------------------
        /** Возвращает указатель на QQuickTextDocument, полученный от TextEdit. */
        inline QQuickTextDocument *textDocument() const { return _textDocument; }

        /** Возвращает изначальный текст. */
        inline const QString& text() const { return _text; }

        /** Возвращает межстрочный интервал в относительных единицах (1.0, 1.5 и т.п.) */
        inline double lineHeight() const { return _lineHeight; }

        /** Возвращает CSS форматируемого текста. */
        inline const QString& css() const { return _css; }

        /** Возвращает цвет ссылки. */
        inline const QColor& linkColor() const { return _linkColor; }

        //--------------------------------------------------------------------
        // Set
        //--------------------------------------------------------------------
        /** Устанавливает указатель на QQuickTextDocument, полученный от TextEdit. */
        void setTextDocument(QQuickTextDocument *textDocument);

        /** Устанавливает изначальный текст, перед его форматированием. */
        void setText(const QString &text);

        /** Устанавливает межстрочный интервал. */
        void setLineHeight(double lineHeight);

        /** Устанавливает css форматируемого текста. */
        void setCss(const QString &css);

        /** Устанавливает цвет ссылки. */
        void setColor(const QColor &linkColor);

        //--------------------------------------------------------------------
        // Special
        //--------------------------------------------------------------------
        /**
         * @brief Форматирует текст и устанавливает его в TextEdit.
         * @warning Для правильной работы нужно вызвать в Component.onCompleted
         * элемента TextEdit
         */
        Q_INVOKABLE void format();

    private:

        /**
         * Приводит url к стандартному виду (без этого ссылка "ya.ru" не
         * откроется в браузере).
         */
        QString formatUrl(const QString &url) const;

        /** Либо составляет CSS из указанных свойств, либо использует _css (если не пуста). */
        void updateCss();

    signals:
        void textDocumentChanged() const;
        void lineHeightChanged() const;
        void textChanged() const;
        void cssChanged() const;
        void colorChanged();

    private:
        QQuickTextDocument* _textDocument = nullptr;
        double _lineHeight = 1.0;
        QString _text;
        QString _css;
        QColor _linkColor = "blue";
};

} // namespace sp
