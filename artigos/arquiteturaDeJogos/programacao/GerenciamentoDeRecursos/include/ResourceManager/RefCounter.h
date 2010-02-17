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

#ifndef REFCOUNTER_H
#define REFCOUNTER_H

#include <boost/detail/atomic_count.hpp>
#include <boost/utility.hpp>

#include "RefCounterFwd.h"

namespace pontov
{
	/**
		Esta classe representa um contador de referências a ser usado com 
		smart pointers intrusivos.

	*/
	class RefCounter_c: public boost::noncopyable
	{		
		protected:
			RefCounter_c();
			virtual ~RefCounter_c() {};

		private:						
			void AddRef();
			void ReleaseRef();

			//Funces chamadas pelo intrusive_ptr para controlar as referencias
			friend inline void boost::intrusive_ptr_add_ref(RefCounter_c *);
			friend inline void boost::intrusive_ptr_release(RefCounter_c *);

		private:			
			//Usamos atomic_count na esperança de deixar o código thread safe
			//Nao testado, use com threads por sua conta e risco
			boost::detail::atomic_count tCount;
	};
}

namespace boost
{
	//Aqui temos as funcoes que o intrusive ptr invoca para controle de referencias
	inline void intrusive_ptr_add_ref(pontov::RefCounter_c *p)
	{
		p->AddRef();
	}

	inline void intrusive_ptr_release(pontov::RefCounter_c *p)
	{
		p->ReleaseRef();
	}
}

#endif