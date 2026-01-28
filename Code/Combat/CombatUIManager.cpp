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

	MeshGen::getInstance()->SetFont("Assets/Fonts/liberation-mono.ttf", "font1", 72);
}

void CombatUIManager::init()
{

}

void CombatUIManager::CreateDamageNumber(AEVec2 pos, Game::DamageInfo info)
{
	auto e = std::make_unique<Entity>("DamageNumber");
	AEVec2 scale = { 300, 100 };
	e->addComponent<Transform2D>(pos, scale, 0.f);
	e->addComponent<DamageNumbers>();
	auto di = e->getComponent<DamageNumbers>();
	di->lifetime = 1.f;
	di->text = std::to_string((int)info.damage);
	di->textColor = DamageNumbers::GetElementColor(info.elementType);
	EntityManager::getInstance()->entities.push_back(std::move(e)); //Make the entity and add it to the entityList
}
void CombatUIManager::CreateMessageText(AEVec2 position, std::string text, Color color)
{
	auto e = std::make_unique<Entity>("Message");
	AEVec2 scale = { 300, 100 };
	e->addComponent<Transform2D>(position, scale, 0.f);
	e->addComponent<DamageNumbers>();
	auto di = e->getComponent<DamageNumbers>();
	di->lifetime = 1.5f;
	di->text = text;
	di->textColor = color;
	EntityManager::getInstance()->entities.push_back(std::move(e)); //Make the entity and add it to the entityList
}

void CombatUIManager::update()
{

}

void CombatUIManager::fixedUpdate()
{

}

void CombatUIManager::destroy()
{

}