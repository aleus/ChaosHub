/// @author M. A. Serebrennikov
#include "TagModel.h"
#include "Tag.h"

#include <QHash>

using namespace sp;

TagModel::TagModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

//------------------------------------------------------------------------------
int TagModel::rowCount(const QModelIndex &/*parent*/) const
{
    return _items.count();
}

//------------------------------------------------------------------------------
QVariant TagModel::data(const QModelIndex &index, int role) const
{
    Q_ASSERT(index.row() >= 0);
    if (!index.isValid() || index.row() >= _items.count()) {
        return QVariant();
    }

    switch (role) {
        case 0:
            return QVariant::fromValue(_items.value(index.row()).data());

        default:
            Q_ASSERT(false);
            return QVariant();
    }
}

//------------------------------------------------------------------------------
QHash<int, QByteArray> TagModel::roleNames() const
{
    QHash<int, QByteArray> result;
    result.insert(0, QByteArrayLiteral("tag"));
    return result;
}
