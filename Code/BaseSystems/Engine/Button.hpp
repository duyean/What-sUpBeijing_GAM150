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
#include "InputInterfaces.hpp"


class Button : public UIElement, public IPointerTriggered
{
private:
	Mesh* buttonMesh;
	void OnPointerTriggered(const PointerEventData& event) override;
	void OnHover() override;
	void OnHoverExit() override;

	Color normal_color;
	Color highlighted_color;
	Color pressed_color;

public:
	using Callback = std::function<void()>;

	void SetOnClick(Callback cb)
	{
		onClick = std::move(cb);
	}

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	void SetNormalColor(Color color);
	void SetHighlightedColor(Color color);
	void SetPressedColor(Color color);

	Button() {
		buttonMesh = nullptr;
		normal_color = {255,255,255,255 };
		highlighted_color = { 255,255,255,255 };
		pressed_color = { 200,200,200,255 };
	}
	~Button(){}

private:
	Callback onClick;
};


#endif