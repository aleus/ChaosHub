/// @author M. A. Serebrennikov
#pragma once

#include "PointersTypedef.h"
#include <QObject>
#include <QUuid>

namespace sp {

/*************************************************************************//**
 * @brief Класс тега из модели TagModel.
 ****************************************************************************/
class Tag: public QObject, public QEnableSharedFromThis<Tag>
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

    public:
        /** Конструктор для создания нового тега. Генерируется новый id. */
        explicit Tag(const QUuid &parentId = {});

        /** Конструктор для загрузки тега из хранилища. */
        Tag(const QString &name, const QUuid &id, const QUuid &parentId = {});

        // Копирующего и перемещеающего конструктора не должно быть, вся передача через TagPtr.
        Tag(const Tag &tag) = delete;
        Tag(Tag &&tag) = delete;

        //--------------------------------------------------------------------
        // Get
        //--------------------------------------------------------------------
        /** Возвращает название тега. */
        inline const QString& name() const { return _name; }

        /** Возвращает идентификатор тега. */
        inline const QUuid& id() const { return _id; }

        /** Возвращает идентификатор родительского тега. */
        inline const QUuid& parentId() const { return _parentId; }

        //--------------------------------------------------------------------
        // Set
        //--------------------------------------------------------------------
        /** Устанавливает название тега. */
        void setName(const QString &name);

        /** Устанавливает родительский элемент тега. */
        void setParentId(const QUuid &parentId);

    signals:
        void nameChanged();

    private:
        QString _name;
        QUuid _id;
        QUuid _parentId;
};

} // namespace sp
