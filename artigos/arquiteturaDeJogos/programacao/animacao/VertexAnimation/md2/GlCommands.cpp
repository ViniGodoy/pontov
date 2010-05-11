#include "GlCommands.h"

using md2::GlCommands;
using md2::GlCommandVertex;

GlCommands::GlCommands(GLenum _cmd)
: cmd(_cmd)
{
}

void GlCommands::begin() const
{
    glBegin(cmd);
}

void GlCommands::add(const GlCommandVertex& vertex)
{
    vertices.push_back(vertex);
}

void GlCommands::end() const
{
    glEnd();
}

const std::vector<GlCommandVertex>&  GlCommands::getVertices() const
{
    return vertices;
}

