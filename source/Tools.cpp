/// @author M. A. Serebrennikov
#include "Tools.h"

#include <QDateTime>
#include <QApplication>
#include <QScreen>

using namespace sp;
QUuid tools::createUuidSeq()
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

//------------------------------------------------------------------------------
double tools::dp()
{
    #if defined(Q_OS_MAC)
        static double const standardDPI = 72;
    #elif defined(Q_OS_WIN)
        static double const standardDPI = 96;
    #else
        static double const standardDPI = qApp->screens().first()->logicalDotsPerInch();
    #endif

    static const double result = qApp->screens().first()->logicalDotsPerInch() / standardDPI;
    return result;
}

//------------------------------------------------------------------------------
double tools::mm()
{
    static const double mmInInch = 25.4;
    static double result =  qApp->screens().first()->physicalDotsPerInch()/mmInInch;
    return result;
}
