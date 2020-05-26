/// @author M.Serebrennikov
#pragma once

#include "AbstractRecord.h"
#include "PointersTypedef.h"

#include <QObject>
#include <QSet>
#include <QSharedPointer>
#include <QUuid>

namespace sp {

/***************************************************************************//**
 * @brief Класс Category содержит данные по категориям записей (Record).
 *
 * @details Категории фильтруют записи по списку тегов. Категории создаются
 * и хранятся в CategoryMaster.
 ******************************************************************************/
class Category : public AbstractRecord, public QEnableSharedFromThis<Category>
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

    public:
        //----------------------------------------------------------------------
        // GET
        //----------------------------------------------------------------------
        /** Возвращает название тега. */
        inline const QString& name() const { return _name; }

        /** Возвращает список тегов, связанных с категорией. */
        inline const QSet<TagPtr>& tags() const { return _tags; }

        //----------------------------------------------------------------------
        // SET
        //----------------------------------------------------------------------
        void setName(const QString &name);

        /** Устанавливает список тегов категории. */
        void setTags(const QSet<TagPtr> &tags);

        /** Добавляет тег к категориям. */
        void addTag(const TagPtr &tag);

        /** Удаляет тег из категории. */
        void removeTag(const TagPtr &tag);

    private:
        /** Вся работа через умные указатели. */
        using AbstractRecord::AbstractRecord;
        friend class QSharedPointer<Category>;

    signals:
        void nameChanged();
        void tagsChanged();

    private:
        QString _name;
        QSet<TagPtr> _tags;
};
} // namespace jetcrypto
