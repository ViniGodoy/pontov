#ifndef BOX_H_INCLUDED
#define BOX_H_INCLUDED

#include "Vector3D.h"

namespace math
{
    /**
        A box is a 3D rectangular area that is parallel to the axis
    */
    class Box
    {
        public:
            Box();
            Box(const Vector3D& _min, const Vector3D& _max);
            Box(float x1, float y1, float z1, float x2, float y2, float z2);

            const Vector3D& getMin() const;
            const Vector3D& getMax() const;
            Vector3D getCenter() const;

            bool intersects(const Box& other, Box* boxIntersect = 0) const;
            bool contains(const Vector3D point) const;

            void set(float x1, float y1, float z1, float x2, float y2, float z2);
            void set(const Vector3D& _min, const Vector3D& _max);

            void move(const Vector3D& position);
            Box moved(const Vector3D& position) const;


        private:
            Vector3D min;
            Vector3D max;
    };
}


#endif // BOX_H_INCLUDED
