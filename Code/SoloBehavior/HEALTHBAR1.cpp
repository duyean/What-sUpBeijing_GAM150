#include "HEALTHBAR1.hpp"
#include "../BaseSystems/Engine/EntityManager.hpp"
#include "Player.hpp"

float newRange(double oldV, double oldMin, double oldMax, double newMin, double newMax)
{
	return (float)(((oldV - oldMin) * (newMax - newMin)) / (oldMax - oldMin)) + (float)newMin;
}

void Healthbar1::awake()
{

}


void Healthbar1::init()
{
	Healthbar1::enSystem = &EntityManager::getInstance();
}

void Healthbar1::update()
{
	float health = Healthbar1::enSystem->rootEntity->FindByName("PLAYER")->getComponent<Player>()->health;
	if (health >= 40.f)
	{
		entity->mesh->color = Color(0, 255, 0, 1);
	}
	else
	{
		entity->mesh->color = Color(255, 0, 0, 1);
	}

	AEVec2 scale = entity->transform->getScale();
	scale.x = newRange(health, 0.00, 100.00, 0.00, 1200.f);
	entity->transform->setScale(scale);

}

void Healthbar1::fixedUpdate()
{

}

void Healthbar1::destroy()
{

}
