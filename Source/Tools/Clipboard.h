/// @author M. A. Serebrennikov
#pragma once

#include <QObject>

namespace sp {

#define ClipboardI Clipboard::instance()

/*************************************************************************//**
 * @brief Синглетон для доступа к буферу обмена из QML.
 * @details details
 ****************************************************************************/
class Clipboard: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString text READ text WRITE setText NOTIFY changed)

    public:
        static Clipboard& instance();

        /** Возвращает текст из буфера обмена. */
        QString text() const;

        /** Записывает текст в буфер обмена. */
        void setText(const QString &text);

    signals:
        void changed();

    private:
        Clipboard();
};

} // namespace sp
