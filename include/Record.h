/// @author M. A. Serebrennikov
#pragma once

#include "PointersTypedef.h"

#include <QDateTime>
#include <QObject>
#include <QString>
#include <QUuid>

namespace sp {

/***********************************************************************//**
 * @brief Класс записи, отображаемой в GUI.
 *
 * @details Запись может содержать один из типов данных:
 * текстовая заметка (TextNote), изображение (ImageNote), ссылка на web-страницу
 * (Bookmark) и др. Записи подгружаются по мере прокрутки списка заметок
 * пользователем в RecordsModel из Storage.
 *
 * @sa RecordsModel, Storage
 ****************************************************************************/
class Record: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString dateStr READ dateStr CONSTANT)
    Q_PROPERTY(Type type READ type CONSTANT)

    public:
        /** Тип содержимого заметки. */
        enum Type {
            TextType = 0,
            UrlType = 1,
            ImageType = 2,
        };
        Q_ENUM(Type)

        //----------------------------------------------------------------------
        // Get
        //----------------------------------------------------------------------
        /** Возвращает id-шник записи. */
        inline const QUuid& id() const { return _id; }

        /** Возвращает тип записи. */
        inline Type type() const { return _type; }

        /** Возвращает указатель на содержимое записи. */
        inline const RecordContentPtr& content() const { return _content; }

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
