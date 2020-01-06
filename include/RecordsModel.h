/// @author M. A. Serebrennikov
#pragma once

#include "ChaosTypedef.h"

#include <QAbstractListModel>
#include <QVector>

namespace sp {

/*************************************************************************//**
 * @brief Модель списка записей заданного тега (категории).
 * @details При установки
 ****************************************************************************/
class RecordsModel: public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(QString tag READ tag WRITE setTag NOTIFY tagChanged)
    Q_PROPERTY(int loadLimit READ loadLimit WRITE setLoadLimit NOTIFY loadLimitChanged)
    Q_PROPERTY(int lazyLoadThreshold READ lazyLoadThreshold WRITE setLazyLoadThreshold NOTIFY lazyLoadThresholdChanged)

    public:
        RecordsModel(QObject *parent = nullptr);

        //--------------------------------------------------------------------
        // Get
        //--------------------------------------------------------------------
        /** Возвращает тег/категория записей в модели. */
        inline const QString& tag() const { return _tag; }

        /** Возвращает предельное количество одновременно загружаемых записей */
        inline int loadLimit() const { return _loadLimit; }

        /**
         * Возвращает количество записей до конца массива уже загруженных
         * после начала просмотра которых запускается подгрузка новых записей.
         */
        inline int lazyLoadThreshold() const { return _lazyLoadThreshold; }

        //----------------------------------------------------------------------
        // Set
        //----------------------------------------------------------------------
        /**
         * @brief Устанавливает тег записей в модели.
         *
         * @details После установки нового тега, загружаются новые записи из
         * хранилища.
         */
        void setTag(const QString &tag);

        /** Устанавливает ограничение на количество одновременно загружаемых записей */
        void setLoadLimit(int loadCount);

        /**
         * Устанавливает количество записей до конца массива уже загруженных
         * после начала просмотра которых запускается подгрузка новых записей.
         */
        void setLazyLoadThreshold(int lazyLoadThreshold);

        //----------------------------------------------------------------------
        // Override
        //----------------------------------------------------------------------
        int rowCount (const QModelIndex & parent = QModelIndex()) const override;
        QVariant data (const QModelIndex & index, int role = Qt::DisplayRole) const override;

    private:
        /** Заново загружает записи. */
        void reloadRecords();

    private slots:
        /** Подгружает записи из БД при пролистывании списка ближе к концу. */
        void lazyLoad();

    signals:
        void tagChanged() const;
        void loadLimitChanged() const;
        void lazyLoadThresholdChanged() const;
        void startLazyLoad() const;
        void allLoaded() const;

    private:
        QString _tag;
        QVector<RecordPtr> _records;
        int _loadLimit = 50;
        int _lazyLoadThreshold = 10;
        bool _allLoaded = false;
};

} // namespace sp
