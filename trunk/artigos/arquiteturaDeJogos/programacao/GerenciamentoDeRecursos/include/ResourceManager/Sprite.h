/******************************************************************************
*
* COPYRIGHT Bruno C Sanches ALL RIGHTS RESERVED.
*
* This software cannot be copied, stored, distributed without  
* Bruno C Sanches prior authorization.
*
* This file was made available on http://www.pontov.com.br and it is free 
* to be restributed or used under Creative Commons license 2.5 br: 
* http://creativecommons.org/licenses/by-sa/2.5/br/
*
* This work was based on Paulo V. W. Radtke animation software.
*
*******************************************************************************
* Este software nao pode ser copiado, armazenado, distribuido sem autorização 
* a priori de Bruno C Sanches
*
* Este arquivo foi disponibilizado no site http://www.pontov.com.br e esta 
* livre para distribuição seguindo a licença Creative Commons 2.5 br: 
* http://creativecommons.org/licenses/by-sa/2.5/br/
*
* Este trabalho é baseado no software de animação criado por Paulo V. W. Radtke
* 
******************************************************************************/

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
			Sprite_c(const std::string &name, float startX, float startY);

			inline float GetPosX()
			{
				return fPosX;
			}

			inline void Update(SDL_Surface &dest, Uint32 ticks)
			{
				fPosX += (float)(ticks * 200 / 1000.0);

				ipTexture->Blit(dest, (int)fPosX, (int)fPosY);
			}

		private:
			TextureResourcePtr_t ipTexture;
			float fPosX, fPosY;
	};
}

#endif
