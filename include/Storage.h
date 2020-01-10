/// @author M. A. Serebrennikov
#pragma once

#include <QObject>
#include <QString>

struct sqlite3;

namespace sp {

/** Быстрое обращение к синглетону. */
#define StorageI sp::Storage::instance()

/***********************************************************************//**
 * @brief Синглетон для доступа к хранилищу с данными хаба.
 * @details Данные хранятся в БД SQLite. На момент прототипирования класс
 * предоставляет прямой доступ к БД.
 ****************************************************************************/
class Storage: public QObject
{
    Q_OBJECT

    public:
        static Storage& instance();

        //--------------------------------------------------------------------
        // Get
        //--------------------------------------------------------------------
        /** Возвращает указатель на БД. */
        inline sqlite3* db() const { return _db; }

        //--------------------------------------------------------------------
        // Special
        //--------------------------------------------------------------------
        /** Открывает или создаёт БД с заметками. */
        void openDb(const QString &filePath);

    private:
        Storage();
        Storage(const Storage &) = delete;
        Storage(Storage &&) = delete;
        ~Storage();

        /** Создаёт необходимые таблицы для заметок. */
        void prepareDb();

    private:
        sqlite3 *_db = nullptr;
};

} // namespace sp
