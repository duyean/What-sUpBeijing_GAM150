#include "DamageNumber.hpp"
#include <string>
#include "CombatUIManager.hpp"

DamageNumbers::DamageNumbers()
{
	enSystem = &EntityManager::getInstance();
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
	
	AEVec2 normalised = {this->entity->transform->getPosition().x / 800.f, this->entity->transform->getPosition().y / 450.f};
	MeshGen::getInstance().DrawFont(normalised.x, normalised.y, size, textColor, text.c_str(), "liberi");
	lifetime -= 1 / 60.f;
	if (lifetime <= 0)
	{
		Destroy(entity);
	}
	else
	{
		if (lifetime > 0.7f && size < 1.f)
		{
			size += 25.f * static_cast<float>(AEFrameRateControllerGetFrameTime());
		}
		else if (lifetime < 0.7f && size > 0.f)
		{
			size -= 0.3f * static_cast<float>(AEFrameRateControllerGetFrameTime());
			if (textColor.A >= 0.f) {
				textColor.A -= 2.f * static_cast<float>(AEFrameRateControllerGetFrameTime());
			}
		

		}
		
		float smoothing = 10.0f;
		AEVec2 lerped{};
		AEVec2 position = entity->transform->getPosition();
		AEVec2 target = entity->transform->getPosition() + AEVec2(0, 5.f);
		AEVec2Lerp(&lerped, &position, &target, 1.0f - static_cast<float>(exp(-smoothing * AEFrameRateControllerGetFrameTime())));
		entity->transform->setPosition(lerped);
	}
}

void DamageNumbers::fixedUpdate()
{
}

void DamageNumbers::destroy()
{

}