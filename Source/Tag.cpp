/// @author M. A. Serebrennikov
#include "Tag.h"

#include <QQmlEngine>

using namespace sp;

Tag::Tag(const QUuid &parentId)
    : _parentId(parentId)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

//------------------------------------------------------------------------------
Tag::Tag(const QString &name, const QUuid &id, const QUuid &parentId)
    : _name(name)
    , _id(id)
    , _parentId(parentId)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

//------------------------------------------------------------------------------
void Tag::setName(const QString &name)
{
    if (_name != name) {
        _name = name;
        emit nameChanged();
    }
}

//------------------------------------------------------------------------------
void Tag::setParentId(const QUuid &parentId)
{
    if (_parentId != parentId) {
        _parentId = parentId;
    }
}
