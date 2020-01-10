/// @author M. A. Serebrennikov
#include "RecordContent.h"

#include <QQmlEngine>

using namespace sp;

RecordContent::RecordContent()
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

//------------------------------------------------------------------------------
RecordContent::RecordContent(int rowid)
    : _rowid(rowid)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

//------------------------------------------------------------------------------
void RecordContent::setRowid(int rowid)
{
    _rowid = rowid;
}
