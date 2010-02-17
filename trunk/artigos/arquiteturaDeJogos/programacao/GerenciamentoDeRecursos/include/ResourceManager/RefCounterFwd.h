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

#ifndef REFCOUNTEDFWD_H
#define REFCOUNTEDFWD_H

#include <boost/intrusive_ptr.hpp>

/**
	Precisamos declarar as funcoes que o intrusive ptr utiliza, mas para
	tal precisamos declarar nossa classe, entao fazemos isso em dois passos
*/

/**
	Declarando a classe RefCounter

*/
namespace pontov
{
	class RefCounter_c;

	typedef boost::intrusive_ptr<RefCounter_c> RefCounterPtr_t;
}

/**
	Declarando as funcoes do ponteiro intrusivo, assim podemos dizer 
	que sao "friends"

*/
namespace boost
{
	inline void intrusive_ptr_add_ref(pontov::RefCounter_c *p);
	inline void intrusive_ptr_release(pontov::RefCounter_c *p);
};

#endif