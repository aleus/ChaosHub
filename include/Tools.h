/// @author M. A. Serebrennikov
#pragma once

#include <QUuid>
#include <functional>

namespace sp {
namespace tools {
/**
 * @brief Создаёт последовательный UUID.
 *
 * @details Последовательный UUID нужен для правильной работы
 * primary key в БД. Он генерируется путём наложения
 * временой метки на UUID, сгенерированный методом DCE+Random.
 *
 * @sa https://en.wikipedia.org/wiki/Universally_unique_identifier#As_database_keys
 */
QUuid createUuidSeq();

/** Возвращает количество точек в логическом пикселе */
double dp();

/** Возвращает количество пикселей в мм экрана. */
double mm();
} // namespace tools {

/**
 * @brief Вспомогательный класс для отложенного вызова функции.
 * @details Когда нужно по выходу из блока вызвать некую функцию,
 * можно использовать следующий макрос defer. Обычно это нужно,
 * когда есть несколько точек выхода из блока.
 * @code
    int main(int , char *[])
    {
        defer([&](){ qDebug("defer 1"); }());
        defer(qDebug("defer 2"));
        defer(qDebug("defer 3"));
        return 0;
    }
    // Вывод:
    // defer 3
    // defer 2
    // defer 1
 * @endcode
 */
#define defer(fn) Deferrer CONCAT(__defer__, __LINE__) { [&]() { fn; } }

#define CONCAT_(a, b) a ## b
#define CONCAT(a, b) CONCAT_(a,b)
class Deferrer
{
    public:
        explicit Deferrer(std::function<void()> &&func);
        ~Deferrer() { _func(); }

    private:
        std::function<void()> _func;
};

} // namespace sp
