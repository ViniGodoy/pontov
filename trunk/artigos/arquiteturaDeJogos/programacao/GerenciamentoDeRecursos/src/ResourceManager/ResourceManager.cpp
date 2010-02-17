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

#include "ResourceManager.h"

namespace pontov
{
	ResourceManager_c ResourceManager_c::clManager_gl;

	ResourceManager_c &ResourceManager_c::GetInstance()
	{
		return clManager_gl;
	}

	/**
		Para que nao seja preciso instanciar um recurso apenas para fazer a busca no conteiner
		usamos um "comparador" especifico para strings

	*/
	struct ResourceComp_s
	{
		bool operator()(const std::string &name, const Resource_c &res) const
		{
			return name.compare(res.GetName()) < 0;	
		}

		bool operator()(const Resource_c &res, const std::string &name) const
		{
			return res.GetName().compare(name) < 0;
		}
	};


	TextureResourcePtr_t ResourceManager_c::LoadTexture(const std::string &name)
	{		
		//pegando o recurso no set
		TexturesSet_t::iterator it(setTextures.find(name, ResourceComp_s()));

		//recurso nao existe?
		if(it == setTextures.end())
		{
			//criamos um novo e inserimos no set
			TextureResourcePtr_t newTexture = new TextureResource_c(name);
			setTextures.insert(*newTexture);

			return newTexture;
		}

		//recurso ja carregado, entao devolvemos o ja existente
		return TextureResourcePtr_t(&(*it));
	}
}

