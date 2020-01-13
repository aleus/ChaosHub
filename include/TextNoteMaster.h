/// @author M. A. Serebrennikov
#pragma once

#include "PointersTypedef.h"

#include <QCache>
#include <QObject>

namespace sp {

#define TextNoteMasterI TextNoteMaster::instance()

/***************************************************************************//**
 * @brief Синглетон, управляющий текстовыми заметками.
 *
 * @details Класс позволяет создавать новую, получать и удалять заметки.
 * При обращении к заметке она либо загружается из хранилища, либо кешируется
 * в памяти.
 ******************************************************************************/
class TextNoteMaster: public QObject
{
    Q_OBJECT

    public:
        static TextNoteMaster& instance();

        /** Создаёт новую текстовую заметку и отправляет в хранилище. */
        Q_INVOKABLE void create(const QString &text);

        /**
         * @brief Возвращает заметку с заданным идентификатором.
         * @details Если заметка не присутствует в кеше, то загружает из
         * хранилища, иначе берёт из кеша.
         */
        RecordContentPtr get(int rowid);

    private:
        TextNoteMaster() = default;

    private:
        QCache<int, RecordContentPtr> _notes{1000}; // TODO После добавления класса Settings, вынести в настройки
};

} // namespace sp
