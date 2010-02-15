#include "ResourceManager.h"

namespace pontov
{
	ResourceManager_c ResourceManager_c::clManager_gl;

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

	ResourceManager_c &ResourceManager_c::GetInstance()
	{
		return clManager_gl;
	}

	TextureResourcePtr_t ResourceManager_c::LoadTexture(const std::string &name)
	{		
		TexturesSet_t::iterator it(setTextures.find(name, ResourceComp_s()));

		if(it == setTextures.end())
		{
			TextureResourcePtr_t newTexture = new TextureResource_c(name);
			setTextures.insert(*newTexture);

			return newTexture;
		}

		return TextureResourcePtr_t(&(*it));
	}
}

