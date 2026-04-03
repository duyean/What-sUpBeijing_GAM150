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

	scrollOffset = startingPos;
	isDisplaying = canShow;

	title->getComponent<Transform2D>()->setPosition({ 0.f, scrollOffset });
	LeftText->getComponent<Transform2D>()->setPosition({ -(float)AEGfxGetWindowWidth() / 2.f + 400.f, scrollOffset });
	RightText->getComponent<Transform2D>()->setPosition({ (float)AEGfxGetWindowWidth() / 2.f - 400.f, scrollOffset });
	Footer->getComponent<Transform2D>()->setPosition({ 0.f, scrollOffset - 2000.f });
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

	auto top_mask = std::make_unique<Entity>("TOP MASK");
	pos = { 0.f ,(float)AEGfxGetWindowHeight() / 2.f };
	scale = { (float)AEGfxGetWindowWidth(), 200.f };
	top_mask->addComponent<Transform2D>(pos, scale, 0.f);
	top_mask->addComponent<Mesh>("Box", Color(0, 0, 0, 1), 900, MeshType::BOX_B);
	entity->transform->AddChild(top_mask->transform);

	auto d_logo = std::make_unique<Entity>("DIGIPEN LOGO");
	pos = { 0.f , 0.f};
	scale = { 500.f, 180.f };
	d_logo->addComponent<Transform2D>(pos, scale, 0.f);
	d_logo->addComponent<Mesh>("Box", "SplashLogo", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);
	entity->transform->AddChild(d_logo->transform);
	logo = d_logo.get();

	//pause menu title
	auto title_credits = std::make_unique<Entity>("CREDITS TITLE");
	pos = { scrollOffset ,(float)AEGfxGetWindowHeight()/2.f };
	scale = { 1.f, 1.f };
	title_credits->addComponent<Transform2D>(pos, scale, 0.f);
	TextBox* ttb = title_credits->addComponent<TextBox>("CREDITS", 1.5f, TextBoxVAllign::TOP, TextBoxHAllign::CENTER);
	ttb->padding_v = 300.f;
	entity->transform->AddChild(title_credits->transform);
	title = title_credits.get();

	auto credits_text_l = std::make_unique<Entity>("CREDITS TEXT LEFT");
	pos = { (-(float)AEGfxGetWindowWidth() / 2.f + 400.f) ,(float)AEGfxGetWindowHeight() / 2.f };
	scale = { 1.f, 1.f };
	credits_text_l->addComponent<Transform2D>(pos, scale, 0.f);
	TextBox* cdt_l = credits_text_l->addComponent<TextBox>(
		"Engine Program:\nCombat Program:\nMap Program:\nAudio and Data Program:\nUi Program:"
		"\n\nFaculty and Advisors\n"
		"\n\n\n"
		"\nCreated at Digipen Institute of Technology Singapore\n\n"
		"\nPresident\n\n"
		"Executives\n", 
		0.6f, TextBoxVAllign::TOP, TextBoxHAllign::LEFT);
	cdt_l->padding_v = 500.f;
	entity->transform->AddChild(credits_text_l->transform);
	LeftText = credits_text_l.get();

	auto credits_text_r = std::make_unique<Entity>("CREDITS TEXT RIGHT");
	pos = { ((float)AEGfxGetWindowWidth() / 2.f - 400.f) ,(float)AEGfxGetWindowHeight() / 2.f };
	scale = { 1.f, 1.f };
	credits_text_r->addComponent<Transform2D>(pos, scale, 0.f);
	TextBox* cdt_r = credits_text_r->addComponent<TextBox>(
		"Edmund\nWayne\nDaniel\nBryson\nQian Yi"
		"\n\n"
		"\nGerald Wong\nSoroor Malekmohammadi Faradounbeh\n"
		"\n\n\n\n"
		"\nClaude Comair\n"
		"\nJason Chu\nSamir Abou Samra\n\nMichele Comair\nAgenla Kugler\n\nErik Mohrmann\nBenjamin Ellinger\nMelvin Gonsalvez",
		0.6f, TextBoxVAllign::TOP, TextBoxHAllign::RIGHT);
	cdt_r->padding_v = 500.f;
	entity->transform->AddChild(credits_text_r->transform);
	RightText = credits_text_r.get();

	auto credits_text_footer = std::make_unique<Entity>("CREDITS TEXT FOOT");
	pos = { 0.f ,-(float)AEGfxGetWindowHeight() / 2.f };
	scale = { 1.f, 1.f };
	credits_text_footer->addComponent<Transform2D>(pos, scale, 0.f);
	TextBox* cdt_f = credits_text_footer->addComponent<TextBox>(
		"Thanks for playing!\nA game by Team WhatsUpBeijing",
		0.6f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);
	cdt_f->padding_v = 0.f;
	entity->transform->AddChild(credits_text_footer->transform);
	Footer = credits_text_footer.get();

	auto bottom_mask = std::make_unique<Entity>("BOTTOM MASK");
	pos = { 0.f ,-(float)AEGfxGetWindowHeight() / 2.f };
	scale = { (float)AEGfxGetWindowWidth(), 400.f };
	bottom_mask->addComponent<Transform2D>(pos, scale, 0.f);
	bottom_mask->addComponent<Mesh>("Box", Color(0, 0, 0, 1), 900, MeshType::BOX_B);
	entity->transform->AddChild(bottom_mask->transform);


	//Close Button
	auto close_b = std::make_unique<Entity>("CLOSE BUTTON");
	pos = { 550.f, 350.f };
	scale = { 50.f, 50.f };
	close_b->addComponent<Transform2D>(pos, scale, 0.f);
	close_b->addComponent<Mesh>("Box", Color(200, 1, 1, 1.f), 901, MeshType::BOX_B);
	entity->transform->AddChild(close_b->transform);

	Button* closeButton = close_b->addComponent<Button>();
	closeButton->SetOnClick([this]() {ShowCredits(false); });
	closeButton->SetNormalColor(Color{ 200,1,1,1 });
	closeButton->SetHighlightedColor(Color{ 255,1,1,1 });
	TextBox* cb_tb = close_b->addComponent<TextBox>("X", 0.5f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);
	cb_tb->text_layer = 920;

	enSystem->entities.push_back(std::move(credits_bg));
	enSystem->entities.push_back(std::move(top_mask));
	enSystem->entities.push_back(std::move(d_logo));
	enSystem->entities.push_back(std::move(title_credits));
	enSystem->entities.push_back(std::move(credits_text_l));
	enSystem->entities.push_back(std::move(credits_text_r));
	enSystem->entities.push_back(std::move(credits_text_footer));
	enSystem->entities.push_back(std::move(bottom_mask));
	enSystem->entities.push_back(std::move(close_b));
}

void CreditsScreen::init()
{
	scrollOffset = startingPos;
}

void CreditsScreen::update()
{
	scrollOffset += (float)AEFrameRateControllerGetFrameTime() * 100.f;
	logo->getComponent<Transform2D>()->setPosition({ 0.f, scrollOffset });
	title->getComponent<Transform2D>()->setPosition({ 0.f, scrollOffset});
	LeftText->getComponent<Transform2D>()->setPosition({ -(float)AEGfxGetWindowWidth() / 2.f + 400.f, scrollOffset });
	RightText->getComponent<Transform2D>()->setPosition({ (float)AEGfxGetWindowWidth() / 2.f - 400.f, scrollOffset });
	Footer->getComponent<Transform2D>()->setPosition({ 0.f, scrollOffset - 2200.f});

	if (scrollOffset >= 2700.f)
	{
		ShowCredits(false);
	}
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
