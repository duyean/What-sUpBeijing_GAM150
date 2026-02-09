#include "HEALTHBAR1.hpp"
#include "../BaseSystems/Engine/EntityManager.hpp"
#include "Player.hpp"
#include "../Combat/Character/Character.hpp"

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
	AEVec2 pos = this->entity->transform->getPosition();
	float hpperc = this->entity->getComponent<Character>()->GetHealthPercentage();
	if (hpperc >= 0.4f)
	{
		color = Color(0, 255, 0, 1);
	}
	else
	{
		color = Color(255, 0, 0, 1);
	}
	AEVec2 scale = { 300, 10 };
	AEVec2 trueScale = { scale.x * hpperc, scale.y };
	AEVec2 offset{ -scale.x * 0.5f, -100 };
	MeshGen::getInstance().DrawFont(pos.x / 800.f, (pos.y - offset.y - 15) / 450.f, 0.5f, Color(255, 255, 255, 1), this->entity->getComponent<Character>()->GetName().c_str(), "liberi");
	MeshGen::getInstance().DrawBoxLeft(pos + offset, scale, Color(55, 55, 55, 1), 0);
	MeshGen::getInstance().DrawBoxLeft(pos + offset, trueScale, color, 0);
}

void Healthbar1::fixedUpdate()
{

}

void Healthbar1::destroy()
{

}
