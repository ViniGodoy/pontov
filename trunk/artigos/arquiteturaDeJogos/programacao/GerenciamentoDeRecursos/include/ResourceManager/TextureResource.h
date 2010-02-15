#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL.h>

#include "Resource.h"

namespace pontov
{
	class TextureResource_c;

	typedef boost::intrusive_ptr<TextureResource_c> TextureResourcePtr_t;

	class TextureResource_c: public Resource_c
	{
		public:
			TextureResource_c(const std::string &name);			

			void Blit(SDL_Surface &dest, int x, int y);

		private:
			~TextureResource_c();

		private:
			SDL_Surface *pSurface;
	};
}

#endif
