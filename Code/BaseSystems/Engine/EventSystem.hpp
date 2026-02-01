#pragma once
#ifndef _InputSystem_
#include <iostream>
#include <cstdint>
#include <vector>
#include <crtdbg.h> // To check for memory leaks
#include <map>
#include <memory>
#include <algorithm>
#include "AEEngine.h"
#include "InputInterfaces.hpp"
#include "Entity.hpp"


using namespace std;
class UIElement;

//Singleton class PhysicSystem Run once before game loop starts
class EventSystem
{
	std::vector<UIElement*> uiElements;

public:

	void addUIElement(UIElement* ui);
	void removeUIElement(UIElement* ui);
	bool pointOverlap(s32 m_x, s32 m_y, UIElement* ui);
	void DispatchPointerTriggered(UIElement* uiElement, const PointerEventData& event);
	void Update(double dt);
	bool IsPointerOverObject();

	EventSystem();
	~EventSystem();

private:

	PointerEventData eventData;
	bool p_overObject = false;
	UIElement* lastUIObject = nullptr;

public:


	EventSystem(const EventSystem&) = delete;
	EventSystem& operator=(const EventSystem&) = delete;

	static EventSystem& getInstance() {

		static EventSystem instance;
		return instance;
	}
};



#endif