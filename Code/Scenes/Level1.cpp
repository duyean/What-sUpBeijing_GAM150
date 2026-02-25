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
#include "Level1.hpp"

Level1::Level1()
{	
}

Level1::~Level1()
{
}


/*!
@brief Initialize splash screen variables

Overwrites virtual GameState::Init().
This function loads splash screen image

@param void
@return void
*//*______________________________________________________________*/
void Level1::Load()
{
	meshSystem = &MeshGen::getInstance();

	//map data info
	map.GenerateNavigationData(MapType::OuterPalace, 15, 15);
	//map data get current location data
	GetCurrentNodeInfo(map);
	//map data info end
	float collidersize = 100.f;

	enSystem = &EntityManager::getInstance();
	auto r = std::make_unique<Entity>("ROOT");
	enSystem->rootEntity = r.get();
	AEVec2 pos = { 0.f,0.f };
	AEVec2 scale = { 1.f, 1.f };
	enSystem->rootEntity->addComponent<Transform2D>(pos, scale, 0.f);
	enSystem->entities.push_back(std::move(r));

	auto ts = std::make_unique<Entity>("TransitionScreen");
	pos = { 0.f, 0.f };
	scale = { (float)AEGfxGetWindowWidth(), (float)AEGfxGetWindowHeight() };
	ts->addComponent<Transform2D>(pos, scale, 0.f);
	ts->addComponent<Mesh>("Box", Color(20, 20, 20, 1), 101, MeshType::BOX_B);
	ts->addComponent<TransitionScreen>(T_State::T_OUT);
	enSystem->rootEntity->transform->AddChild(ts->transform);
	enSystem->entities.push_back(std::move(ts));

	auto n_path = std::make_unique<Entity>("N_Path");
	scale = { (float)AEGfxGetWindowWidth(), collidersize };
	pos = { 0.f, (float)AEGfxGetWindowHeight() / 2 - scale.y/2};
	n_path->addComponent<Transform2D>(pos, scale, 0.f);
	n_path->addComponent<Mesh>("Box", Color(0, 0, 255, 0.5), 100, MeshType::BOX_B);
	n_path->addComponent<BoxCollider2D>(scale.x/2, scale.y/2);
	n_path->addComponent<SceneEdge>();
	enSystem->rootEntity->transform->AddChild(n_path->transform);
	enSystem->entities.push_back(std::move(n_path));

	auto e_path = std::make_unique<Entity>("E_Path");	
	scale = { collidersize, (float)AEGfxGetWindowHeight() };
	pos = { (float)AEGfxGetWindowWidth()/2 - scale.x/2, 0.f };
	e_path->addComponent<Transform2D>(pos, scale, 0.f);
	e_path->addComponent<Mesh>("Box", Color(0, 0, 255, 0.5), 100, MeshType::BOX_B);
	e_path->addComponent<BoxCollider2D>(scale.x / 2, scale.y / 2);
	e_path->addComponent<SceneEdge>();
	enSystem->rootEntity->transform->AddChild(e_path->transform);
	enSystem->entities.push_back(std::move(e_path));

	auto s_path = std::make_unique<Entity>("S_Path");
	scale = { (float)AEGfxGetWindowWidth(), collidersize };
	pos = { 0.f, scale.y/2 - (float)AEGfxGetWindowHeight()/2};
	s_path->addComponent<Transform2D>(pos, scale, 0.f);
	s_path->addComponent<Mesh>("Box", Color(0, 0, 255, 0.5), 100, MeshType::BOX_B);
	s_path->addComponent<BoxCollider2D>(scale.x / 2, scale.y / 2);
	s_path->addComponent<SceneEdge>();
	enSystem->rootEntity->transform->AddChild(s_path->transform);
	enSystem->entities.push_back(std::move(s_path));

	auto w_path = std::make_unique<Entity>("W_Path");
	scale = { collidersize, (float)AEGfxGetWindowHeight() };
	pos = { scale.x/2 - (float)AEGfxGetWindowWidth() / 2, 0.f };
	w_path->addComponent<Transform2D>(pos, scale, 0.f);
	w_path->addComponent<Mesh>("Box", Color(0, 0, 255, 0.5), 100, MeshType::BOX_B);
	w_path->addComponent<BoxCollider2D>(scale.x / 2, scale.y / 2);
	w_path->addComponent<SceneEdge>();
	enSystem->rootEntity->transform->AddChild(w_path->transform);
	enSystem->entities.push_back(std::move(w_path));

	auto e = std::make_unique<Entity>("Player");
	pos = { 0.f, 0.f };
	scale = { 50.f, 100.f };
	e->addComponent<Transform2D>(pos, scale, 0.f);
	e->addComponent<Player>();
	e->addComponent<Mesh>("Box", Color(0, 255, 0, 1), 100, MeshType::BOX_B);
	e->addComponent<BoxCollider2D>(scale.x/2, scale.y/2);
	enSystem->rootEntity->transform->AddChild(e->transform);
	enSystem->entities.push_back(std::move(e));

	auto SE_Manager = std::make_unique<Entity>("SceneEdgeManager");
	SE_Manager->addComponent<EdgeManager>(map);
	enSystem->entities.push_back(std::move(SE_Manager));
}


/*!
@brief Clears splash screen variables

Overwrites virtual GameState::Exit().
This function frees splash screen image used.

@param void
@return void
*//*______________________________________________________________*/
void Level1::Unload()
{
	EntityManager::getInstance().needsCleanup = true;
	for (auto& e : enSystem->entities) {
		e->toDestroy = true;
	}
}
