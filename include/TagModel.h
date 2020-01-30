/// @author M. A. Serebrennikov
#pragma once

#include "PointersTypedef.h"

#include <QAbstractListModel>
#include <QVector>

namespace sp {

/*************************************************************************//**
 * @brief Класс модели списка тегов.
 *
 * @details Модель используется в QML компоненте TagList. Модель загружается
 * из Storage и хранится в кешированном виде.
 ****************************************************************************/
class TagModel: public QAbstractListModel
{
    Q_OBJECT

    public:
        TagModel(QObject *parent = nullptr);

        //----------------------------------------------------------------------
        // Override
        //----------------------------------------------------------------------
        int rowCount (const QModelIndex & parent = QModelIndex()) const override;
        QVariant data (const QModelIndex & index, int role = Qt::DisplayRole) const override;
        QHash<int, QByteArray> roleNames() const override;

    private:
        QVector<TagPtr> _items;
};

} // namespace sp
