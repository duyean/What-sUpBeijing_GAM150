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
	virtual void OnHover() = 0;
	virtual void OnHoverExit() = 0;
	UIElement(){}
	~UIElement(){};
};


#endif