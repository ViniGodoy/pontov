#ifndef RESOURCE_H
#define RESOURCE_H

#include "RefCounter.h"

#include <boost/intrusive/set.hpp>

namespace pontov
{
	typedef boost::intrusive::set_base_hook<boost::intrusive::link_mode<boost::intrusive::auto_unlink> > ResourceAutoUnlinkHook_t;

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
			virtual ~Resource_c() {};

		private:
			std::string strName;
	};
}

#endif
