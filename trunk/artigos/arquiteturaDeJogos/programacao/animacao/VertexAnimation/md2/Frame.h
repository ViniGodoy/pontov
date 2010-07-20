#ifndef MD2FRAME_H_INCLUDED
#define MD2FRAME_H_INCLUDED

#include <vector>
#include <stdexcept>
#include <memory>

#include "GlCommands.h"
#include "Vertex.h"
#include "md2.h"

#include <Box.h>


namespace md2
{
    class Frame
    {
        public:
            explicit Frame() {}            
			explicit Frame(std::istream &stream, int numVertices, const Md2Frame_t &frameHeader, float scale);

            void set(const std::vector<Vertex>& _vertices);            

            void draw(const std::vector<GlCommands> &commands, const Frame& nextFrame, float interpolation) const;
            void draw(const std::vector<GlCommands> &commands) const;
            const math::Box& getBounds() const;

        private:
            math::Box bounds;
            std::vector<Vertex> vertices;
            void Frame::setMinMax(float value, float &min, float &max) const;
    };
}
#endif // MD2FRAME_H_INCLUDED
