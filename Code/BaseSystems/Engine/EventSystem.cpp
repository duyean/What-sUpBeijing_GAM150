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

bool EventSystem::pointOverlap(UIElement* ui)
{
	AEInputGetCursorPosition(m_x, m_y);
	return false;
}

void EventSystem::Update(double dt)
{

}
