#pragma once
#include <cmath>

float dist(float x1, float y1, float x2, float y2)
{
    return sqrtf(fabs(x1 - x2) * fabs(x1 - x2) + fabs(y1 - y2) * fabs(y1 - y2));
}
