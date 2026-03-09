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
#include "../Code/SoloBehavior/EdgeManagerBase.hpp"

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

	meshSystem->CreateTexture("../../Assets/Images/base_camp.png", "BC_BG");
	auto bg = std::make_unique<Entity>("Background");
	pos = { 0.f, 0.f };
	scale = { (float)AEGfxGetWindowWidth(), (float)AEGfxGetWindowHeight() };
	bg->addComponent<Transform2D>(pos, scale, 0.f);
	bg->addComponent<Mesh>("Box", "BC_BG", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);
	enSystem->rootEntity->transform->AddChild(bg->transform);
	enSystem->entities.push_back(std::move(bg));

	meshSystem->CreateTexture("../../Assets/Images/shop.png", "shop");
	auto Shop = std::make_unique<Entity>("Shop");
	pos = { -300.f, 100.f };
	scale = { 200.f, 200.f };
	Shop->addComponent<Transform2D>(pos, scale, 0.f);
	Shop->addComponent<Mesh>("Box", "shop", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);
	Shop->addComponent<BoxCollider2D>(scale.x / 2, scale.y / 2);
	enSystem->rootEntity->transform->AddChild(Shop->transform);
	enSystem->entities.push_back(std::move(Shop));

	meshSystem->CreateTexture("../../Assets/Images/barracks.png", "barracks");
	auto PartyManager = std::make_unique<Entity>("PartyManager");
	pos = { 300.f, 100.f };
	scale = { 200.f, 200.f };
	PartyManager->addComponent<Transform2D>(pos, scale, 0.f);
	PartyManager->addComponent<Mesh>("Box", "barracks", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);
	PartyManager->addComponent<BoxCollider2D>(scale.x / 2, scale.y / 2);
	enSystem->rootEntity->transform->AddChild(PartyManager->transform);
	enSystem->entities.push_back(std::move(PartyManager));

	meshSystem->CreateTexture("../../Assets/Images/GuanShiYinBack.png", "player_sprite");
	auto e = std::make_unique<Entity>("Player");
	pos = { 0.f, -200.f };
	scale = { 100.f, 100.f };
	e->addComponent<Transform2D>(pos, scale, 0.f);
	e->addComponent<Player>();
	e->addComponent<Mesh>("Box", "player_sprite", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);
	e->addComponent<BoxCollider2D>(scale.x/2, scale.y/2);
	enSystem->rootEntity->transform->AddChild(e->transform);
	enSystem->entities.push_back(std::move(e));

	auto ts = std::make_unique<Entity>("TransitionScreen");
	pos = { 0.f, 0.f };
	scale = { (float)AEGfxGetWindowWidth(), (float)AEGfxGetWindowHeight() };
	ts->addComponent<Transform2D>(pos, scale, 0.f);
	ts->addComponent<Mesh>("Box", Color(20, 20, 20, 1), 101, MeshType::BOX_B);
	ts->addComponent<TransitionScreen>(T_State::T_OUT);
	enSystem->rootEntity->transform->AddChild(ts->transform);
	enSystem->entities.push_back(std::move(ts));

	auto baseExit = std::make_unique<Entity>("baseExit");
	scale = { (float)AEGfxGetWindowWidth(), collidersize };
	pos = { 0.f, scale.y / 2 - (float)AEGfxGetWindowHeight() / 2 };
	baseExit->addComponent<Transform2D>(pos, scale, 0.f);
	baseExit->addComponent<Mesh>("Box", Color(255, 255, 255, 0.3), 100, MeshType::BOX_B);
	baseExit->addComponent<BoxCollider2D>(scale.x / 2, scale.y / 2);
	baseExit->addComponent<SceneEdge>();
	enSystem->rootEntity->transform->AddChild(baseExit->transform);
	enSystem->entities.push_back(std::move(baseExit));

	auto SE_Manager = std::make_unique<Entity>("SceneEdgeManager");
	SE_Manager->addComponent<EdgeManagerBase>();
	enSystem->entities.push_back(std::move(SE_Manager));
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
