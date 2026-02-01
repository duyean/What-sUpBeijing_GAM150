#include "Button.hpp"

EventSystem* eventSystem = &EventSystem::getInstance();

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

void Button::SetNormalColor(Color color)
{
	normal_color = color;
}

void Button::SetHighlightedColor(Color color)
{
	highlighted_color = color;
}

void Button::SetPressedColor(Color color)
{
	pressed_color = color;
}

void Button::OnPointerTriggered(const PointerEventData& event)
{
	buttonMesh->color = pressed_color;
	if (onClick)
		onClick();
}

void Button::OnHover()
{
	buttonMesh->color = highlighted_color;
}

void Button::OnHoverExit()
{
	buttonMesh->color = normal_color;
}
