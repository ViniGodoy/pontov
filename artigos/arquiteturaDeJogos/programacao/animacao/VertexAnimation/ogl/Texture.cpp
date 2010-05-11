#include "Texture.h"

#include <stdexcept>

//#include "functions.h"

//#include "GL/glu.h"
//#include "GL/glext.h"

#include <SDL.h>
#include <SDL_image.h>
//#include "SDL_ttf.h"

using ogl::Texture;

Texture::Texture(const std::string& fileName)
{
    //Loads the image
    SDL_Surface *image = IMG_Load(fileName.c_str());

    if (image == NULL)
        throw std::invalid_argument("Unable to load texture file: " + fileName);

    createTexture(image);

}

/*
Texture::Texture(const std::string& text,
    const std::string& fontName, int size, float r, float g, float b)
{
    if (!TTF_WasInit() && TTF_Init() == -1)
  		throw std::runtime_error(std::string("Unable to start font system! Reason: ") + TTF_GetError());

    TTF_Font* font = TTF_OpenFont(fontName.c_str(), size);
    if (font == NULL)
        throw std::runtime_error("Unable to open font: " + fontName);


    SDL_Color color;
    color.b = 255 * r;
    color.g = 255 * g;
    color.r = 255 * b;

    SDL_Surface *textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
    TTF_CloseFont(font);
    if (textSurface == NULL)
        throw std::runtime_error("Unable create text: " + text + " Reason: " + TTF_GetError());

    createTexture(textSurface);

}*/

void Texture::createTexture(SDL_Surface* image)
{
    width = image->w;
    height = image->h;

    glGenTextures(1, &id);

    glBindTexture(GL_TEXTURE_2D, id);

    //Setup texture filters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


    glTexImage2D(GL_TEXTURE_2D, 0,
        image->format->BytesPerPixel, width, height, 0, image->format->BytesPerPixel == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
    //Free SDL image.
    SDL_FreeSurface(image);

    //Throw an exception in case of error
    GLenum err = glGetError ();
    if (GL_NO_ERROR != err)
        throw std::runtime_error("Error when creating texture!");
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::release() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

/*
void Texture::draw(float left, float top) const
{
    glColor3f(1,1,1);

    bind();
    ogl::flatQuad(left, top, width, height);
    release();
}
*/
int Texture::getWidth() const
{
    return width;
}

int Texture::getHeight() const
{
    return height;
}

