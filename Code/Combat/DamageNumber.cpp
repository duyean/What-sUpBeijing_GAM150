#include "DamageNumber.hpp"
#include <string>
#include "CombatUIManager.hpp"

DamageNumbers::DamageNumbers()
{
	enSystem = EntityManager::getInstance();
	lifetime = 0.8f;
}

void DamageNumbers::awake()
{

}

Color DamageNumbers::GetElementColor(Game::WUXING_ELEMENT element)
{
	switch (element)
	{
		case (Game::EARTH):
		{
			return Color(53, 196, 10, 1);
		}
		case (Game::FIRE):
		{
			return Color(217, 68, 0, 1);
		}
		case (Game::METAL):
		{
			return Color(189, 189, 189, 1);
		}
		case (Game::WATER):
		{
			return Color(0, 76, 255, 1);
		}
		case (Game::WOOD):
		{
			return Color(107, 57, 48, 1);
		}
		case (Game::NORMAL):
		default:
		{
			return Color(255, 255, 255, 1);
		}
	}
}


void DamageNumbers::init()
{

}

void DamageNumbers::update()
{

	AEVec2 normalised = {(this->entity->transform->getPosition().x - this->entity->transform->getScale().x * 0.10f)/ 800, (this->entity->transform->getPosition().y + 100) / 450};
	MeshGen::getInstance()->DrawFont(normalised.x, normalised.y, 1, textColor, text.c_str(), "font1");
	lifetime -= 1 / 60.f;
	if (lifetime <= 0)
	{
		destroy();
	}
}

void DamageNumbers::fixedUpdate()
{
}

void DamageNumbers::destroy()
{
	printf("Destroyed Text\n");
	enSystem->entities.erase(
		std::remove_if(
			enSystem->entities.begin(),
			enSystem->entities.end(),
			[this](const std::unique_ptr<Entity>& e) {
				return e.get() == this->entity;
			}
		),
		enSystem->entities.end()
	);
}