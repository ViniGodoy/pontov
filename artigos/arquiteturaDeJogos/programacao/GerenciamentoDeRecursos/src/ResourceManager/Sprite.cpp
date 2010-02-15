#include "Sprite.h"

#include "ResourceManager.h"

namespace pontov
{
	Sprite_c::Sprite_c(const std::string &name, int startX, int startY):
		ipTexture(ResourceManager_c::GetInstance().LoadTexture(name)),
		iPosX(startX), 
		iPosY(startY)
	{
		//empty
	}
}
