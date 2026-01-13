#pragma once
#include "AEEngine.h"
#include "Mesh.hpp"
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

