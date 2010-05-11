#include <string>

#include "Frame.h"
#include "../math/MathUtil.h"

using namespace md2;

Frame::Frame(const std::vector<Vertex>& _vertices)
{
    set(_vertices);
}

void Frame::set(const std::vector<Vertex>& _vertices)
{
    float minX = _vertices[0].getVertex().getX();
    float minY = _vertices[0].getVertex().getY();
    float minZ = _vertices[0].getVertex().getZ();

    float maxX = _vertices[0].getVertex().getX();
    float maxY = _vertices[0].getVertex().getY();
    float maxZ = _vertices[0].getVertex().getZ();

    for (unsigned i = 0; i < _vertices.size(); i++)
    {
        vertices.push_back(_vertices[i]);
        setMinMax(_vertices[i].getVertex().getX(), minX, maxX);
        setMinMax(_vertices[i].getVertex().getY(), minY, maxY);
        setMinMax(_vertices[i].getVertex().getZ(), minZ, maxZ);
    }

    bounds.set(minX, minY, minZ, maxX, maxY, maxZ);
}

const Vertex& Frame::get(int index) const
{
    return vertices[index];
}

void Frame::draw(const std::vector<GlCommands> &commands, const Frame& nextFrame, float interpolation) const
{
    math::padValue(interpolation, 0.0, 1.0);

    if (interpolation == 0)
    {
        draw(commands);
        return;
    }

    for (unsigned i = 0; i < commands.size(); i++)
    {
        commands[i].begin();
            for (unsigned j = 0; j < commands[i].getVertices().size(); j++)
            {
                const GlCommandVertex &cmdVertex = commands[i].getVertices()[j];

                cmdVertex.applyTexture();
                get(cmdVertex.getVertexIndex())
                    .interpolate(nextFrame.get(cmdVertex.getVertexIndex()), interpolation)
                    .draw();
            }
        commands[i].end();
    }
}

void Frame::draw(const std::vector<GlCommands> &commands) const
{
    for (unsigned i = 0; i < commands.size(); i++)
    {
        commands[i].begin();
            for (unsigned j = 0; j < commands[i].getVertices().size(); j++)
            {
                const GlCommandVertex &cmdVertex = commands[i].getVertices()[j];

                cmdVertex.applyTexture();
                get(cmdVertex.getVertexIndex()).draw();
            }
        commands[i].end();
    }
}

const math::Box& Frame::getBounds() const
{
    return bounds;
}

void Frame::setMinMax(float value, float &min, float &max) const
{
    if (value < min)
        min = value;
    else if (value > max)
        max = value;
}
