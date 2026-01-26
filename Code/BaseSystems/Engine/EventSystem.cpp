#include "EventSystem.hpp"
#include <cmath>
#include "../EaseFunctions/AEVEC2OVERLOAD.hpp"


void EventSystem::addUIElement(UIElement* ui)
{
	uiElements.push_back(ui);
}

void EventSystem::removeUIElement(UIElement* ui)
{
	uiElements.erase(
		std::remove(uiElements.begin(), uiElements.end(), ui),
		uiElements.end()
	);
}

bool EventSystem::pointOverlap(s32 m_x, s32 m_y, UIElement* ui)
{	
	float ui_x = ui->entity->transform->getPosition().x;
	float ui_y = ui->entity->transform->getPosition().y;
	float halfx = ui->entity->transform->getScale().x / 2;
	float halfy = ui->entity->transform->getScale().y / 2;
	
	s32 min_x = (s32) ui_x - halfx;
	s32 min_y = (s32) ui_y - halfy;
	s32 max_x = (s32) ui_x + halfx;
	s32 max_y = (s32) ui_y + halfy;

	if (m_x >= min_x &&
		m_y >= min_y &&
		m_x <= max_x &&
		m_y <= max_y)
	{
		return true;
	}

	return false;
}

void EventSystem::Update(double dt)
{
	//get the mouse position
	s32 m_x{}, m_y{};
	AEInputGetCursorPosition(&m_x, &m_y);

	//check for each ui element whether it is colliding with it
	for (auto& uiElement : uiElements) {
		if (pointOverlap(m_x, m_y, uiElement))
		{
			eventData.currentUIObject = uiElement;
			std::cout << "Mouse is over ui element:" << uiElement->entity->name;
		}
	}

	//return event data
	/*eventData.x = m_x;
	eventData.y = m_y;*/
}

EventSystem::EventSystem()
{
}

EventSystem::~EventSystem()
{

}
