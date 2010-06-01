#include "Vertex.h"
#include "../math/MathUtil.h"

using namespace md2;

Vec3 Vertex::NORMALS[] = {
#include "anorms.h"
};

Vertex::Vertex():
	vertex(0, 0, 0),
	lightNormal(0, 0, 0)
{
	//empty
}

Vertex::Vertex(float x, float y, float z, int _lightNormal) :
vertex(y, z, x), lightNormal(NORMALS[_lightNormal][1], NORMALS[_lightNormal][2], NORMALS[_lightNormal][0])
{
}

Vertex::Vertex(const math::Vector3D& _vertex, const math::Vector3D& _lightNormal) :
vertex(_vertex), lightNormal(_lightNormal)
{
}

const math::Vector3D& Vertex::getVertex() const
{
    return vertex;
}

const math::Vector3D& Vertex::getLightNormal() const
{
    return lightNormal;
}

void Vertex::draw() const
{
    glNormal3f(lightNormal.getX(), lightNormal.getY(), lightNormal.getZ());
    glVertex3f(vertex.getX(), vertex.getY(), vertex.getZ());
}

Vertex Vertex::interpolate(const Vertex& other, float interpolation) const
{
    return Vertex(math::Vector3D(vertex + ((other.vertex - vertex) * interpolation)), lightNormal);
}

