/* Vinícius Godoy de Mendonça. */
#ifndef MATHUTIL_H_INCLUDED
#define MATHUTIL_H_INCLUDED

#include <cmath>

namespace math
{
    static const double PI = 3.14159265358979323846;
    static const double ONE_DEGREE = PI / 180.0;
    static const double E = 2.7182818284590452354;

    inline double toDegrees(double angrad)
    {
        return angrad * 180.0 / PI;
    }

    inline float toDegrees(float angrad)
    {
        return static_cast<float>(angrad * 180.0f / PI);
    }

    inline float toDegrees(int angrad)
    {
        return toDegrees(static_cast<float>(angrad));
    }

    inline double toRadians(double angdeg)
    {
        return static_cast<float>(angdeg / 180.0 * PI);
    }

    inline float toRadians(float angdeg)
    {
        return static_cast<float>(angdeg / 180.0f * PI);
    }

    inline float toRadians(int angdeg)
    {
        return toRadians(static_cast<float>(angdeg));
    }

    void padValue(float &value, float min, float max);
}

#endif // MATHUTIL_H_INCLUDED
