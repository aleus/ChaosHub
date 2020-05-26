/// @author M. A. Serebrennikov
#pragma once

#include "AbstractRecord.h"
#include "PointersTypedef.h"
#include "RecordContent.h"

#include <QDateTime>
#include <QString>
#include <QUuid>

namespace sp {

/***********************************************************************//**
 * @brief Класс записи для GUI.
 *
 * @details Record - это универсальный контейнер для пользовательских записей.
 * По своей сути является временным объектом, который используются в GUI,
 * к примеру внутри модели RecordModel.
 * Запись может содержать один из типов данных:
 * - текстовая заметка (TextNote),
 * - изображение (ImageNote),
 * - ссылка на web-страницу (Bookmark) ,
 * - другое...
 *
 * Для создания новых объектов класса Record используются конкретные мастера:
 * TextNoteMaster, ImageNoteMaster, LinkNoteMaster и т.д. После создания
 * записи тип записи не может быть заменен.
 *
 * @sa RecordsModel, RecordContent, Tag
 ****************************************************************************/
class Record : public AbstractRecord, public QEnableSharedFromThis<Record>
{
    Q_OBJECT

    Q_PROPERTY(QString dateStr READ dateStr CONSTANT)
    Q_PROPERTY(Type type READ type CONSTANT)
    Q_PROPERTY(RecordContent* content READ contentRaw CONSTANT)

    public:
        /** Тип содержимого заметки. */
        // TODO Заменить на механизм регистрации типов
        enum Type {
            TextType = 0,
            UrlType = 1,
            ImageType = 2,
        };
        Q_ENUM(Type)

        //----------------------------------------------------------------------
        // GET
        //----------------------------------------------------------------------
        /** Возвращает id-шник записи. */
        inline const QUuid& id() const { return _id; }

        /** Возвращает тип записи. */
        inline Type type() const { return _type; }

        /** Возвращает указатель на содержимое записи. */
        inline const RecordContentPtr& content() const { return _content; }

        /** Возвращает дату создания записи. */
        inline const QDateTime& date() const { return _date; }

        /** Возвращает дату создания в виде строки. */
        QString dateStr() const;

        //----------------------------------------------------------------------
        // SET
        //----------------------------------------------------------------------
        void setType(Type type);
        inline Record* type(Type type) { setType(type); return this; }

        void setContent(const RecordContentPtr &content);
        inline Record* content(const RecordContentPtr &content) { setContent(content); return this; }

        void setDate(const QDateTime &date);
        inline Record* date(const QDateTime &date) { setDate(date); return this; }

    private:
        friend class QSharedPointer<Record>;
        using AbstractRecord::AbstractRecord;

        /** Возвращает голый указатель на содержимое записи. Используется в QML */
        inline RecordContent* contentRaw() const { return _content.data(); }

    private:
        QUuid _id;
        Type _type;
        RecordContentPtr _content;
        QDateTime _date;
};

} // namespace sp
