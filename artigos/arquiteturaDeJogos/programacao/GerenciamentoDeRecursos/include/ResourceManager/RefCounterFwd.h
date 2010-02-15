#ifndef REFCOUNTEDFWD_H
#define REFCOUNTEDFWD_H

#include <boost/intrusive_ptr.hpp>
#include <boost/detail/atomic_count.hpp>

namespace pontov
{
	class RefCounter_c;

	typedef boost::intrusive_ptr<RefCounter_c> RefCounterPtr_t;
}

namespace boost
{
	inline void intrusive_ptr_add_ref(pontov::RefCounter_c *p);
	inline void intrusive_ptr_release(pontov::RefCounter_c *p);
};

#endif