/// @author M. A. Serebrennikov
#pragma once

#include "PointersTypedef.h"
#include "RecordContent.h"

#include <QDateTime>
#include <QString>
#include <QUuid>

namespace sp {

/***********************************************************************//**
 * @brief Класс записи для GUI.
 *
 * @details Record - это универсальный контейнер для пользовательской записи.
 * апись может содержать один из типов данных:
 * текстовая заметка (TextNote), изображение (ImageNote), ссылка на web-страницу
 * (Bookmark) и др. После создания записи тип записи не может быть заменен.
 *
 * @sa RecordsModel, Storage
 ****************************************************************************/
class Record: public QObject
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

        /**
         * Конструктор для создания новой записи. Генерируется новый id,
         * время записи указывается текущее
         */
        Record(Type type, const RecordContentPtr &content);

        /** Конструктор для загрузки записи. */
        Record(const QUuid &id, Type type, const RecordContentPtr &content, const QDateTime &date);

        /** Копирующего конструктора не должно быть, вся передача через RecordPtr. */
        Record(const Record &record) = delete;

        /** Перемещающего конструктора не должно быть, вся передача через RecordPtr. */
        Record(Record &&record) = delete;

        //----------------------------------------------------------------------
        // Get
        //----------------------------------------------------------------------
        /** Возвращает id-шник записи. */
        inline const QUuid& id() const { return _id; }

        /** Возвращает тип записи. */
        inline Type type() const { return _type; }

        /** Возвращает указатель на содержимое записи. */
        inline const RecordContentPtr& content() const { return _content; }

        /** Возвращает голый указатель на содержимое записи. Используется в QML */
        inline RecordContent* contentRaw() const { return _content.data(); }

        /** Возвращает дату создания записи. */
        inline const QDateTime& date() const { return _date; }

        /** Возвращает дату создания записи в виде строки. */
        QString dateStr() const;

    private:
        /** Загружает данные записи из хранилища. */
        void load();

    private:
        QUuid _id;
        Type _type;
        RecordContentPtr _content;
        QDateTime _date;
};

} // namespace sp
