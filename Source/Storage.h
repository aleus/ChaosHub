/// @author M. A. Serebrennikov
#pragma once

#include <QObject>
#include <QString>
#include <optional>

struct sqlite3;
struct sqlite3_stmt;

namespace sp {

/** Быстрое обращение к синглетону. */
#define StorageI Storage::instance()

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

        /**
         * @brief Возвращает идентификатор из проведённого запроса.
         *
         * @param stmt структура состояния SQLite-запроса
         * @param columNumber номер столбца из запроса
         */
        static std::optional<QUuid> getId(sqlite3_stmt *stmt, int columnNumber);

        /**
         * @brief Возвращает строку из проведённого запроса.
         *
         * @param stmt структура состояния SQLite-запроса
         * @param columNumber номер столбца из запроса
         */
        static QString getString(sqlite3_stmt *stmt, int columnNumber);

        /**
         * @brief Возвращает int из проведённого запроса.
         *
         * @param stmt структура состояния SQLite-запроса
         * @param columNumber номер столбца из запроса
         */
        static int getInt(sqlite3_stmt *stmt, int columnNumber);

        /**
         * @brief Возвращает значение перечисления из проведённого запроса.
         *
         * @param stmt структура состояния SQLite-запроса
         * @param columNumber номер столбца из запроса
         * @tparam type тип перечисления для привидения из int.
         */
        template<class type>
        static inline type getEnum(sqlite3_stmt *stmt, int columnNumber) { return static_cast<type>(getInt(stmt, columnNumber)); }

        /**
         * @brief Возвращает строку из проведённого запроса.
         *
         * @param stmt структура состояния SQLite-запроса
         * @param columNumber номер столбца из запроса
         */
        static QDateTime getDate(sqlite3_stmt *stmt, int columnNumber);

        //--------------------------------------------------------------------
        // Special
        //--------------------------------------------------------------------
        /** Открывает или создаёт БД с заметками. */
        void openDb(const QString &filePath);

        /**
         * @brief Создаёт таблицу по запросу.
         *
         * TODO Заменить на нормальный механику запросов
         */
        void createTable(const QString &query);

        /** Создаёт необходимые таблицы для заметок. */
        void prepareStorage();

    private:
        Storage();
        Storage(const Storage &) = delete;
        Storage(Storage &&) = delete;
        ~Storage();

    private:
        sqlite3 *_db = nullptr;
};

} // namespace sp
