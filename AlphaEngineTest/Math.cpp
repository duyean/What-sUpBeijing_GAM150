#include "Math.hpp"

float Lerp(float a, float b, float t)
{
	t = AEClamp(t, 0.0f, 1.0f);
	return a + t * (b - a);
}
