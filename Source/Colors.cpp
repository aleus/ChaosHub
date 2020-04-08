/// @author M. A. Serebrennikov
#include "Colors.h"

using namespace sp;

Colors &Colors::instance()
{
    static Colors result;
    return result;
}
