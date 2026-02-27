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
#include "SplashScreen.hpp"

SplashScreen::SplashScreen()
{	
}

SplashScreen::~SplashScreen()
{
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
	meshSystem = &MeshGen::getInstance();
	meshSystem->CreateTexture("../../Assets/Images/DigiPen_Singapore_WEB_RED.png", "SplashLogo");

	enSystem = &EntityManager::getInstance();
	auto r = std::make_unique<Entity>("ROOT");
	enSystem->rootEntity = r.get();
	AEVec2 pos = { 0.f,0.f };
	AEVec2 scale = { 1.f, 1.f };
	enSystem->rootEntity->addComponent<Transform2D>(pos, scale, 0.f);
	enSystem->entities.push_back(std::move(r));

	auto e = std::make_unique<Entity>("SPLASHSLOGO");
	Entity* en = e.get();
	pos = { 0.f,0.f };
	scale = { 1525.f, 445.f };
	en->addComponent<Transform2D>(pos, scale, 0.f);
	en->addComponent<Mesh>("Box", "SplashLogo", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);
	en->addComponent<SplashLogo>();
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
	EntityManager::getInstance().needsCleanup = true;
	for (auto& e : enSystem->entities) {
		e->toDestroy = true;
	}
}
