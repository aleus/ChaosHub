/// @author M. A. Serebrennikov
#pragma once

#include "AbstractRecord.h"

#include <QObject>
#include <QSharedPointer>
#include <QUuid>

namespace sp {

/*************************************************************************//**
 * @brief Класс тега из модели TagModel.
 ****************************************************************************/
class Tag: public AbstractRecord, public QEnableSharedFromThis<Tag>
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

    public:
        //--------------------------------------------------------------------
        // GET
        //--------------------------------------------------------------------
        /** Возвращает название тега. */
        inline const QString& name() const { return _name; }

        //--------------------------------------------------------------------
        // SET
        //--------------------------------------------------------------------
        /** Устанавливает название тега. */
        void setName(const QString &name);

    private:
        /** Вся работа через умные указатели. */
        using AbstractRecord::AbstractRecord;
        friend class QSharedPointer<Tag>;

    signals:
        void nameChanged();

    private:
        QString _name;
};

} // namespace sp
