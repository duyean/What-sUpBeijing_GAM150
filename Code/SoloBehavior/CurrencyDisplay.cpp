#include "CurrencyDisplay.hpp"
#include "../BaseSystems/Engine/EventSystem.hpp"
#include "../Code/SoloBehavior/RunManager.hpp"

void CurrencyDisplay::DisplayCurrency()
{
	//std::string curr = std::to_string(RunManager::Instance().GetCurrency());
	//textbox->text = curr;
}
	
void CurrencyDisplay::awake()
{
	enSystem = &EntityManager::getInstance();

	auto c_display = std::make_unique<Entity>("CURRENCY COUNT DISPLAY");
	AEVec2 pos = { 0.f , 0.f };
	AEVec2 scale = { 1.f, 1.f };
	c_display->addComponent<Transform2D>(pos, scale, 0.f);
	textbox = c_display->addComponent<TextBox>("COINS", 0.6f, TextBoxVAllign::CENTER, TextBoxHAllign::LEFT);
	entity->transform->AddChild(c_display->transform);
	enSystem->entities.push_back(std::move(c_display));
}

void CurrencyDisplay::init()
{	
	DisplayCurrency();
}

void CurrencyDisplay::update()
{
	DisplayCurrency();
}

void CurrencyDisplay::fixedUpdate()
{

}

void CurrencyDisplay::destroy()
{

}

