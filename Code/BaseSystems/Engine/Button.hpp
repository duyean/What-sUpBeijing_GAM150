#pragma once
#ifndef _BoxCollider2D_
#include <iostream>
#include <cstdint>
#include <vector>
#include <functional>
#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include "OOP.hpp"
#include "Colors.hpp"
#include "UIElement.hpp"


class Button : public UIElement
{
private:

public:
	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	Color normal_color;
	Color highlighted_color;
	Color pressed_color;


	Button(){}
	~Button(){};
};


#endif