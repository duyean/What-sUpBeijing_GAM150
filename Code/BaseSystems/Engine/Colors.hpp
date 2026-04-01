/*!
@file Colors.hpp
@author Tan Yifeng, Edmund (t.yifengedmund)
@course CSD11451
@section B
@Final Project GAM 150
@date 01/04/26
@brief
This file contains the Color class which stores RGBA colour values and provides
normalisation utilities for use with the rendering system
*//*______________________________________________________________________*/
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

	/*!***********************************************************************
	* \brief
	* Normalises a colour channel value from the range [0, 255] to [0, 1]
	* \param[in] oldValue
	* The raw colour channel value to normalise
	* \return
	* The normalised float value in the range [0.0, 1.0]
	*************************************************************************/
	float normalize(float oldValue)
	{
		return ((oldValue - 0.f) / (255.f - 0.f)) * (1.f - 0.f) + 0.f;
	}

	/*!***********************************************************************
	* \brief
	* Default constructor, initialises all colour channels to zero and
	* sets the hex code to white (0xFFFFFFFF)
	*************************************************************************/
	Color() {
		R = G = B = 0;
		A = 0.f;
		hexCode = 0xFFFFFFFF;
	}

	/*!***********************************************************************
	* \brief
	* Constructs a Color with explicit RGBA values and computes the packed
	* hex representation
	* \param[in] Red
	* The red channel value (0-255)
	* \param[in] Green
	* The green channel value (0-255)
	* \param[in] Blue
	* The blue channel value (0-255)
	* \param[in] Alpha
	* The alpha channel value (0.0-1.0)
	*************************************************************************/
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

