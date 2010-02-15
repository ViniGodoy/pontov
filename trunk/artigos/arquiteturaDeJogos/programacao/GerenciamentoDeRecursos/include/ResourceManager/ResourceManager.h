#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <string>

#include <boost/intrusive/set.hpp>

#include "TextureResource.h"

namespace pontov
{
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