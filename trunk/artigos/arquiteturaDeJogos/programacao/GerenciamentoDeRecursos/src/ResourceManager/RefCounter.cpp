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

#include "RefCounter.h"

namespace pontov
{
	RefCounter_c::RefCounter_c():
		tCount(0)
	{
	}
		
	void RefCounter_c::AddRef()
	{
		++tCount;
	}

	void RefCounter_c::ReleaseRef()
	{
		//Reduzimos o contador
		//Note que jogamos o valor em um temporario, pois como tCount pode ser modificado por threads
		//confiamos apenas no retorno de --
		long count = --tCount;

		//ultima referencia? Entao suicidio!
		if(count == 0)
			delete this;
	}	

}
