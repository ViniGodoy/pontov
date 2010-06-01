#ifndef VERTEX_H_INCLUDED
#define VERTEX_H_INCLUDED

#include <SDL_opengl.h>

#include <Vector3D.h>

namespace md2
{
    typedef GLfloat Vec3[3];

    class Vertex
    {
        public:
			Vertex();
            explicit Vertex(float x, float y, float z, int lightNormal);
            explicit Vertex(const math::Vector3D& _vertex, const math::Vector3D& _lightNormal);

            const math::Vector3D& getVertex() const;
            const math::Vector3D& getLightNormal() const;

            void draw() const;
            Vertex interpolate(const Vertex& other, float interpolation) const;

        private:
            static Vec3 NORMALS[162];

            math::Vector3D vertex;
            math::Vector3D lightNormal;
    };
}



#endif // VERTEX_H_INCLUDED
