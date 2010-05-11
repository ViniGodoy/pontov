#include <algorithm>
#include "MathUtil.h"

void math::padValue(float &value, float min, float max)
{
    value = std::max(value, min);
    value = std::min(value, max);
}
