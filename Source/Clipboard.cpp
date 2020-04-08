/// @author M. A. Serebrennikov
#include "Clipboard.h"

#include <QClipboard>
#include <QApplication>

using namespace sp;

Clipboard &Clipboard::instance()
{
    static Clipboard result;
    return result;
}

//------------------------------------------------------------------------------
Clipboard::Clipboard()
{
    connect(qApp->clipboard(), &QClipboard::changed ,this, &Clipboard::changed);
}

//------------------------------------------------------------------------------
QString Clipboard::text() const
{
    return qApp->clipboard()->text();
}

//------------------------------------------------------------------------------
void Clipboard::setText(const QString &text)
{
    if (qApp->clipboard()->text() != text) {
        qApp->clipboard()->setText(text);
    }
}
