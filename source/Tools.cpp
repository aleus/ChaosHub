/// @author M. A. Serebrennikov
#include "Tools.h"

#include <QDateTime>

using namespace sp;
QUuid tools::createSeqUuid()
{
    QUuid result = QUuid::createUuid();
    quint64 curtime = QDateTime::currentMSecsSinceEpoch();

    // Для последовательного UUID нужны последние 6 значащих байт временной метки
    #if Q_BYTE_ORDER == Q_LITTLE_ENDIAN
        memcpy(reinterpret_cast<char*>(&result), reinterpret_cast<char*>(&curtime)+2, 4);
        memcpy(reinterpret_cast<char*>(&result)+4, reinterpret_cast<char*>(&curtime), 2);
    #else
        memcpy(reinterpret_cast<char*>(&result), reinterpret_cast<char*>(&curtime)+2, 6);
    #endif

    return result;
}
