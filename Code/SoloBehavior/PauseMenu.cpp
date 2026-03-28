#include "PauseMenu.hpp"
#include "../BaseSystems/Engine/EventSystem.hpp"
#include "../Code/SceneHandler_WZBJ_Pak.hpp"
#include "../Code/SoloBehavior/RunManager.hpp"

void PauseMenu::awake()
{
	enSystem = &EntityManager::getInstance();

	auto ss = std::make_unique<Entity>("SettingsScreen");
	AEVec2 pos = { 0.f, 0.f };
	AEVec2 scale = { 1.f, 1.f };
	ss->addComponent<Transform2D>(pos, scale, 0.f);
	settings = ss->addComponent<SettingsScreen>();

	//background
	auto pause_bg = std::make_unique<Entity>("PAUSE BG");
	pos = { 0.f ,0.f };
	scale = { 1.f, 1.f };
	pause_bg->addComponent<Transform2D>(pos, scale, 0.f);
	pause_bg->addComponent<Mesh>("Box", Color(1, 1, 1, 0.5), 900, MeshType::BOX_B);
	entity->transform->AddChild(pause_bg->transform);
	settings->AddPrevDisplayEntity(pause_bg.get());


	//pause menu title
	auto title_pause = std::make_unique<Entity>("PAUSE TITLE");
	pos = { 0.f ,0.f };
	scale = { 1.f, 1.f };
	title_pause->addComponent<Transform2D>(pos, scale, 0.f);
	TextBox* ttb = title_pause->addComponent<TextBox>("PAUSE", 1.5f, TextBoxVAllign::TOP, TextBoxHAllign::CENTER);
	ttb->text_layer = 902;
	ttb->padding_v = 100.f;
	entity->transform->AddChild(title_pause->transform);
	settings->AddPrevDisplayEntity(title_pause.get());


	//Quit to main menu button
	auto qmmb = std::make_unique<Entity>("QUIT MAIN MENU BUTTON");
	pos = { 0.f, 0.f };
	scale = { 0.15f, 0.1f };
	qmmb->addComponent<Transform2D>(pos, scale, 0.f);
	qmmb->addComponent<Mesh>("Box", "Button", Color(255, 255, 255, 1.f), 901, MeshType::BOX_T);
	entity->transform->AddChild(qmmb->transform);

	Button* quitMMButton = qmmb->addComponent<Button>();
	quitMMButton->SetOnClick([this]() {QuitToMainMenu(); });
	quitMMButton->SetNormalColor(Color{ 200,200,200,1 });
	quitMMButton->SetHighlightedColor(Color{ 255,255,255,1 });
	TextBox* tb1 = qmmb->addComponent<TextBox>("MAIN MENU", 0.5f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);
	tb1->text_layer = 902;
	settings->AddPrevDisplayEntity(qmmb.get());

	//Quit button
	auto qb = std::make_unique<Entity>("PAUSE QUIT BUTTON");
	pos = { 0.f, -200.f };
	scale = { 0.15f, 0.1f };
	qb->addComponent<Transform2D>(pos, scale, 0.f);
	qb->addComponent<Mesh>("Box", "Button", Color(255, 255, 255, 1.f), 901, MeshType::BOX_T);
	entity->transform->AddChild(qb->transform);

	Button* quitButton = qb->addComponent<Button>();
	quitButton->SetOnClick([this]() {QuitGame(); });
	quitButton->SetNormalColor(Color{ 200,200,200,1 });
	quitButton->SetHighlightedColor(Color{ 255,255,255,1 });
	TextBox* tb2 = qb->addComponent<TextBox>("QUIT GAME", 0.5f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);
	tb2->text_layer = 902;
	settings->AddPrevDisplayEntity(qb.get());

	//Settings Button
	auto settingsB = std::make_unique<Entity>("SETTINGS BUTTON");
	Entity* settingsB_en = settingsB.get();
	pos = { 0.f,-100.f };
	scale = { 0.15f, 0.1f };
	settingsB_en->addComponent<Transform2D>(pos, scale, 0.f);
	settingsB_en->addComponent<Mesh>("Box", "Button", Color(255, 255, 255, 1.f), 901, MeshType::BOX_T);
	entity->transform->AddChild(settingsB->transform);

	Button* settingsButton = settingsB_en->addComponent<Button>();
	settingsButton->SetNormalColor(Color{ 200,200,200,1 });
	settingsButton->SetHighlightedColor(Color{ 255,255,255,1 });
	TextBox* tb3 = settingsB_en->addComponent<TextBox>("SETTINGS", 0.5f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);
	tb3->text_layer = 902;
	settings->AddPrevDisplayEntity(settingsB.get());

	
	//Resume Button
	auto rb = std::make_unique<Entity>("RESUME BUTTON");
	pos = { 0.f, 100.f };
	scale = { 0.15f, 0.1f };
	rb->addComponent<Transform2D>(pos, scale, 0.f);
	rb->addComponent<Mesh>("Box", "Button", Color(255, 255, 255, 1.f), 901, MeshType::BOX_T);
	entity->transform->AddChild(rb->transform);

	Button* resumeButton = rb->addComponent<Button>();
	resumeButton->SetOnClick([this]() {ResumeGame(); });
	resumeButton->SetNormalColor(Color{ 200,200,200,1 });
	resumeButton->SetHighlightedColor(Color{ 255,255,255,1 });
	TextBox* tb4 = rb->addComponent<TextBox>("CONTINUE", 0.5f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);
	tb4->text_layer = 902;
	settings->AddPrevDisplayEntity(rb.get());

	//push back all the display entities to the entity system
	enSystem->entities.push_back(std::move(pause_bg));
	enSystem->entities.push_back(std::move(title_pause));
	enSystem->entities.push_back(std::move(qmmb));
	enSystem->entities.push_back(std::move(qb));
	enSystem->entities.push_back(std::move(rb));
	enSystem->entities.push_back(std::move(settingsB));
	
	
	//push the settings screen entity last
	enSystem->entities.push_back(std::move(ss));

	//add the settings button on click function after to avoid potential problems
	settingsButton->SetOnClick([this]() {settings->ShowSettings(true); });

	

	for (Transform2D* child : entity->transform->children)
	{
		child->entity->isActive = false;
	}
}

void PauseMenu::init()
{
	ts_comp = enSystem->FindByNameGLOBAL("TransitionScreen")->getComponent<TransitionScreen>();	
}

void PauseMenu::update()
{
	if (RunManager::Instance().game_paused == false)
	{
		settings->ShowSettings(false);
	}

	if (settings->IsDisplaying()) return;

	if (RunManager::Instance().game_paused)
	{
		for (Entity* en : prevDisplay)
		{
			en->isActive = false;
		}
	}

	for (Transform2D* child : entity->transform->children)
	{
		child->entity->isActive = RunManager::Instance().game_paused;
	}
}

void PauseMenu::fixedUpdate()
{

}

void PauseMenu::destroy()
{

}

void PauseMenu::ResumeGame()
{
	RunManager::Instance().game_paused = false;
}

void PauseMenu::QuitGame()
{
	GameManager::GetInstance()->quitGame = true;
}

void PauseMenu::QuitToMainMenu()
{
	if(ts_comp)
		ts_comp->TransitionToScene(GameStateManager::MAIN_MENU);
}

void PauseMenu::AddPrevDisplayEntity(Entity* en)
{
	prevDisplay.push_back(en);
}