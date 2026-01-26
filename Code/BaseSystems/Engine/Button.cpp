#include "Button.hpp"
#include "Entity.hpp"
#include "EventSystem.hpp"

EventSystem* eventSystem = EventSystem::getInstance();

void Button::awake()
{
	eventSystem->addUIElement(this);
	buttonMesh = this->entity->getComponent<Mesh>();
}


void Button::init()
{
	
}

void Button::update()
{

}

void Button::fixedUpdate()
{
	
}

void Button::destroy()
{
	eventSystem->removeUIElement(this);
}

void Button::OnPointerTriggered(const PointerEventData& event)
{

}
