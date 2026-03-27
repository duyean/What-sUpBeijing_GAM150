#include "CreditsScreen.hpp"
#include "../BaseSystems/Engine/EventSystem.hpp"
#include "../Code/SoloBehavior/PauseMenu.hpp"
#include "../Audio_WZBJ_Pak.hpp"

void CreditsScreen::ShowCredits(bool canShow)
{
	for (Entity* en : prevDisplay)
	{
		en->isActive = !canShow;
	}

	for (Transform2D* child : entity->transform->children)
	{
		child->entity->isActive = canShow;
	}

	isDisplaying = canShow;
}

void CreditsScreen::awake()
{
	enSystem = &EntityManager::getInstance();

	//background
	auto credits_bg = std::make_unique<Entity>("CREDITS BG");
	AEVec2 pos = { 0.f ,0.f };
	AEVec2 scale = { (float)AEGfxGetWindowWidth(), (float)AEGfxGetWindowHeight() };
	credits_bg->addComponent<Transform2D>(pos, scale, 0.f);
	credits_bg->addComponent<Mesh>("Box", Color(1, 1, 1, 0.5), 499, MeshType::BOX_B);
	entity->transform->AddChild(credits_bg->transform);

	//pause menu title
	auto title_credits = std::make_unique<Entity>("CREDITS TITLE");
	pos = { 0.f ,(float)AEGfxGetWindowHeight()/2.f };
	scale = { 1.f, 1.f };
	title_credits->addComponent<Transform2D>(pos, scale, 0.f);
	TextBox* ttb = title_credits->addComponent<TextBox>("CREDITS", 1.5f, TextBoxVAllign::TOP, TextBoxHAllign::CENTER);
	ttb->padding_v = 100.f;
	entity->transform->AddChild(title_credits->transform);


	


	//Close Button
	auto close_b = std::make_unique<Entity>("CLOSE BUTTON");
	pos = { 0.f, -300.f };
	scale = { 200.f, 80.f };
	close_b->addComponent<Transform2D>(pos, scale, 0.f);
	close_b->addComponent<Mesh>("Box", "Button", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);
	entity->transform->AddChild(close_b->transform);

	Button* closeButton = close_b->addComponent<Button>();
	closeButton->SetOnClick([this]() {ShowCredits(false); });
	closeButton->SetNormalColor(Color{ 200,200,200,1 });
	closeButton->SetHighlightedColor(Color{ 255,255,255,1 });
	close_b->addComponent<TextBox>("CLOSE", 0.5f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);
	

	enSystem->entities.push_back(std::move(credits_bg));
	enSystem->entities.push_back(std::move(title_credits));
	enSystem->entities.push_back(std::move(close_b));
}

void CreditsScreen::init()
{
	
}

void CreditsScreen::update()
{
	
}

void CreditsScreen::fixedUpdate()
{

}

void CreditsScreen::destroy()
{

}

void CreditsScreen::AddPrevDisplayEntity(Entity* en)
{
	prevDisplay.push_back(en);
}
