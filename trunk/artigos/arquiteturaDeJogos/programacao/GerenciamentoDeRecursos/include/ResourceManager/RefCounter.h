#ifndef REFCOUNTER_H
#define REFCOUNTER_H

#include <boost/utility.hpp>

#include "RefCounterFwd.h"

namespace pontov
{
	class RefCounter_c: public boost::noncopyable
	{		
		protected:
			RefCounter_c();
			virtual ~RefCounter_c() {};

		private:						
			void AddRef();
			void ReleaseRef();

			friend inline void boost::intrusive_ptr_add_ref(RefCounter_c *);
			friend inline void boost::intrusive_ptr_release(RefCounter_c *);

		private:			
			boost::detail::atomic_count tCount;
	};
}

namespace boost
{
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