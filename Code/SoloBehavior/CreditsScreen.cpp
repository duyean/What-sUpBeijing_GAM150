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


	auto credits_text_l = std::make_unique<Entity>("CREDITS TEXT LEFT");
	pos = { (-(float)AEGfxGetWindowWidth() / 2.f + 400.f) ,(float)AEGfxGetWindowHeight() / 2.f };
	scale = { 1.f, 1.f };
	credits_text_l->addComponent<Transform2D>(pos, scale, 0.f);
	TextBox* cdt_l = credits_text_l->addComponent<TextBox>(
		"Engine Program:\nCombat Program:\nMap Program:\nAudio and Shop Program:\nUi Program:", 
		0.6f, TextBoxVAllign::TOP, TextBoxHAllign::LEFT);
	cdt_l->padding_v = 300.f;
	entity->transform->AddChild(credits_text_l->transform);

	auto credits_text_r = std::make_unique<Entity>("CREDITS TEXT RIGHT");
	pos = { ((float)AEGfxGetWindowWidth() / 2.f - 400.f) ,(float)AEGfxGetWindowHeight() / 2.f };
	scale = { 1.f, 1.f };
	credits_text_r->addComponent<Transform2D>(pos, scale, 0.f);
	TextBox* cdt_r = credits_text_r->addComponent<TextBox>(
		"edmund\nwayne\ndaniel\nbryson\nqian yi",
		0.6f, TextBoxVAllign::TOP, TextBoxHAllign::RIGHT);
	cdt_r->padding_v = 300.f;
	entity->transform->AddChild(credits_text_r->transform);

	auto credits_text_footer = std::make_unique<Entity>("CREDITS TEXT FOOT");
	pos = { 0.f ,-(float)AEGfxGetWindowHeight() / 2.f };
	scale = { 1.f, 1.f };
	credits_text_footer->addComponent<Transform2D>(pos, scale, 0.f);
	TextBox* cdt_f = credits_text_footer->addComponent<TextBox>(
		"Thanks for playing!\nA game by Team WhatsUpBeijing",
		0.6f, TextBoxVAllign::BOTTOM, TextBoxHAllign::CENTER);
	cdt_f->padding_v = -250.f;
	entity->transform->AddChild(credits_text_footer->transform);


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
	enSystem->entities.push_back(std::move(credits_text_l));
	enSystem->entities.push_back(std::move(credits_text_r));
	enSystem->entities.push_back(std::move(credits_text_footer));
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
