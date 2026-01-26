#include "UIElement.hpp"
#include "EventSystem.hpp"

EventSystem* eventSystem = EventSystem::getInstance();

void UIElement::awake()
{
	eventSystem->addUIElement(this);
}

void UIElement::destroy()
{
	eventSystem->removeUIElement(this);
}
