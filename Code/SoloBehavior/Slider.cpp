#include "Slider.hpp"
#include "../BaseSystems/Engine/EventSystem.hpp"

void Slider::awake()
{
	enSystem = &EntityManager::getInstance();
	meSystem = &MeshGen::getInstance();

	entity->addComponent<Mesh>("Box", Color(50, 50, 50, 1), 100, MeshType::BOX_B);
	inc_button = entity->addComponent<Button>();

	AEVec2 scale = { 40.f, 40.f };
	inc_button->entity->transform->setScale(scale);
}

void Slider::init()
{	
	
}

void Slider::update()
{
	
}

void Slider::fixedUpdate()
{

}

void Slider::destroy()
{

}