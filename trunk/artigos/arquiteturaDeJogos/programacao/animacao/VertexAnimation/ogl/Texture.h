#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include <string>
#include <SDL_opengl.h>

struct SDL_Surface;

namespace ogl
{
    class Texture
    {
        public:
            explicit Texture(const std::string& fileName);
            explicit Texture(const std::string& text,
                const std::string& fontName, int size, float r=1.0, float g=1.0, float b=1.0);

            /** Binds the texture to the next vertexes */
            void bind() const;

            /** Releases the texture */
            void release() const;

            /** Draws the texture as a flat image.*/
            //void draw(float left=0, float top=0) const;

            int getWidth() const;
            int getHeight() const;

        private:
            int width;
            int height;

            //Disallows copy and assignment
            Texture(const Texture& other);
            Texture& operator=(const Texture& other);

            void createTexture(SDL_Surface* image);

            GLuint id;
    };
}

#endif // TEXTURE_H_INCLUDED
