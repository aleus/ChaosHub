/// @author M. A. Serebrennikov
#pragma once

#include <QObject>
#include <QColor>
#include <QQmlParserStatus>

class QTextDocument;
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
class TextHelper: public QObject, public QQmlParserStatus
{
    Q_OBJECT

    Q_PROPERTY(QQuickTextDocument* textDocument WRITE setTextDocument CONSTANT)
    // Q_PROPERTY(QString css READ css WRITE setCss NOTIFY cssChanged)
    Q_PROPERTY(double lineHeight READ lineHeight WRITE setLineHeight NOTIFY lineHeightChanged)
    Q_PROPERTY(QColor linkColor READ linkColor WRITE setColor NOTIFY colorChanged)

    Q_INTERFACES(QQmlParserStatus)

    public:
        //--------------------------------------------------------------------
        // Get
        //--------------------------------------------------------------------
        /** Возвращает межстрочный интервал в относительных единицах (1.0, 1.5 и т.п.) */
        inline double lineHeight() const { return _lineHeight; }

        /** Возвращает цвет ссылки. */
        inline const QColor& linkColor() const { return _linkColor; }

        //--------------------------------------------------------------------
        // Set
        //--------------------------------------------------------------------
        /** Устанавливает указатель на QTextDocument, полученный от TextEdit. */
        void setTextDocument(QQuickTextDocument *textDocument);

        /** Устанавливает межстрочный интервал. */
        void setLineHeight(double lineHeight);

        /** Устанавливает цвет ссылки. */
        void setColor(const QColor &linkColor);

        //----------------------------------------------------------------------
        // Override
        //----------------------------------------------------------------------
        void classBegin() override;
        void componentComplete() override;

    private:
        /**
         * Приводит url к стандартному виду (без этого ссылка "ya.ru" не
         * откроется в браузере).
         */
        QString formatUrl(const QString &url) const;

        void onContentsChange(int position, int charsRemoved, int charsAdded);

    signals:
        void lineHeightChanged() const;
        void colorChanged();

    private:
        QTextDocument* _textDocument = nullptr;
        QColor _linkColor = "blue";
        double _lineHeight = 1.0;
        bool _ready = false;
};

} // namespace sp
