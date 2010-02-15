#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include "TextureResource.h"
#include "RefCounter.h"

namespace pontov
{
	class Sprite_c;

	typedef boost::intrusive_ptr<Sprite_c> SpritePtr_t;

	class Sprite_c: public RefCounter_c
	{
		public:
			Sprite_c(const std::string &name, int startX, int startY);

			inline void SetPosX(int x)
			{
				iPosX = x;
			}

			inline int GetPosX()
			{
				return iPosX;
			}

			inline void Blit(SDL_Surface &dest)
			{
				ipTexture->Blit(dest, iPosX, iPosY);
			}

		private:
			TextureResourcePtr_t ipTexture;
			int iPosX, iPosY;
	};
}

#endif
