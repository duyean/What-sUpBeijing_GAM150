#pragma once
#ifndef _InputSystem_
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
#include "InputInterfaces.hpp"
#include "Entity.hpp"
#include "UIElement.hpp"

using namespace std;

//Singleton class PhysicSystem Run once before game loop starts
class EventSystem
{
	static EventSystem* instance;
	static mutex mtx;

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

	EventSystem(const EventSystem& obj) = delete;

	static EventSystem* getInstance() {
		if (instance == nullptr)
		{
			lock_guard<mutex> lock(mtx);
			if (instance == nullptr) {
				instance = new EventSystem();
			}
		}

		return instance;
	}
};



#endif