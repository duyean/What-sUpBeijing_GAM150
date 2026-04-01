/******************************************************************************/
/*!
\file   Math.hpp
\author Tai Qian Yi
\par    Email: t.qianyi\@digipen.edu
\par    DigiPen login: t.qianyi
\par    Course: CSD1451
\par    Section B
\brief  This file contains only one helper function which is kinda sad
*/
/******************************************************************************/

#pragma once
#include "AEEngine.h"
#include <cassert>
#include <cmath>

/*!***********************************************************************
\brief Displays the selected blessing
\param[in] nameStr
The name of the blessing selected
\param[in] a
starting value
\param[in] b
ending value
\param[in] t
time taken to lerp
\return float
*************************************************************************/
float Lerp(float a, float b, float t);

