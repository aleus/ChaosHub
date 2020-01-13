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

} // namespace sp
