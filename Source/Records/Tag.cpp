/// @author M. A. Serebrennikov
#include "Tag.h"

using namespace sp;

void Tag::setName(const QString &name)
{
    if (_name != name) {
        _name = name;
        emit nameChanged();
    }
}
