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
#include "OOP.hpp"
#include "Entity.hpp"
#include "Colors.hpp"

class UIElement : public SoloBehavior
{
public:
	UIElement(){}
	~UIElement(){};
};


#endif