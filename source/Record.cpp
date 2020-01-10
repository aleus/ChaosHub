/// @author M. A. Serebrennikov
#include "Record.h"
#include "Tools.h"

#include <QDateTime>
#include <QQmlEngine>

using namespace sp;

Record::Record(Record::Type type, const RecordContentPtr &content)
    : _id(tools::createUuidSeq())
    , _type(type)
    , _content(content)
    , _date(QDateTime::currentDateTime())
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

//------------------------------------------------------------------------------
Record::Record(const QUuid &id, Record::Type type, const RecordContentPtr &content, const QDateTime &date)
    : _id(id)
    , _type(type)
    , _content(content)
    , _date(date)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

//------------------------------------------------------------------------------
QString Record::dateStr() const
{
    return _date.toString();
}
