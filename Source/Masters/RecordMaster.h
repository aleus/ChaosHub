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
 * @brief Синглетон релизует CRUD-механику для Record.
 *
 * @details Записи Record хранятся в Storage. Сам синглетон не хранит
 * в оперативной памяти объекты Record, а лишь создаёт их передаёт управления
 * ими наружу. Record по своей сути является временным объектом, который
 * используются в GUI, к примеру внутри модели RecordModel.
 *
 * @sa TextNoteMaster, Storage
 ****************************************************************************/
class RecordMaster: public QObject
{
    Q_OBJECT

    public:
        /** Возвращает синглетон. */
        static RecordMaster& instance();

        //--------------------------------------------------------------------
        // GET
        //--------------------------------------------------------------------
        /** Возвращает список записей по тегу, загруженных из хранилища. */
        QVector<RecordPtr> get(const QString &tag, int limit, int offset = 0);

        /** Возвращает название таблицы, в которой хранятся записи. */
        inline const QString &tableName() const { return _tableName; }

        //--------------------------------------------------------------------
        // SPECIAL
        //--------------------------------------------------------------------
        /** Добавляет запись в хранилище. */
        void add(const RecordPtr &record);

        /** Удаляет запись из хранилища и приложения. */
        void remove(const RecordPtr &record);
        void remove(const QVector<RecordPtr> &records);
        void remove(const QVector<QUuid> &records);
        Q_INVOKABLE void remove(Record *recordRaw);

        /** Подготавливает хранилище для дальнейшей работы (создаёт таблицы). */
        void prepareStorage() const;

    private:
        RecordMaster() = default;

        /** Загружает из хранилища содержимое записи в зависиомсти от его типа. */
        RecordContentPtr loadContent(Record::Type type, int rowid);

    signals:
        void recordRemoved(RecordPtr record) const;
        void recordCreated(RecordPtr record) const;

    private:
        const QString _tableName = "Records";
};

} // namespace sp
