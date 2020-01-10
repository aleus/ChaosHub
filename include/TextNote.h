/// @author M. Serebrennikov
#pragma once

#include "PointersTypedef.h"
#include "RecordContent.h"

#include <QString>

namespace sp {

/***************************************************************************//**
 * @brief Текстовая заметка, хранится в объекте класса Record.
 ******************************************************************************/
class TextNote: public RecordContent
{
    Q_OBJECT

    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

    public:
        // TODO Возможно, нужно убрать в private
        TextNote(const QString &text);
        TextNote(int rowid, const QString &text);

        /** Возвращает текст заметки. */
        inline QString text() const { return _text; }

        /** Устанавливает текст заметки. */
        void setText(QString text);

    signals:
        void textChanged();

    private:
        QString _text;
};

/***************************************************************************//**
 * @brief Класс для создания текстовой заметки из QMl.
 ******************************************************************************/
class TextNoteMaster: public QObject
{
    Q_OBJECT

    public:
        TextNoteMaster() = default;

        /** Создаёт новую текстовую заметку и отправляет в хранилище. */
        Q_INVOKABLE static void create(const QString &text);

        /** Загружает текстовую заметку из хранилища. */
        static RecordContentPtr load(int rowid);
};

} // namespace sp
