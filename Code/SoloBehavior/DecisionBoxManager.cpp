#include "DecisionBoxManager.hpp"
#include "../Code/SoloBehavior/RunManager.hpp"

void DecisionBoxManager::ToggleDecisionBox(bool toggle)
{
	for (Transform2D* child : entity->transform->children)
	{
		child->entity->isActive = toggle;
	}
	RunManager::Instance().playerCanMove = !toggle;
}

void DecisionBoxManager::awake()
{
}

void DecisionBoxManager::init()
{
	leftButton = entity->transform->children.at(1)->entity->getComponent<Button>();
	rightButton = entity->transform->children.at(2)->entity->getComponent<Button>();
}

void DecisionBoxManager::update()
{
	//leftButton->SetOnClick([this]() { ToggleDecisionBox(false); });
	//rightButton->SetOnClick([this]() { ToggleDecisionBox(false); });
}

void DecisionBoxManager::fixedUpdate()
{
}

void DecisionBoxManager::destroy()
{
}
