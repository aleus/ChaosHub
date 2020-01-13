/// @author M. A. Serebrennikov
#include "Record.h"
#include "RecordMaster.h"
#include "RecordModel.h"

#include <QDebug>

using namespace sp;

RecordModel::RecordModel(QObject *parent)
    : QAbstractListModel(parent)
{
    connect(this, &RecordModel::startLazyLoad
           ,this, &RecordModel::lazyLoad, Qt::QueuedConnection);

    connect(&RecordMasterI, &RecordMaster::recordCreated
           ,this, &RecordModel::onRecordCreated, Qt::QueuedConnection);
}

//------------------------------------------------------------------------------
void RecordModel::setTag(const QString &tag)
{
    Q_ASSERT(!tag.isEmpty());

    if (_tag != tag) {
        _tag = tag;
        reloadRecords();
        emit tagChanged();
    }
}

//------------------------------------------------------------------------------
void RecordModel::setLoadLimit(int loadCount)
{
    Q_ASSERT(loadCount > 0);

    if (_loadLimit != loadCount) {
        _loadLimit = loadCount;
        emit loadLimitChanged();
    }
}

//------------------------------------------------------------------------------
int RecordModel::rowCount(const QModelIndex &) const
{
    return _records.count();
}

//------------------------------------------------------------------------------
QVariant RecordModel::data(const QModelIndex &index, int role) const
{
    Q_ASSERT_X(!_tag.isEmpty(), "RecordsModel", "Нужно установить тег для работы модели.");
    Q_ASSERT(index.row() >= 0);
    if (!index.isValid() || index.row() >= _records.count()) {
        return QVariant();
    }

    if (int countToEnd = _records.count() - index.row()
        ; !_allLoaded && countToEnd <= _lazyLoadThreshold)
    {
        emit startLazyLoad();
    }

    switch (role) {
        case 0:
            return QVariant::fromValue(_records.value(index.row()).data());

        default:
            Q_ASSERT(false);
            return QVariant();
    }
}

//------------------------------------------------------------------------------
QHash<int, QByteArray> RecordModel::roleNames() const
{
    QHash<int, QByteArray> result;
    result.insert(0, QByteArrayLiteral("record"));
    return result;
}

//------------------------------------------------------------------------------
void RecordModel::reloadRecords()
{
    emit beginResetModel();
    _allLoaded = false;
    _records = RecordMasterI.get(_tag, _loadLimit);
    emit endResetModel();

    if (_records.count() < _loadLimit) {
        _allLoaded = true;
    }
}

//------------------------------------------------------------------------------
void RecordModel::setLazyLoadThreshold(int lazyLoadThreshold)
    {
        if (_lazyLoadThreshold != lazyLoadThreshold) {
        _lazyLoadThreshold = lazyLoadThreshold;
        emit lazyLoadThresholdChanged();
    }
}

//------------------------------------------------------------------------------
void RecordModel::lazyLoad()
{
    Q_ASSERT(_records.count()); // Ленивая загрузка загружается только после загрузки хоть одной записи. Иначе должна работать reloadRecords.

    auto newRecords = RecordMasterI.get(_tag, _loadLimit, _records.count());
    if (!newRecords.count()) {
        _allLoaded = true;
        return;
    }

    emit beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _records.append(newRecords);
    emit endInsertRows();

    if (_records.count() < _loadLimit) {
        _allLoaded = true;
    }
}

//------------------------------------------------------------------------------
void RecordModel::onRecordCreated(RecordPtr record)
{
    emit beginInsertRows(QModelIndex(), 0, 0);
    _records.insert(0, record);
    emit endInsertRows();
}
