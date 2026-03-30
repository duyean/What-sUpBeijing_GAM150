/******************************************************************************/
/*!
\file   EventSystem.hpp
\author Tai Qian Yi
\par    Email: t.qianyi\@digipen.edu
\par    DigiPen login: t.qianyi
\par    Course: CSD1451
\par    Section B
\brief  This file contains the declarations of functions for Event System
*/
/******************************************************************************/

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
/*!***********************************************************************
\brief This function adds the UI object to the EventSystem to be updated
\param ui
The UIElement object we want to add to the event system
*************************************************************************/
	void addUIElement(UIElement* ui);
/*!***********************************************************************
\brief This function adds the UI object to the EventSystem to be updated
\param ui
The UIElement object we want to add to the event system
*************************************************************************/
	void removeUIElement(UIElement* ui);
/*!***********************************************************************
\brief Checks if the mouse if currently over the UIElement
\param m_x
The current mouse x pos
\param m_y
The current mouse y pos
\param ui
Pointer to the current UIElement object
\return bool
*************************************************************************/
	bool pointOverlap(s32 m_x, s32 m_y, UIElement* ui);
/*!***********************************************************************
\brief Dispatch pointer event when mouse clicked
\param uiElement
Pointer to the current UIElement we trigger
\param event
Const reference to the Pointer Event Data 
*************************************************************************/
	void DispatchPointerTriggered(UIElement* uiElement, const PointerEventData& event);
/*!***********************************************************************
\brief Updates all the UIElements 
\param dt
game delta time
*************************************************************************/
	void Update(double dt);
/*!***********************************************************************
\brief Returns if mouse pointer is over UIElement
\return bool
*************************************************************************/
	bool IsPointerOverObject();

	EventSystem();
	~EventSystem();

private:	
	bool p_overObject = false;
	UIElement* lastObject = nullptr;
public:
	
	PointerEventData eventData{ 0,0,0,0 };
/*!***********************************************************************
\brief Clears the last UIElement that was hovered
*************************************************************************/
	void ClearLastHoverObject();
	EventSystem(const EventSystem&) = delete;
	EventSystem& operator=(const EventSystem&) = delete;
/*!***********************************************************************
\brief Returns instance of Event System
\return EventSystem&
*************************************************************************/
	static EventSystem& getInstance() {

		static EventSystem instance;
		return instance;
	}
};



#endif