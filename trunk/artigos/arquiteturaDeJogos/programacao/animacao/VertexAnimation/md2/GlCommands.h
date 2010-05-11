#ifndef GLCOMMANDS_H_INCLUDED
#define GLCOMMANDS_H_INCLUDED

#include <vector>
#include <SDL_opengl.h>

namespace md2
{
    class GlCommandVertex
    {
        public:
            explicit GlCommandVertex(GLfloat _s, GLfloat _t, int _vertex) : s(_s), t(_t), vertex(_vertex) {}

            inline int getVertexIndex() const { return vertex; }
            inline void applyTexture() const {glTexCoord2f (s, t); }

        private:
            GLfloat s;
            GLfloat t;
            int vertex;
    };

    class GlCommands
    {
        public:
            explicit GlCommands(GLenum _cmd);
            void begin() const;
            void add(const GlCommandVertex& vertex);
            void end() const;
            const std::vector<GlCommandVertex>& getVertices() const;

        private:
            GLenum cmd;
            std::vector<GlCommandVertex> vertices;
    };
}

#endif // GLCOMMAND_H_INCLUDED
