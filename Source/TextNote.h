/// @author M. Serebrennikov
#pragma once

#include "PointersTypedef.h"
#include "RecordContent.h"

#include <QString>

class QQuickTextDocument;

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
        inline QString text() const { return _text.trimmed(); }

        /** Устанавливает текст заметки. */
        void setText(QString text);

        //--------------------------------------------------------------------
        // Override
        //--------------------------------------------------------------------
        bool remove() override;

    signals:
        void textChanged();

    private:
        QString _text;
};

} // namespace sp
