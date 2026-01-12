#pragma once
#include "AEEngine.h"

struct Color4
{
	float r; //red value (0 to 1 range)
	float g; //green value (0 to 1 range)
	float b; //blue value (0 to 1 range)
	float a; //opacity value (0 to 1 range)

	Color4() { r = g = b = a = 1.f; }
	Color4(float r, float g, float b, float a) { this->r = r; this->g = g; this->b = b; this->a = a; }
};