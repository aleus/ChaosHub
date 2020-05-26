/// @author M.Serebrennikov
#include "AbstractRecord.h"
#include "Tools.h"

#include <QQmlEngine>

using namespace sp;

AbstractRecord::AbstractRecord()
    : _id(tools::createUuidSeq())
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

//------------------------------------------------------------------------------
AbstractRecord::AbstractRecord(const QUuid &id)
    : _id(id)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}
