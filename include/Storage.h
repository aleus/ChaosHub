/// @author M. A. Serebrennikov
#pragma once

#include <QString>

struct sqlite3;

namespace sp {

/** Быстрое обращение к синглетону. */
#define StorageI Storage::instance()

/***********************************************************************//**
 * @brief Синглетон для доступа к хранилищу с данными хаба.
 * @details Данные хранятся в БД SQLite.
 ****************************************************************************/
class Storage
{
    public:
        static Storage& instance();

        //----------------------------------------------------------------------
        // Special
        //----------------------------------------------------------------------
        /** Открывает или создаёт БД с заметками. */
        void openDb(const QString &filePath);

        static void debug();

    private:
        Storage();
        Storage(const Storage &) = delete;
        Storage(Storage &&) = delete;

        /** Создаёт необходимые таблицы для заметок. */
        void prepareDb();

    private:
        sqlite3 *_db = nullptr;
};

} // namespace sp
