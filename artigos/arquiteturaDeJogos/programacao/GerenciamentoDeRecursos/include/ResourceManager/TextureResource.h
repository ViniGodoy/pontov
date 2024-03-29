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
* Este software nao pode ser copiado, armazenado, distribuido sem autoriza��o 
* a priori de Bruno C Sanches
*
* Este arquivo foi disponibilizado no site http://www.pontov.com.br e esta 
* livre para distribui��o seguindo a licen�a Creative Commons 2.5 br: 
* http://creativecommons.org/licenses/by-sa/2.5/br/
*
* Este trabalho � baseado no software de anima��o criado por Paulo V. W. Radtke
* 
******************************************************************************/

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL.h>

#include "Resource.h"

namespace pontov
{	
	typedef boost::intrusive_ptr<class TextureResource_c> TextureResourcePtr_t;

	class TextureResource_c: public Resource_c
	{
		public:
			TextureResource_c(const std::string &name);			

			void Blit(SDL_Surface &dest, int x, int y) const;

		private:
			~TextureResource_c();

		private:
			SDL_Surface *pSurface;
	};
}

#endif
