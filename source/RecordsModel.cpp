/// @author M. A. Serebrennikov
#include "Record.h"
#include "RecordsMaster.h"
#include "RecordsModel.h"

using namespace sp;

RecordsModel::RecordsModel(QObject *parent)
    : QAbstractListModel(parent)
{
    connect(this, &RecordsModel::startLazyLoad
           ,this, &RecordsModel::lazyLoad, Qt::QueuedConnection);
}

//------------------------------------------------------------------------------
void RecordsModel::setTag(const QString &tag)
{
    Q_ASSERT(!tag.isEmpty());

    if (_tag != tag) {
        _tag = tag;

        reloadRecords();
    }
}

//------------------------------------------------------------------------------
void RecordsModel::setLoadLimit(int loadCount)
{
    Q_ASSERT(loadCount > 0);

    if (_loadLimit != loadCount) {
        _loadLimit = loadCount;
        emit loadLimitChanged();
    }
}

//------------------------------------------------------------------------------
int RecordsModel::rowCount(const QModelIndex &) const
{
    return _records.count();
}

//------------------------------------------------------------------------------
QVariant RecordsModel::data(const QModelIndex &index, int role) const
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
void RecordsModel::reloadRecords()
{
    emit beginResetModel();
    _allLoaded = false;
    _records = RecordsMasterI.get(_tag, _loadLimit);
    emit endResetModel();

    if (_records.count() < _loadLimit) {
        _allLoaded = true;
    }
}

//------------------------------------------------------------------------------
void RecordsModel::setLazyLoadThreshold(int lazyLoadThreshold)
    {
        if (_lazyLoadThreshold != lazyLoadThreshold) {
        _lazyLoadThreshold = lazyLoadThreshold;
        emit lazyLoadThresholdChanged();
    }
}

//------------------------------------------------------------------------------
void RecordsModel::lazyLoad()
{
    Q_ASSERT(_records.count()); // Ленивая загрузка загружается только после загрузки хоть одной записи. Иначе должна работать reloadRecords.

    auto newRecords = RecordsMasterI.get(_tag, _loadLimit, _records.count());
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
