/// @author M. A. Serebrennikov
#pragma once

#include <QSharedPointer>

namespace sp {

class Record;
class RecordContent;
class Tag;

using RecordPtr = QSharedPointer<Record>;
using RecordContentPtr = QSharedPointer<RecordContent>;
using TagPtr = QSharedPointer<Tag>;
using TagWeak = QWeakPointer<Tag>;

} // namespace sp
