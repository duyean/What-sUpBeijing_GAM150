#include "CombatUIManager.hpp"
#include "DamageNumber.hpp"
#include <string>


CombatUIManager* CombatUIManager::instance;

void CombatUIManager::awake()
{
	if (!instance)
	{
		instance = this;
	}

	MeshGen::getInstance().SetFont("../../Assets/Fonts/liberation-mono.ttf", "liberi", 50);
}

void CombatUIManager::init()
{

}

void CombatUIManager::CreateDamageNumber(AEVec2 pos, Game::DamageInfo info)
{
	auto e = std::make_unique<Entity>("DamageNumber");
	AEVec2 scale = { 150, 50 };
	e->addComponent<Transform2D>(pos, scale, 0.f);
	e->addComponent<DamageNumbers>();
	auto di = e->getComponent<DamageNumbers>();
	di->lifetime = 1.f;
	di->text = std::to_string((int)info.damage);
	di->textColor = DamageNumbers::GetElementColor(info.elementType);
	di->size = info.isCritical ? 2.1f : 0.7f;
	EntityManager::getInstance().rootEntity->transform->AddChild(e->transform);
	damageNumbers.push(std::move(e));
	//EntityManager::getInstance().entities.push_back(std::move(e)); //Make the entity and add it to the entityList
}
void CombatUIManager::CreateMessageText(AEVec2 position, std::string text, Color color)
{
	auto e = std::make_unique<Entity>("Message");
	AEVec2 scale = { 150, 50 };
	e->addComponent<Transform2D>(position, scale, 0.f);
	e->addComponent<DamageNumbers>();
	auto di = e->getComponent<DamageNumbers>();
	di->lifetime = 1.5f;
	di->text = text;
	di->textColor = color;
	EntityManager::getInstance().rootEntity->transform->AddChild(e->transform);
	messages.push(std::move(e));
	//EntityManager::getInstance().entities.push_back(std::move(e)); //Make the entity and add it to the entityList
}

void CombatUIManager::update()
{
	//Handle damageNumbers
	if (!damageNumbers.empty())
	{
		if (dnDelay <= 0)
		{
			EntityManager::getInstance().entities.push_back(std::move(damageNumbers.front()));
			damageNumbers.pop();
			dnDelay = 0.1f;
		}
		else
		{
			dnDelay -= 1.0 / AEFrameRateControllerGetFrameRate();
		}
	}

	//Handle messages
	if (!messages.empty())
	{
		if (messDelay <= 0)
		{
			EntityManager::getInstance().entities.push_back(std::move(messages.front()));
			messages.pop();
			messDelay = 0.1f;
		}
		else
		{
			messDelay -= 1.0 / AEFrameRateControllerGetFrameRate();
		}
	}
}

void CombatUIManager::fixedUpdate()
{

}

void CombatUIManager::destroy()
{

}