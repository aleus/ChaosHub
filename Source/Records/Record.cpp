/// @author M. A. Serebrennikov
#include "Record.h"
#include "Tools.h"

#include <QDateTime>
#include <QQmlEngine>

using namespace sp;

QString Record::dateStr() const
{
    return _date.toString("hh:mm, d MMM yyyy");
}

//------------------------------------------------------------------------------
void Record::setType(Record::Type type)
{
    _type = type;
}

//------------------------------------------------------------------------------
void Record::setContent(const RecordContentPtr &content)
{
    _content = content;
}

//------------------------------------------------------------------------------
void Record::setDate(const QDateTime &date)
{
    _date = date;
}
