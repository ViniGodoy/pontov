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

#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <string>

#include <boost/intrusive/set.hpp>

#include "TextureResource.h"

namespace pontov
{
	/**
		Este é o gerenciador de recursos.

		O seu trabalho é manter uma lista dos recursos carregados

	*/
	class ResourceManager_c
	{
		public:
			static ResourceManager_c &GetInstance();

			TextureResourcePtr_t LoadTexture(const std::string &name);

		private:
			static ResourceManager_c clManager_gl;

			typedef boost::intrusive::set<TextureResource_c, boost::intrusive::constant_time_size<false> > TexturesSet_t;
			TexturesSet_t setTextures;
	};
}

#endif