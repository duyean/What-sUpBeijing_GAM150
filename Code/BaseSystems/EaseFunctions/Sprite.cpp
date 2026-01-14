#include "Sprite.hpp"

void Sprite::SetTexture(AEGfxTexture* _texture)
{
	texture = _texture;
	AEGfxTextureSet(texture, 0, 0);
}

void Sprite::FreeTexture()
{
	if(texture != nullptr)
		AEGfxTextureUnload(texture);
}

Sprite::Sprite()
{
	texture = nullptr;
	//SetRenderMode(AE_GFX_RM_TEXTURE);
}

Sprite::~Sprite()
{
}
