/// @author M. A. Serebrennikov
#include "RecordHelper.h"

using namespace sp;

// static ----------------------------------------------------------------------
RecordHelper &RecordHelper::instance()
{
    static RecordHelper result;
    return result;
}

//------------------------------------------------------------------------------
QString RecordHelper::formatUrl(const QString &url) const
{
    if (url.startsWith("http://") || url.startsWith("https://")) {
        return url;
    } else {
        // TODO Тут нужна обработка всех кривых случаев составления url'а
        QString result = "https://" + url;
        return result;
    }
}
