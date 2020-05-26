/// @author M. A. Serebrennikov
#pragma once

#include <QObject>

namespace sp {

/*************************************************************************//**
 * @brief Абстрактный класс содержимого для объекта класса Record.
 ****************************************************************************/
class RecordContent: public QObject
{
    Q_OBJECT

    public:
        /** Возвращает rowId в соотвествующей таблице. */
        inline int64_t rowid() const { return _rowid; }

        /** Устанавилвает rowid. */
        void setRowid(int64_t rowid);

        /**
         * @brief Удаляет данные объекта из хранилища.
         * @return Возвращает true, если данные удалены успешно, иначе false.
         */
        virtual bool remove() = 0;

    protected:
        RecordContent();
        RecordContent(int64_t rowid);

    protected:
        int64_t _rowid = -1;
};

} // namespace sp
