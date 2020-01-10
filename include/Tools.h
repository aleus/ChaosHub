/// @author M. A. Serebrennikov
#pragma once

#include <QUuid>

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

} // namespace sp
