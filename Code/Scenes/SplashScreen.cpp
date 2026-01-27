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
#include "../BaseSystems_WZBJ_Pak.hpp"
#include "../SceneHandler_WZBJ_Pak.hpp"

SplashScreen::SplashScreen()
{	
}

SplashScreen::~SplashScreen()
{
}

void NextScene()
{
	GameStateManager::GetInstance()->NextScene(GameStateManager::SCENES::MAIN_MENU);
}


/*!
@brief Initialize splash screen variables

Overwrites virtual GameState::Init().
This function loads splash screen image

@param void
@return void
*//*______________________________________________________________*/
void SplashScreen::Load()
{
	meshSystem = MeshGen::getInstance();
	meshSystem->CreateTexture("../../Assets/Images/Button.png", "ButtonDefault");

	enSystem = EntityManager::getInstance();
	auto r = std::make_unique<Entity>("ROOT");
	enSystem->rootEntity = r.get();
	AEVec2 pos = { 0.f,0.f };
	AEVec2 scale = { 1.f, 1.f };
	enSystem->rootEntity->addComponent<Transform2D>(pos, scale, 0.f);
	enSystem->entities.push_back(std::move(r));

	auto e = std::make_unique<Entity>("BUTTON1");
	Entity* en = e.get();
	pos = { 0.f,0.f };
	scale = { 150.f, 40.f };
	en->addComponent<Transform2D>(pos, scale, 0.f);
	en->addComponent<Mesh>("Box", "ButtonDefault", Color(255, 255, 255, 1), 100, MeshType::BOX_T);
	Button* b = en->addComponent<Button>();
	b->SetHighlightedColor(Color(30, 255, 30, 255));
	b->SetOnClick(&NextScene);
	enSystem->rootEntity->transform->AddChild(en->transform);
	enSystem->entities.push_back(std::move(e));

}


/*!
@brief Clears splash screen variables

Overwrites virtual GameState::Exit().
This function frees splash screen image used.

@param void
@return void
*//*______________________________________________________________*/
void SplashScreen::Unload()
{
	for (auto& e : enSystem->entities) {
		e->destroy();
	}
	enSystem->entities.clear();
}
