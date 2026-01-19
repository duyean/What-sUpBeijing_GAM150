#include "HEALTHBAR2.hpp"
#include "EntityManager.hpp"
#include "Player.hpp"


void Healthbar2::awake()
{

}


void Healthbar2::init()
{
	Healthbar2::enSystem = EntityManager::getInstance();
}

void Healthbar2::update()
{
	float health = Healthbar2::enSystem->rootEntity->FindByName("PLAYER")->getComponent<Player>()->health;
	Color colorTemp = Color(0, 255, 0, 1);
	if (health >= 40.f)
	{
		colorTemp.G = 255;
		colorTemp.R = 0;
	}
	else
	{
		colorTemp.G = 0;
		colorTemp.R = 255;
	}

	if (health <= hideAtValue)
	{
		colorTemp.A = 0;
	}
	else
	{
		colorTemp.A = 1;
	}

	entity->mesh->color = colorTemp;

}

void Healthbar2::fixedUpdate()
{

}

void Healthbar2::destroy()
{

}
