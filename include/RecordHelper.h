/// @author M. A. Serebrennikov
#pragma once

#include <QObject>

namespace sp {

#define RecordHelperI RecordHelper::instance()

/*************************************************************************//**
 * @brief Класс со вспомогательными методами для работы заметок в GUI.
 * @details details
 ****************************************************************************/
class RecordHelper: public QObject
{
    Q_OBJECT

    public:
        static RecordHelper& instance();

        /**
         * Приводит url к стандартному виду (без этого ссылка "ya.ru" не
         * откроется в браузере).
         */
        Q_INVOKABLE QString formatUrl(const QString &url) const;

    private:
        RecordHelper() = default;
};

} // namespace sp
