/// @author M.Serebrennikov
#include "Category.h"

#include <QQmlEngine>

using namespace sp;

//------------------------------------------------------------------------------
void Category::setName(const QString &name)
{
    if (_name != name) {
        _name = name;
        emit nameChanged();
    }
}

//------------------------------------------------------------------------------
void Category::setTags(const QSet<TagPtr> &tags)
{
    if (_tags != tags) {
        _tags = tags;
        emit tagsChanged();
    }
}

//------------------------------------------------------------------------------
void Category::addTag(const TagPtr &tag)
{
    Q_ASSERT(!_tags.contains(tag));
    _tags.insert(tag);
    emit tagsChanged();
}

//------------------------------------------------------------------------------
void Category::removeTag(const TagPtr &tag)
{
    Q_ASSERT(_tags.contains(tag));
    _tags.remove(tag);
    emit tagsChanged();
}
