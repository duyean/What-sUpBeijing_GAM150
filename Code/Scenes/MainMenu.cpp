/*!
@file SplashScreen.cpp
@author Tai Qian Yi (t.qianyi)
@course CSD11451
@section B
@Final Project
@date 13/1/26
@brief
This file contains the definitions for the collection of functions in SplashScreen.h
*//*______________________________________________________________________*/
#include "MainMenu.hpp"
#include "../Code/SoloBehavior/RunManager.hpp"
#include "../Code/SoloBehavior/Player.hpp"

MainMenu::MainMenu()
{	
}

MainMenu::~MainMenu()
{
}


/*!
@brief Initialize splash screen variables

Overwrites virtual GameState::Init().
This function loads splash screen image

@param void
@return void
*//*______________________________________________________________*/
void MainMenu::Load()
{
	meshSystem = &MeshGen::getInstance();
	meshSystem->CreateTexture("../../Assets/UI/button_border.png", "Button");

	enSystem = &EntityManager::getInstance();
	auto r = std::make_unique<Entity>("ROOT");
	enSystem->rootEntity = r.get();
	AEVec2 pos = { 0.f,0.f };
	AEVec2 scale = { 1.f, 1.f };
	enSystem->rootEntity->addComponent<Transform2D>(pos, scale, 0.f);
	enSystem->entities.push_back(std::move(r));


	/*auto title_en = std::make_unique<Entity>("TITLE");
	Entity* te = title_en.get();
	pos = { -1400.f,800.f };
	scale = { 1525.f, 445.f };
	te->addComponent<Transform2D>(pos, scale, 0.f);
	te->addComponent<TextMesh>(AEVec2{ pos.x , pos.y }, 1.5, "THE HEAVENS MOVE", Color{ 255,255,255,1 });
	enSystem->rootEntity->transform->AddChild(te->transform);
	enSystem->entities.push_back(std::move(title_en));*/


	//////////////////////////////////////////////////
	//// 
	//// START BUTTON
	////
	//////////////////////////////////////////////////

	//auto b = std::make_unique<Entity>("START BUTTON");
	//Entity* sb = b.get();
	//pos = { 0.f,0.f };
	//scale = { 300.f, 80.f };
	//sb->addComponent<Transform2D>(pos, scale, 0.f);
	//sb->addComponent<Mesh>("Box", "Button", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);


	//Button* startButton = sb->addComponent<Button>();
	//startButton->SetOnClick([this]() {SwitchToGame(); });
	//startButton->SetNormalColor(Color{ 200,200,200,1 });
	//startButton->SetHighlightedColor(Color{ 255,255,255,1 });
	//sb->addComponent<TextMesh>(AEVec2{ pos.x - 100.f, pos.y - 40.f }, 0.6, "PLAY", Color{ 255, 255, 255, 1.f });

	//enSystem->rootEntity->transform->AddChild(sb->transform);
	//enSystem->entities.push_back(std::move(b));


	//////////////////////////////////////////////////
	//// 
	//// NEW GAME BUTTON
	////
	//////////////////////////////////////////////////

	//auto ng = std::make_unique<Entity>("NEW GAME BUTTON");
	//Entity* ngb = ng.get();
	//pos = { 0.f,-100.f };
	//scale = { 300.f, 80.f };
	//ng->addComponent<Transform2D>(pos, scale, 0.f);
	//ng->addComponent<Mesh>("Box", "Button", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);


	//Button* newGameButton = ngb->addComponent<Button>();
	//newGameButton->SetOnClick([this]() {PlayNewSave(); });
	//newGameButton->SetNormalColor(Color{ 200,200,200,1 });
	//newGameButton->SetHighlightedColor(Color{ 255,255,255,1 });
	//ng->addComponent<TextMesh>(AEVec2{ pos.x - 300.f, pos.y - 340.f }, 0.6, "NEW GAME", Color{ 255, 255, 255, 1.f });


	//enSystem->rootEntity->transform->AddChild(ngb->transform);
	//enSystem->entities.push_back(std::move(ng));


	//////////////////////////////////////////////////
	//// 
	//// QUIT BUTTON
	////
	//////////////////////////////////////////////////

	//auto e = std::make_unique<Entity>("QUIT BUTTON");
	//Entity* qb = e.get();
	//pos = { 0.f,-200.f };
	//scale = { 300.f, 80.f };
	//qb->addComponent<Transform2D>(pos, scale, 0.f);
	//qb->addComponent<Mesh>("Box", "Button", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);


	//Button* quitButton = qb->addComponent<Button>();
	//quitButton->SetOnClick([this]() {QuitGame(); });
	//quitButton->SetNormalColor(Color{ 200,200,200,1 });
	//quitButton->SetHighlightedColor(Color{ 255,255,255,1 });
	//qb->addComponent<TextMesh>(AEVec2{ pos.x - 100.f, pos.y -640.f}, 0.6, "QUIT", Color{ 255, 255, 255, 1.f });


	//enSystem->rootEntity->transform->AddChild(qb->transform);
	//enSystem->entities.push_back(std::move(e));

	auto test = std::make_unique<Entity>("Text");
	pos = { 300.f, 0.f };
	scale = { 300.f, 80.f };
	test->addComponent<Transform2D>(pos, scale, 0.f);
	test->addComponent<Mesh>("Box", Color(50, 50, 50, 1), 100, MeshType::BOX_B);
	TextMesh* mytext = test->addComponent<TextMesh>(AEVec2{ pos.x, pos.y }, 0.6, "test", Color{ 255, 255, 255, 1.f }, TextAlignment::CENTER);
	test->transform->AddChild(mytext->entity->transform);
	enSystem->rootEntity->transform->AddChild(test->transform);
	enSystem->entities.push_back(std::move(test));

	auto t = std::make_unique<Entity>("lineH");
	pos = { 0.f, 0.f };
	scale = { 2, (float)AEGfxGetWindowHeight() };
	t->addComponent<Transform2D>(pos, scale, 0.f);
	t->addComponent<Mesh>("Box", Color(50, 50, 50, 1), 100, MeshType::BOX_B);
	enSystem->rootEntity->transform->AddChild(t->transform);
	enSystem->entities.push_back(std::move(t));

	auto l = std::make_unique<Entity>("LineV");
	pos = { 0.f, 0.f };
	scale = { (float)AEGfxGetWindowWidth(), 2 };
	l->addComponent<Transform2D>(pos, scale, 0.f);
	l->addComponent<Mesh>("Box", Color(50, 50, 50, 1), 100, MeshType::BOX_B);
	enSystem->rootEntity->transform->AddChild(l->transform);
	enSystem->entities.push_back(std::move(l));

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
	ts_comp = ts->addComponent<TransitionScreen>(T_NONE);
	enSystem->rootEntity->transform->AddChild(ts->transform);
	enSystem->entities.push_back(std::move(ts));

}

void MainMenu::SwitchToGame()
{
	ts_comp->TransitionToScene(GameStateManager::BASE_CAMP);
}

void MainMenu::PlayNewSave()
{
	RunManager::Instance().ResetSave();
	SwitchToGame();
}

void MainMenu::QuitGame()
{
	GameManager::GetInstance()->quitGame = true;
}


/*!
@brief Clears splash screen variables

Overwrites virtual GameState::Exit().
This function frees splash screen image used.

@param void
@return void
*//*______________________________________________________________*/
void MainMenu::Unload()
{
	EntityManager::getInstance().needsCleanup = true;
	for (auto& e : enSystem->entities) {
		e->toDestroy = true;
	}
}
