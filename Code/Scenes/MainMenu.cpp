/******************************************************************************/
/*!
\file   MainMenu.cpp
\author Tai Qian Yi
\par    Email: t.qianyi\@digipen.edu
\par    DigiPen login: t.qianyi
\par    Course: CSD1451
\par    Section B
\brief  This file contains the definitions of functions for Main Menu
*/
/******************************************************************************/

#include "MainMenu.hpp"
#include "../Code/SoloBehavior/RunManager.hpp"
#include "../Code/SoloBehavior/Player.hpp"
#include "../Code/SoloBehavior/PauseMenu.hpp"
#include "../Code/SoloBehavior/SettingsScreen.hpp"
#include "../Code/SoloBehavior/CreditsScreen.hpp"
#include "../SoloBehavior/Occurence.hpp"
#include "../Audio_WZBJ_Pak.hpp"
#include "../SoloBehavior/TutorialScreen.hpp"

#include <fstream>

MainMenu::MainMenu()
{	
}

MainMenu::~MainMenu()
{
}

void MainMenu::Load()
{
	InitBlessingDatabase();
	InitEventsDatabase();

	meshSystem = &MeshGen::getInstance();
	meshSystem->CreateTexture("../../Assets/UI/button_border.png", "Button");

	enSystem = &EntityManager::getInstance();
	auto r = std::make_unique<Entity>("ROOT");
	enSystem->rootEntity = r.get();
	AEVec2 pos = { 0.f,0.f };
	AEVec2 scale = { 1.f, 1.f };
	enSystem->rootEntity->addComponent<Transform2D>(pos, scale, 0.f);
	enSystem->entities.push_back(std::move(r));

	meshSystem->CreateTexture("../../Assets/Images/MenuScene.png", "MenuImage");
	auto menuScreen = std::make_unique<Entity>("MENU_IMAGE");
	Entity* ms = menuScreen.get();
	pos = { 0.f ,0.f };
	scale = { 1800.f, 1280.f };
	ms->addComponent<Transform2D>(pos, scale, 0.f);
	ms->addComponent<Mesh>("Box", "MenuImage", Color(255, 255, 255, 1.f), 99, MeshType::BOX_T);
	enSystem->rootEntity->transform->AddChild(ms->transform);
	enSystem->entities.push_back(std::move(menuScreen));

	


	auto title_en = std::make_unique<Entity>("TITLE");
	Entity* te = title_en.get();
	pos = { 0.f ,300.f };
	scale = { 1525.f, 445.f };
	te->addComponent<Transform2D>(pos, scale, 0.f);
	te->addComponent<TextBox>("THE HEAVENS MOVE", 1.5f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);
	enSystem->rootEntity->transform->AddChild(te->transform);
	enSystem->entities.push_back(std::move(title_en));


	////////////////////////////////////////////////
	// 
	// SETTINGS SCREEN
	//
	////////////////////////////////////////////////
	auto ss = std::make_unique<Entity>("SettingsScreen");
	pos = { 0.f, 0.f };
	scale = { 1.f, 1.f };
	ss->addComponent<Transform2D>(pos, scale, 0.f);
	SettingsScreen* settings = ss->addComponent<SettingsScreen>();

	////////////////////////////////////////////////
	// 
	// CREDITS SCREEN
	//
	////////////////////////////////////////////////
	auto cs = std::make_unique<Entity>("CreditsScreen");
	pos = { 0.f, 0.f };
	scale = { 1.f, 1.f };
	cs->addComponent<Transform2D>(pos, scale, 0.f);
	CreditsScreen* credits = cs->addComponent<CreditsScreen>();

	////////////////////////////////////////////////
	// 
	// START BUTTON
	//
	////////////////////////////////////////////////
	std::ifstream ifs("Assets/SaveFile.json");
	if (ifs.good()) {
		auto b = std::make_unique<Entity>("START BUTTON");
		Entity* sb = b.get();
		pos = { 0.f,150.f };
		scale = { 300.f, 80.f };
		sb->addComponent<Transform2D>(pos, scale, 0.f);
		sb->addComponent<Mesh>("Box", "Button", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);


		Button* startButton = sb->addComponent<Button>();
		startButton->SetOnClick([this]() {SwitchToGame(); });
		startButton->SetNormalColor(Color{ 200,200,200,1 });
		startButton->SetHighlightedColor(Color{ 255,255,255,1 });
		sb->addComponent<TextBox>("CONTINUE", 0.6f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);
		enSystem->rootEntity->transform->AddChild(sb->transform);
		enSystem->entities.push_back(std::move(b));

		settings->AddPrevDisplayEntity(sb);
		credits->AddPrevDisplayEntity(sb);
	}


	////////////////////////////////////////////////
	// 
	// NEW GAME BUTTON
	//
	////////////////////////////////////////////////
	auto ng = std::make_unique<Entity>("NEW GAME BUTTON");
	Entity* ngb = ng.get();
	pos = { 0.f, 50.f };
	scale = { 300.f, 80.f };
	ng->addComponent<Transform2D>(pos, scale, 0.f);
	ng->addComponent<Mesh>("Box", "Button", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);


	Button* newGameButton = ngb->addComponent<Button>();
	newGameButton->SetOnClick([this]() {PlayNewSave(); });
	newGameButton->SetNormalColor(Color{ 200,200,200,1 });
	newGameButton->SetHighlightedColor(Color{ 255,255,255,1 });
	ng->addComponent<TextBox>("NEW GAME", 0.6f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);

	enSystem->rootEntity->transform->AddChild(ngb->transform);
	enSystem->entities.push_back(std::move(ng));


	////////////////////////////////////////////////
	// 
	// HOW TO PLAY BUTTON
	//
	////////////////////////////////////////////////
	auto htp = std::make_unique<Entity>("HOW TO PLAY BUTTON");
	Entity* htpb = htp.get();
	pos = { 0.f, -50.f };
	scale = { 300.f, 80.f };
	htp->addComponent<Transform2D>(pos, scale, 0.f);
	htp->addComponent<Mesh>("Box", "Button", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);

	Button* HTPButton = htpb->addComponent<Button>();
	HTPButton->SetNormalColor(Color{ 200,200,200,1 });
	HTPButton->SetHighlightedColor(Color{ 255,255,255,1 });
	htp->addComponent<TextBox>("HOW TO PLAY", 0.6f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);

	enSystem->rootEntity->transform->AddChild(htpb->transform);
	enSystem->entities.push_back(std::move(htp));


	////////////////////////////////////////////////
	// 
	// CREDITS BUTTON
	//
	////////////////////////////////////////////////
	auto creditsB = std::make_unique<Entity>("CREDITS BUTTON");
	Entity* creditsB_en = creditsB.get();
	pos = { 0.f,-150.f };
	scale = { 300.f, 80.f };
	creditsB_en->addComponent<Transform2D>(pos, scale, 0.f);
	creditsB_en->addComponent<Mesh>("Box", "Button", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);

	Button* creditsButton = creditsB_en->addComponent<Button>();
	creditsButton->SetNormalColor(Color{ 200,200,200,1 });
	creditsButton->SetHighlightedColor(Color{ 255,255,255,1 });
	creditsB_en->addComponent<TextBox>("CREDITS", 0.6f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);
	enSystem->rootEntity->transform->AddChild(creditsB_en->transform);
	enSystem->entities.push_back(std::move(creditsB));

	////////////////////////////////////////////////
	// 
	// SETTINGS BUTTON
	//
	////////////////////////////////////////////////
	auto settingsB = std::make_unique<Entity>("SETTINGS BUTTON");
	Entity* settingsB_en = settingsB.get();
	pos = { 0.f,-250.f };
	scale = { 300.f, 80.f };
	settingsB_en->addComponent<Transform2D>(pos, scale, 0.f);
	settingsB_en->addComponent<Mesh>("Box", "Button", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);


	Button* settingsButton = settingsB_en->addComponent<Button>();
	settingsButton->SetNormalColor(Color{ 200,200,200,1 });
	settingsButton->SetHighlightedColor(Color{ 255,255,255,1 });
	settingsB_en->addComponent<TextBox>("SETTINGS", 0.6f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);
	enSystem->rootEntity->transform->AddChild(settingsB_en->transform);
	enSystem->entities.push_back(std::move(settingsB));
	


	////////////////////////////////////////////////
	// 
	// QUIT BUTTON
	//
	////////////////////////////////////////////////
	auto e = std::make_unique<Entity>("QUIT BUTTON");
	Entity* qb = e.get();
	pos = { 0.f,-350.f };
	scale = { 300.f, 80.f };
	qb->addComponent<Transform2D>(pos, scale, 0.f);
	qb->addComponent<Mesh>("Box", "Button", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);


	Button* quitButton = qb->addComponent<Button>();
	quitButton->SetOnClick([this]() {QuitGame(); });
	quitButton->SetNormalColor(Color{ 200,200,200,1 });
	quitButton->SetHighlightedColor(Color{ 255,255,255,1 });
	qb->addComponent<TextBox>("QUIT", 0.6f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);

	enSystem->rootEntity->transform->AddChild(qb->transform);
	enSystem->entities.push_back(std::move(e));

	////////////////////////////////////////////////
	// 
	// TUTORIAL SCREEN
	//
	////////////////////////////////////////////////
	auto tut_s = std::make_unique<Entity>("TutorialScreen");
	pos = { 0.f, 0.f };
	scale = { 1.f, 1.f };
	tut_s->addComponent<Transform2D>(pos, scale, 0.f);
	TutorialScreen* tutorial = tut_s->addComponent<TutorialScreen>(TutorialScreen::TUTORIAL_TYPE::HOW_TO_PLAY);
	enSystem->rootEntity->transform->AddChild(tut_s->transform);
	enSystem->entities.push_back(std::move(tut_s));
	tutorial->ShowTutorial(false);
	HTPButton->SetOnClick([this, tutorial]() {tutorial->ShowTutorial(true); });

	settings->AddPrevDisplayEntity(ms);
	settings->AddPrevDisplayEntity(te);
	settings->AddPrevDisplayEntity(ngb);
	settings->AddPrevDisplayEntity(creditsB_en);
	settings->AddPrevDisplayEntity(settingsB_en);
	settings->AddPrevDisplayEntity(qb);

	enSystem->rootEntity->transform->AddChild(ss->transform);
	enSystem->entities.push_back(std::move(ss));

	//add the settings button on click function after to avoid potential problems
	settingsButton->SetOnClick([this, settings]() {settings->ShowSettings(true); });

	credits->AddPrevDisplayEntity(ms);
	credits->AddPrevDisplayEntity(te);
	credits->AddPrevDisplayEntity(ngb);
	credits->AddPrevDisplayEntity(creditsB_en);
	credits->AddPrevDisplayEntity(settingsB_en);
	credits->AddPrevDisplayEntity(qb);

	enSystem->rootEntity->transform->AddChild(cs->transform);
	enSystem->entities.push_back(std::move(cs));

	//add the credits button on click function after to avoid potential problems
	creditsButton->SetOnClick([this, credits]() {credits->ShowCredits(true); });


	if (RunManager::Instance().game_won)
	{
		std::cout << "GAME WON!!!!" << std::endl;
		credits->ShowCredits(true);
	}
	else
	{
		credits->ShowCredits(false);
	}

	////////////////////////////////////////////////
	// 
	// TRANSITION SCREEN
	//
	////////////////////////////////////////////////

	auto ts = std::make_unique<Entity>("TransitionScreen");
	pos = { 0.f, 0.f };
	scale = { (float)AEGfxGetWindowWidth(), (float)AEGfxGetWindowHeight() };
	ts->addComponent<Transform2D>(pos, scale, 0.f);
	ts->addComponent<Mesh>("Box", Color(20, 20, 20, 1), 999, MeshType::BOX_B);
	ts_comp = ts->addComponent<TransitionScreen>(T_OUT);
	enSystem->rootEntity->transform->AddChild(ts->transform);
	enSystem->entities.push_back(std::move(ts));

	AudioManager::GetInstance()->StopAllTracks(true, AudioManager::AUDIO_MAINMENU_BGM);
	AudioManager::GetInstance()->PlayTrack(AudioManager::AUDIO_MAINMENU_BGM, true);

	RunManager::Instance().game_paused = false;
}

void MainMenu::SwitchToGame()
{
	ts_comp->TransitionToScene(GameStateManager::BASE_CAMP);
	AudioManager::GetInstance()->PlaySFX(AudioManager::SFX_GAME_START);
}

void MainMenu::PlayNewSave()
{
	RunManager::Instance().ResetSave();
	RunManager::Instance().ResetTutorials();
	RunManager::Instance().SaveRun();
	SwitchToGame();
}

void MainMenu::QuitGame()
{
	int result = MessageBox(
		AESysGetWindowHandle(),
		"Are you sure you want to quit? Unsaved progress will be lost",
		"Confirm Exit",
		MB_YESNO | MB_ICONQUESTION
	);

	if (result == IDYES)
	GameManager::GetInstance()->quitGame = true;
}


void MainMenu::Unload()
{
	EntityManager::getInstance().needsCleanup = true;
    for (auto& e : enSystem->entities) {
        e->toDestroy = true;
    }
}
