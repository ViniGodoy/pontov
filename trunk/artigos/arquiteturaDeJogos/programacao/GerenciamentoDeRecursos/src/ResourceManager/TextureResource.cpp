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

#include "TextureResource.h"

#include <exception>
#include <sstream>

using namespace std;

namespace pontov
{
	TextureResource_c::TextureResource_c(const std::string &name):
		Resource_c(name)
	{
		//carregando a surface
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

	void TextureResource_c::Blit(SDL_Surface &dest, int x, int y) const
	{
		SDL_Rect rect;

		rect.x = x;
		rect.y = y;
		rect.w = pSurface->w;
		rect.h = pSurface->h;

		SDL_BlitSurface(pSurface, NULL, &dest, &rect);		
	}
}
