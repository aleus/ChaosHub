/// @author M. A. Serebrennikov
#pragma once

#include <QSharedPointer>

namespace sp {

class Record;
class RecordContent;

using RecordPtr = QSharedPointer<Record>;
using RecordContentPtr = QSharedPointer<RecordContent>;

} // namespace sp
