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

#ifndef RESOURCE_H
#define RESOURCE_H

#include "RefCounter.h"

#include <boost/intrusive/set.hpp>

namespace pontov
{
	typedef boost::intrusive::set_base_hook<boost::intrusive::link_mode<boost::intrusive::auto_unlink> > ResourceAutoUnlinkHook_t;

	/**
		Essa classe é a base para armazenar um recurso da aplicacao.

		Recursos sao controlados pelo nome do arquivo (incluindo caminho) do qual representam

	*/
	class Resource_c: public RefCounter_c, public ResourceAutoUnlinkHook_t
	{
		public:			
			inline bool operator<(const Resource_c &rhs) const
			{
  				return strName.compare(rhs.strName) < 0;	
			}

			inline std::string GetName() const
			{
				return strName;
			}

		protected:
			Resource_c(const std::string &name);			

		private:
			std::string strName;
	};
}

#endif
