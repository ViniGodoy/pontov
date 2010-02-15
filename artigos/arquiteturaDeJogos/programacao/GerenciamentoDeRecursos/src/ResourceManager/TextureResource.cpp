#include "TextureResource.h"

#include <exception>
#include <sstream>

using namespace std;

namespace pontov
{
	TextureResource_c::TextureResource_c(const std::string &name):
		Resource_c(name)
	{
		pSurface = SDL_LoadBMP(this->GetName().c_str());
		if(pSurface == NULL)
		{
			stringstream stream;
			stream << "Cant load " + name;
			throw exception(stream.str().c_str());
		}
	}

	TextureResource_c::~TextureResource_c()
	{
		SDL_FreeSurface(pSurface);
	}

	void TextureResource_c::Blit(SDL_Surface &dest, int x, int y)
	{
		SDL_Rect rect;

		rect.x = x;
		rect.y = y;
		rect.w = pSurface->w;
		rect.h = pSurface->h;

		SDL_BlitSurface(pSurface, NULL, &dest, &rect);		
	}
}
