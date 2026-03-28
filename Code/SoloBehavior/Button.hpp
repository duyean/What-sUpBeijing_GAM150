#pragma once
#ifndef _BoxCollider2D_
#include <iostream>
#include <cstdint>
#include <vector>
#include <functional>
#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include "UIElement.hpp"



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
	Color disabled_color;
public:
	using Callback = std::function<void()>;

	void SetOnClick(Callback cb)
	{
		//onClick = std::move(cb);
		onClick = cb;
	}

	void SetOnHover(Callback cb)
	{
		onHover = cb;
	}

	void SetOnHoverExit(Callback cb)
	{
		onHoverExit = cb;
	}

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	void SetNormalColor(Color color);
	void SetHighlightedColor(Color color);
	void SetPressedColor(Color color);
	void SetDisabledColor(Color color);

	Button() {
		enabled = true;
		buttonMesh = nullptr;
		normal_color = {255,255,255,1 };
		highlighted_color = { 255,255,255,1 };
		pressed_color = { 200,200,200,1 };
		disabled_color = { 200,200,200, 0.5 };
	}
	~Button(){}

private:
	Callback onClick;
	Callback onHover;
	Callback onHoverExit;
};


#endif