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
	meshSystem->CreateTexture("../../Assets/Images/Button.png", "Button");

	enSystem = &EntityManager::getInstance();
	auto r = std::make_unique<Entity>("ROOT");
	enSystem->rootEntity = r.get();
	AEVec2 pos = { 0.f,0.f };
	AEVec2 scale = { 1.f, 1.f };
	enSystem->rootEntity->addComponent<Transform2D>(pos, scale, 0.f);
	enSystem->entities.push_back(std::move(r));


	////////////////////////////////////////////////
	// 
	// START BUTTON
	//
	////////////////////////////////////////////////

	auto b = std::make_unique<Entity>("START BUTTON");
	Entity* sb = b.get();
	pos = { 0.f,0.f };
	scale = { 200.f, 80.f };
	sb->addComponent<Transform2D>(pos, scale, 0.f);
	sb->addComponent<Mesh>("Box", "Button", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);


	Button* startButton = sb->addComponent<Button>();
	startButton->SetOnClick([this]() {SwitchToGame(); });
	startButton->SetNormalColor(Color{ 0,200,0,1 });
	startButton->SetHighlightedColor(Color{ 0,255,0,1 });
	sb->addComponent<TextMesh>(AEVec2{ pos.x + 100.f , pos.y + 30.f }, 0.6, "PLAY", Color{1,1,1,1});


	enSystem->rootEntity->transform->AddChild(sb->transform);
	enSystem->entities.push_back(std::move(b));


	////////////////////////////////////////////////
	// 
	// QUIT BUTTON
	//
	////////////////////////////////////////////////

	auto e = std::make_unique<Entity>("QUIT BUTTON");
	Entity* qb = e.get();
	pos = { 0.f,-100.f };
	scale = { 200.f, 80.f };
	qb->addComponent<Transform2D>(pos, scale, 0.f);
	qb->addComponent<Mesh>("Box", "Button", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);


	Button* quitButton = qb->addComponent<Button>();
	quitButton->SetOnClick([this]() {QuitGame(); });
	quitButton->SetNormalColor(Color{ 200,0,0,1 });
	quitButton->SetHighlightedColor(Color{ 255,0,0,1 });
	qb->addComponent<TextMesh>(AEVec2{ pos.x + 100.f , pos.y - 250.f }, 0.6, "QUIT", Color{ 1,1,1,1 });


	enSystem->rootEntity->transform->AddChild(qb->transform);
	enSystem->entities.push_back(std::move(e));


	////////////////////////////////////////////////
	// 
	// TRANSITION SCREEN
	//
	////////////////////////////////////////////////

	auto ts = std::make_unique<Entity>("TransitionScreen");
	pos = { 0.f, 0.f };
	scale = { (float)AEGfxGetWindowWidth(), (float)AEGfxGetWindowHeight() };
	ts->addComponent<Transform2D>(pos, scale, 0.f);
	ts->addComponent<Mesh>("Box", Color(20, 20, 20, 1), 101, MeshType::BOX_B);
	ts_comp = ts->addComponent<TransitionScreen>(T_NONE);
	enSystem->rootEntity->transform->AddChild(ts->transform);
	enSystem->entities.push_back(std::move(ts));

}

void MainMenu::SwitchToGame()
{
	ts_comp->TransitionToScene(GameStateManager::BASE_CAMP);
}

void MainMenu::QuitGame()
{
	
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
