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
		long count = --tCount;
		if(count == 0)
			delete this;
	}	

}
