/// @author M. A. Serebrennikov
#pragma once

#include "PointersTypedef.h"
#include "Record.h"

#include <QObject>
#include <QVector>

namespace sp {

/** Быстрое обращение к синглетону. */
#define RecordMasterI RecordMaster::instance()

/*************************************************************************//**
 * @brief Синглетон, работающий с записями Record в Storage.
 *
 * @details Класс умеет загружать, добавлять и удалять записи из Storage.
 * В то же время синглетон не хранит объекты Record. Они по своей сути
 * являются временным объектами, которые используются в GUI (к примеру
 * внутри модели RecordModel).
 ****************************************************************************/
class RecordMaster: public QObject
{
    Q_OBJECT

    public:
        /** Возвращает синглетон. */
        static RecordMaster& instance();

        //--------------------------------------------------------------------
        // Get
        //--------------------------------------------------------------------
        /** Возвращает список записей по тегу, загруженных из хранилища. */
        QVector<RecordPtr> get(const QString &tag, int limit, int offset = 0);

        /** Возвращает название таблицы, в которой хранятся записи. */
        inline const QString &tableName() const { return _tableName; }

        //--------------------------------------------------------------------
        // Special
        //--------------------------------------------------------------------
        /** Добавляет запись в хранилище. */
        void append(const RecordPtr &record);

        /** Удаляет запись из хранилища и приложения. */
        void remove(const RecordPtr &record);
        void remove(const QVector<RecordPtr> &records);
        void remove(const QVector<QUuid> &records);

        /** Подготавливает хранилище для дальнейшей работы (создаёт таблицы). */
        void prepareStorage() const;

    private:
        RecordMaster() = default;

        /** Загружает из хранилища содержимое записи в зависиомсти от его типа. */
        RecordContentPtr loadContent(Record::Type type, int rowid);

        /** Удаляет запись из хранилища. Используется в QML. */
        Q_INVOKABLE void removeRaw(Record *recordRaw);

    signals:
        void recordRemoved(RecordPtr record) const;
        void recordCreated(RecordPtr record) const;

    private:
        const QString _tableName = "Records";
};

} // namespace sp
