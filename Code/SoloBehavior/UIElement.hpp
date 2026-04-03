/******************************************************************************/
/*!
\file   UIElement.hpp
\author Tai Qian Yi
\par    Email: t.qianyi\@digipen.edu
\par    DigiPen login: t.qianyi
\par    Course: CSD1451
\par    Section B
\brief  This file contains the declarations of functions for UIElement class
*/
/******************************************************************************/

#pragma once
#ifndef _UIElement_
#include <iostream>
#include <cstdint>
#include <vector>
#include <crtdbg.h> // To check for memory leaks
#include <mutex>
#include <map>
#include <memory>
#include <algorithm>
#include "AEEngine.h"
#include "../Engine_WZBJ_Pak.hpp"

class UIElement : public SoloBehavior
{
public:
	//virtual On Hover function
	virtual void OnHover() = 0;
	//virtual On Hover Exit function
	virtual void OnHoverExit() = 0;
	//ui element values
	bool reset;
	bool enabled;
	//default cstr
	UIElement():reset(false), enabled(true){}
	//dstr
	~UIElement(){};
};


#endif