/// @author M. A. Serebrennikov
#pragma once

#include "PointersTypedef.h"

#include <QObject>

namespace sp {

/** Быстрое обращение к синглетону. */
#define TagMasterI TagMaster::instance()

/*************************************************************************//**
 * @brief Синглетон, работающий с тегами Tag в Storage.
 *
 * @details Класс умеет загружать, добавлять и удалять теги из Storage.
 * В то же время синглетон не хранит объекты Tag. Они по своей сути
 * являются временным объектами, которые используются в GUI (к примеру
 * внутри модели TagModel).
 ****************************************************************************/
class TagMaster: public QObject
{
    Q_OBJECT

    public:
        /** Возвращает синглетон. */
        static TagMaster& instance();

        //--------------------------------------------------------------------
        // Get
        //--------------------------------------------------------------------
        /** Возвращает список тегов из хранилища. */
        QVector<TagPtr> get();

        /** Возвращает название таблицы, в которой хранятся теги. */
        inline const QString &tableName() const { return _tableName; }

        /** Возвращает название таблицы, в которой хранится сопоставление тегов и записей. */
        inline const QString &tableNameMath() const { return _tableNameMath; }

        //--------------------------------------------------------------------
        // Special
        //--------------------------------------------------------------------
        /** Добавляет запись в хранилище. */
        void append(const TagPtr &tag);

        /** Удаляет запись из хранилища и приложения. */
        void remove(const TagPtr &tag);
        void remove(const QVector<TagPtr> &tags);
        void remove(const QVector<QUuid> &tags);

        /** Подготавливает хранилище для дальнейшей работы (создаёт таблицы). */
        void prepareStorage() const;

    private:
        TagMaster() = default;

        /** Удаляет запись из хранилища. Используется в QML. */
        Q_INVOKABLE void remove(Tag *tagRaw);

    signals:
        void tagCreated(TagPtr tag) const;
        void tagRemoved(TagPtr tag) const;

    private:
        const QString _tableName = "Tags";
        const QString _tableNameMath = "RecordsTags";
};

} // namespace sp
