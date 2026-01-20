#pragma once
#include "AEEngine.h"
#include "../../BaseSystems_WZBJ_Pak.hpp"
class Sprite : public Mesh
{
private:
	AEGfxTexture* texture;
public:
	void SetTexture(AEGfxTexture* _texture);
	void FreeTexture();
	Sprite();
	~Sprite();
};

