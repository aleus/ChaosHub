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
    Q_PROPERTY(QString textRendered READ textRendered NOTIFY textChanged)

    public:
        // TODO Возможно, нужно убрать в private
        TextNote(const QString &text);
        TextNote(int rowid, const QString &text);

        /** Возвращает текст заметки. */
        inline const QString& text() const { return _text; }

        /** Возвращает текст заметки со вставленными тегами отображения. */
        QString textRendered() const;

        /** Устанавливает текст заметки. */
        void setText(QString text);

    signals:
        void textChanged();

    private:
        QString _text;
};

} // namespace sp
