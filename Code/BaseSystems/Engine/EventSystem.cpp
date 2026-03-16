#include "EventSystem.hpp"
#include <cmath>
#include "../EaseFunctions/AEVEC2OVERLOAD.hpp"
#include "../../SoloBehavior/UIElement.hpp"

void EventSystem::addUIElement(UIElement* ui)
{
	uiElements.push_back(ui);
}

void EventSystem::removeUIElement(UIElement* ui)
{
	lastObject = nullptr;
	uiElements.erase(
		std::remove(uiElements.begin(), uiElements.end(), ui),
		uiElements.end()
	);
}

bool EventSystem::pointOverlap(s32 m_x, s32 m_y, UIElement* ui)
{	

	float ui_x = ui->entity->transform->getPosition().x;
	float ui_y = -ui->entity->transform->getPosition().y;
	float halfx = ui->entity->transform->getScale().x / 2;
	float halfy = ui->entity->transform->getScale().y / 2;

	float min_x = ui_x - halfx;
	float min_y = ui_y - halfy;
	float max_x = ui_x + halfx;
	float max_y = ui_y + halfy;

	if (m_x >= min_x &&
		m_y >= min_y &&
		m_x <= max_x &&
		m_y <= max_y)
	{
		return true;
	}

	return false;
}

void EventSystem::DispatchPointerTriggered(UIElement* uiElement, const PointerEventData& event)
{
	if (auto* handler = dynamic_cast<IPointerTriggered*>(uiElement))
	{
		handler->OnPointerTriggered(event);
		std::cout << "Mouse Button click Handler called for UI Element:" << uiElement->entity->name<<std::endl;
		return;
	}
}

void EventSystem::Update(double dt)
{
	//get the mouse position
	s32 m_x{}, m_y{};
	AEInputGetCursorPosition(&m_x, &m_y);
	s32 screen_x_offset = AEGfxGetWindowWidth() / 2;
	s32 screen_y_offset = AEGfxGetWindowHeight() / 2;

	// Mouse poition in world space (center being middle of the screen):
	eventData.x = m_x - screen_x_offset;
	eventData.y = -m_y + screen_y_offset;

	// Mouse position in screen space (center being top left of the screen):
	eventData.delta_x = m_x;
	eventData.delta_y = m_y;

	//check for each ui element whether it is colliding with it
	for (auto& uiElement : uiElements) {
		if (pointOverlap(m_x - screen_x_offset, m_y - screen_y_offset, uiElement))
		{			
			//call the respective dispatchers to return event data
			if (AEInputCheckTriggered(AEVK_LBUTTON) && uiElement->entity->isActive == true)
			{
				DispatchPointerTriggered(uiElement, eventData);
			}			
		}
	}

	//handle on hover events
	UIElement* currentHovered = nullptr;

	//if(GameStateManager::GetInstance()->GetCurrentLevel)
	for (auto& uiElement : uiElements)
	{
		//check if current mouse over any UI element
		if (pointOverlap(m_x - screen_x_offset, m_y - screen_y_offset, uiElement))
		{
			//set the current hovered
			currentHovered = uiElement;
			//break to skip any other elements
			break; 
		}
	}

	//Check if the current hovered got changed
	if (currentHovered != lastObject)
	{
		//If changed, set last object to call ExitHover
		if (lastObject && lastObject->entity->isActive == true)
			lastObject->OnHoverExit();

		//set the current hovered object OnHover
		if (currentHovered)
			currentHovered->OnHover();
		
		//reset the new object
		lastObject = currentHovered;
	}
	
}

bool EventSystem::IsPointerOverObject()
{
	return p_overObject;
}

EventSystem::EventSystem()
{
}

EventSystem::~EventSystem()
{

}

void EventSystem::ClearLastHoverObject()
{
	lastObject = nullptr;
}


