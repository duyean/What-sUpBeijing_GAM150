#include "Button.hpp"
#include "Entity.hpp"
#include "EventSystem.hpp"

EventSystem* eventSystem = EventSystem::getInstance();

void Button::awake()
{
	eventSystem->addUIElement(this);
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
