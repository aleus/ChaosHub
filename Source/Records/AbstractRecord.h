/// @author M.Serebrennikov
#pragma once

#include <QObject>
#include <QUuid>

namespace sp {

/***************************************************************************//**
 * @brief AbstractNamedObject - базовый класс для хранимых объектов имеющих UUID.
 ******************************************************************************/
class AbstractRecord : public QObject
{
    Q_OBJECT

    public:
        //--------------------------------------------------------------------
        // Get
        //--------------------------------------------------------------------
        /** Возвращает идентификатор тега. */
        inline const QUuid& id() const { return _id; }

    protected:
        /** Конструктор для создания нового тега. Генерируется новый id. */
        AbstractRecord();

        /** Конструктор для загрузки тега из хранилища. */
        AbstractRecord(const QUuid &id);

    signals:
        void nameChanged();

    private:
        QUuid _id;
};
} // namespace sp
