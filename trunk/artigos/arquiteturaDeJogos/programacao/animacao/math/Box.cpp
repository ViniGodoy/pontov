#include "Box.h"
#include <stdexcept>

using math::Box;
using math::Vector3D;

Box::Box() : min(0,0,0), max(1,1,1)
{
}

Box::Box(const Vector3D& _min, const Vector3D& _max)
{
    set(_min, _max);
}

Box::Box(float x1, float y1, float z1, float x2, float y2, float z2)
{
    set(x1, y1, z1, x2, y2, z2);
}

const Vector3D& Box::getMin() const
{
    return min;
}

const Vector3D& Box::getMax() const
{
    return max;
}

Vector3D Box::getCenter() const
{
    return (min + max) * 0.5f;
}

bool Box::intersects(const Box& other, Box* boxIntersect) const
{
	// Check for no overlap
	if (min.getZ() > other.getMax().getZ()) return false;
	if (max.getZ() < other.getMin().getZ()) return false;

	if (min.getX() > other.getMax().getX()) return false;
	if (max.getX() < other.getMin().getX()) return false;

	if (min.getY() > other.getMax().getY()) return false;
	if (max.getY() < other.getMin().getY()) return false;

	if (boxIntersect == NULL)
        return true;

    boxIntersect->set(
        std::max(getMin().getX(), other.getMin().getX()),
        std::max(getMin().getY(), other.getMin().getY()),
        std::max(getMin().getZ(), other.getMin().getZ()),

        std::min(getMax().getX(), other.getMax().getX()),
        std::min(getMax().getY(), other.getMax().getY()),
        std::min(getMax().getZ(), other.getMax().getZ()));

	return true;
}

bool Box::contains(const Vector3D point) const
{
	return
		(point.getX() >= min.getX()) && (point.getX() <= max.getX()) &&
		(point.getY() >= min.getY()) && (point.getY() <= max.getY()) &&
		(point.getZ() >= min.getZ()) && (point.getZ() <= max.getZ());
}

void Box::set(float x1, float y1, float z1,
              float x2, float y2, float z2)
{
    if (x1 > x2 || y1 > y2 || z1 > z2)
        throw std::invalid_argument("Invalid box points!");

    min.set(x1, y1, z1);
    max.set(x2, y2, z2);
}

void Box::set(const Vector3D& _min, const Vector3D& _max)
{
    set(_min.getX(), _min.getY(), _min.getZ(),
        _max.getX(), _max.getY(), _max.getZ());
}

void Box::move(const Vector3D& position)
{
    min += position;
    max += position;
}

Box Box::moved(const Vector3D& position) const
{
    return Box(min + position, max + position);
}

