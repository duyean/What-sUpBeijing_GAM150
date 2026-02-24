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
#include "BaseCamp.hpp"

BaseCamp::BaseCamp()
{	
}

BaseCamp::~BaseCamp()
{
}


/*!
@brief Initialize splash screen variables

Overwrites virtual GameState::Init().
This function loads splash screen image

@param void
@return void
*//*______________________________________________________________*/
void BaseCamp::Load()
{
	meshSystem = &MeshGen::getInstance();

	float collidersize = 100.f;

	enSystem = &EntityManager::getInstance();
	auto r = std::make_unique<Entity>("ROOT");
	enSystem->rootEntity = r.get();
	AEVec2 pos = { 0.f,0.f };
	AEVec2 scale = { 1.f, 1.f };
	enSystem->rootEntity->addComponent<Transform2D>(pos, scale, 0.f);
	enSystem->entities.push_back(std::move(r));


	auto Shop = std::make_unique<Entity>("Shop");
	pos = { -300.f, 100.f };
	scale = { 200.f, 200.f };
	Shop->addComponent<Transform2D>(pos, scale, 0.f);
	Shop->addComponent<Mesh>("Box", Color(100, 100, 100, 1), 100, MeshType::BOX_B);
	Shop->addComponent<BoxCollider2D>(scale.x / 2, scale.y / 2);
	enSystem->rootEntity->transform->AddChild(Shop->transform);
	enSystem->entities.push_back(std::move(Shop));

	auto PartyManager = std::make_unique<Entity>("PartyManager");
	pos = { 300.f, 100.f };
	scale = { 200.f, 200.f };
	PartyManager->addComponent<Transform2D>(pos, scale, 0.f);
	PartyManager->addComponent<Mesh>("Box", Color(100, 100, 100, 1), 100, MeshType::BOX_B);
	PartyManager->addComponent<BoxCollider2D>(scale.x / 2, scale.y / 2);
	enSystem->rootEntity->transform->AddChild(PartyManager->transform);
	enSystem->entities.push_back(std::move(PartyManager));

	auto e = std::make_unique<Entity>("Player");
	pos = { 0.f, -200.f };
	scale = { 50.f, 100.f };
	e->addComponent<Transform2D>(pos, scale, 0.f);
	e->addComponent<Player>();
	e->addComponent<Mesh>("Box", Color(0, 255, 0, 1), 100, MeshType::BOX_B);
	e->addComponent<BoxCollider2D>(scale.x/2, scale.y/2);
	enSystem->rootEntity->transform->AddChild(e->transform);
	enSystem->entities.push_back(std::move(e));

	auto ts = std::make_unique<Entity>("TransitionScreen");
	pos = { 0.f, 0.f };
	scale = { (float)AEGfxGetWindowWidth(), (float)AEGfxGetWindowHeight() };
	ts->addComponent<Transform2D>(pos, scale, 0.f);
	ts->addComponent<Mesh>("Box", Color(20, 20, 20, 1), 100, MeshType::BOX_B);
	ts->addComponent<TransitionScreen>(T_State::T_OUT);
	enSystem->rootEntity->transform->AddChild(ts->transform);
	enSystem->entities.push_back(std::move(ts));

	auto baseExit = std::make_unique<Entity>("baseExit");
	scale = { (float)AEGfxGetWindowWidth(), collidersize };
	pos = { 0.f, scale.y / 2 - (float)AEGfxGetWindowHeight() / 2 };
	baseExit->addComponent<Transform2D>(pos, scale, 0.f);
	baseExit->addComponent<Mesh>("Box", Color(0, 0, 255, 0.5), 100, MeshType::BOX_B);
	baseExit->addComponent<BoxCollider2D>(scale.x / 2, scale.y / 2);
	baseExit->addComponent<SceneEdge>(EdgeType::BASE);
	enSystem->rootEntity->transform->AddChild(baseExit->transform);
	enSystem->entities.push_back(std::move(baseExit));
}


/*!
@brief Clears splash screen variables

Overwrites virtual GameState::Exit().
This function frees splash screen image used.

@param void
@return void
*//*______________________________________________________________*/
void BaseCamp::Unload()
{
	EntityManager::getInstance().needsCleanup = true;
	for (auto& e : enSystem->entities) {
		e->toDestroy = true;
	}
}
