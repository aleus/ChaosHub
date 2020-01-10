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
        inline int rowid() const { return _rowid; }

        /** Устанавилвает rowid. */
        void setRowid(int rowid);

    protected:
        RecordContent();
        RecordContent(int rowid);

    protected:
        int _rowid = -1;
};

} // namespace sp
