#include "Button.hpp"
#include "../Audio_WZBJ_Pak.hpp"

EventSystem* eventSystem = &EventSystem::getInstance();

void Button::awake()
{
	eventSystem->addUIElement(this);
	buttonMesh = this->entity->getComponent<Mesh>();
}


void Button::init()
{
	if(buttonMesh)
		buttonMesh->color = normal_color;
}

void Button::update()
{
	if (reset)
	{
		buttonMesh->color = normal_color;
		reset = false;
	}
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
	if(buttonMesh)
		buttonMesh->color = pressed_color;
	if (onClick)
	{
		onClick();
		AudioManager::GetInstance()->PlaySFX(AudioManager::SFX_BUTTON_PRESS);
	}
}

void Button::OnHover()
{
	if(buttonMesh)
		buttonMesh->color = highlighted_color;
	if (onHover)
		onHover();
}

void Button::OnHoverExit()
{
	if(buttonMesh)
		buttonMesh->color = normal_color;
	if (onHoverExit)
		onHoverExit();
}
