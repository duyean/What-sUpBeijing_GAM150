#pragma once
#ifndef _Colors_
#include <iostream>
#include <cstdint>
#include <vector>
#include <crtdbg.h> // To check for memory leaks
#include <mutex>
#include <map>
#include <memory>
#include "AEEngine.h"


using namespace std;

class Color
{
public:
	int R;
	int G;
	int B;
	float A;
	u32 hexCode;

	float normalize(float oldValue)
	{
		return ((oldValue - 0.f) / (255.f - 0.f)) * (1.f - 0.f) + 0.f;
	}

	Color() {
		R = G = B = 0;
		A = 0.f;
		hexCode = 0xFFFFFFFF;
	}

	Color(int Red, int Green, int Blue, float Alpha) {
		R = Red;
		G = Green;
		B = Blue;
		A = Alpha;
		hexCode = ((static_cast<u32>(R) & 0xff) << 24) +
			((static_cast<u32>(G) & 0xff) << 16) +
			((static_cast<u32>(B) & 0xff) << 8) +
			(static_cast<u32>(A) & 0xff);
	}
};

#endif