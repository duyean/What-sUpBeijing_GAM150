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
#include "LevelScene.hpp"
#include <fstream>
#include "../SoloBehavior/Player.hpp"
#include "../Code/SoloBehavior/TransitionScreen.hpp"
#include "../Code/SoloBehavior/EdgeManager.hpp"
#include "../Code/SoloBehavior/RunManager.hpp"

LevelScene::LevelScene()
{	
}

LevelScene::~LevelScene()
{
}


/*!
@brief Initialize splash screen variables

Overwrites virtual GameState::Init().
This function loads splash screen image

@param void
@return void
*//*______________________________________________________________*/
void LevelScene::Load()
{
	meshSystem = &MeshGen::getInstance();

	//check if the current map is the same as the prev set map
	if (RunManager::Instance().GetMapType() == RunManager::Instance().GetPrevMapType())
	{
		//if there is a map already saved, load the map
		std::ifstream ifs("Assets/Map/NavData.json");
		if (ifs.good())
		{
			std::cout << "Loading map since map already exists and level did not change!" << "\n";
			JSONSerializer serializer{};
			map.LoadNavigationData(serializer);
		}
		else
		{
			//generate a new map	
			map.GenerateNavigationData(RunManager::Instance().GetMapType(), 4, 4);
			std::cout << "Generating a new map since we just started the run!" << "\n";
		}		
	}
	else
	{
		//generate the new current map
		map.GenerateNavigationData(RunManager::Instance().GetMapType(), 4, 4);
		RunManager::Instance().SetPrevMapType(RunManager::Instance().GetMapType());

		std::cout << "Generating a new map since we change level!" << "\n";
	}
	
	std::cout << "Now on map: " << RunManager::Instance().GetMapType()<<"\n";
		
	//map data get current location data
	//GetCurrentNodeInfo(map);
	//map data info end
	float collidersize = 100.f;

	enSystem = &EntityManager::getInstance();
	auto r = std::make_unique<Entity>("ROOT");
	enSystem->rootEntity = r.get();
	AEVec2 pos = { 0.f,0.f };
	AEVec2 scale = { 1.f, 1.f };
	enSystem->rootEntity->addComponent<Transform2D>(pos, scale, 0.f);
	enSystem->entities.push_back(std::move(r));

	float NODE_SIZE = 23.f;
	float minimapOffX =  300.f;
	float minimapOffY = -150.f;
	int depthWall = 202;
	float thickWall = 2.f;

	//map entities
	for (int x = map.playMap.mapNodes[0].size() - 1; x >= 0 ; x--) { for (int y = map.playMap.mapNodes.size() - 1; y >= 0 ; y--) {
		auto mapNode = std::make_unique<Entity>("MapNode_" + std::to_string(x) + "_" + std::to_string(y));
		auto mapFog = std::make_unique<Entity>("MapFog_" + std::to_string(x) + "_" + std::to_string(y));
		pos = { minimapOffX + (float)x * NODE_SIZE, minimapOffY - (float)y * NODE_SIZE };
		scale = { NODE_SIZE, NODE_SIZE };
		mapNode->addComponent<Transform2D>(pos, scale, 0.f);
		mapFog->addComponent<Transform2D>(pos, scale, 0.f);
		enSystem->rootEntity->transform->AddChild(mapNode->transform);
		enSystem->entities.push_back(std::move(mapNode));
		enSystem->rootEntity->transform->AddChild(mapFog->transform);
		enSystem->entities.push_back(std::move(mapFog));
		//map walls
		for (int wallVal = 0; wallVal < 4; wallVal++)
		{
			switch (wallVal)
			{
				case 0:
					if (map.playMap.mapNodes[y][x].n)
					{
						auto wall = std::make_unique<Entity>("Wall_N_" + std::to_string(x) + "_" + std::to_string(y));
						pos = { minimapOffX + (float)x * NODE_SIZE, minimapOffY - (float)y * NODE_SIZE + NODE_SIZE/2 };
						scale = { NODE_SIZE, thickWall };
						wall->addComponent<Transform2D>(pos, scale, 0.f);
						wall->addComponent<Mesh>("Box", Color(0, 0, 0, 1.f), depthWall, MeshType::BOX_B);
						enSystem->rootEntity->transform->AddChild(wall->transform);
						enSystem->entities.push_back(std::move(wall));
					}
					break;
				case 1:
					if (map.playMap.mapNodes[y][x].e)
					{
						auto wall = std::make_unique<Entity>("Wall_E_" + std::to_string(x) + "_" + std::to_string(y));
						pos = { minimapOffX + (float)x * NODE_SIZE + NODE_SIZE/2, minimapOffY - (float)y * NODE_SIZE };
						scale = { thickWall, NODE_SIZE };
						wall->addComponent<Transform2D>(pos, scale, 0.f);
						wall->addComponent<Mesh>("Box", Color(0, 0, 0, 1.f), depthWall, MeshType::BOX_B);
						enSystem->rootEntity->transform->AddChild(wall->transform);
						enSystem->entities.push_back(std::move(wall));
					}
					break;
				case 2:
					if (map.playMap.mapNodes[y][x].s)
					{
						auto wall = std::make_unique<Entity>("Wall_S_" + std::to_string(x) + "_" + std::to_string(y));
						pos = { minimapOffX + (float)x * NODE_SIZE, minimapOffY - (float)y * NODE_SIZE - NODE_SIZE / 2 };
						scale = { NODE_SIZE, thickWall };
						wall->addComponent<Transform2D>(pos, scale, 0.f);
						wall->addComponent<Mesh>("Box", Color(0, 0, 0, 1.f), depthWall, MeshType::BOX_B);
						enSystem->rootEntity->transform->AddChild(wall->transform);
						enSystem->entities.push_back(std::move(wall));
					}
					break;
				case 3:
					if (map.playMap.mapNodes[y][x].w)
					{
						auto wall = std::make_unique<Entity>("Wall_W_" + std::to_string(x) + "_" + std::to_string(y));
						pos = { minimapOffX + (float)x * NODE_SIZE - NODE_SIZE / 2, minimapOffY - (float)y * NODE_SIZE };
						scale = { thickWall, NODE_SIZE };
						wall->addComponent<Transform2D>(pos, scale, 0.f);
						wall->addComponent<Mesh>("Box", Color(0, 0, 0, 1.f), depthWall, MeshType::BOX_B);
						enSystem->rootEntity->transform->AddChild(wall->transform);
						enSystem->entities.push_back(std::move(wall));
		}	}
	}	}	}

	//player character
	auto playerCharacter = std::make_unique<Entity>("MapDisplayCharacter");
	pos = { minimapOffX + (float)map.xPos * NODE_SIZE, minimapOffY - (float)map.yPos * NODE_SIZE };
	scale = { NODE_SIZE - 2, NODE_SIZE - 2};
	playerCharacter->addComponent<Transform2D>(pos, scale, 0.f);
	enSystem->rootEntity->transform->AddChild(playerCharacter->transform);
	enSystem->entities.push_back(std::move(playerCharacter));

	auto MD_Manager = std::make_unique<Entity>("MapDisplayManager");
	MD_Manager->addComponent<MapDisplay>(map);
	enSystem->entities.push_back(std::move(MD_Manager));
	meshSystem->CreateTexture("../../Assets/Images/Outer_Palace.png", "OP_BG");
	auto bg = std::make_unique<Entity>("Background");
	pos = { 0.f, 0.f };
	scale = { (float)AEGfxGetWindowWidth(), (float)AEGfxGetWindowHeight() };
	bg->addComponent<Transform2D>(pos, scale, 0.f);
	bg->addComponent<Mesh>("Box", "OP_BG", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);
	enSystem->rootEntity->transform->AddChild(bg->transform);
	enSystem->entities.push_back(std::move(bg));

	auto ts = std::make_unique<Entity>("TransitionScreen");
	pos = { 0.f, 0.f };
	scale = { (float)AEGfxGetWindowWidth(), (float)AEGfxGetWindowHeight() };
	ts->addComponent<Transform2D>(pos, scale, 0.f);
	ts->addComponent<Mesh>("Box", Color(20, 20, 20, 1), 999, MeshType::BOX_B);
	ts->addComponent<TransitionScreen>(T_State::T_OUT);
	enSystem->rootEntity->transform->AddChild(ts->transform);
	enSystem->entities.push_back(std::move(ts));

	meshSystem->CreateTexture("../../Assets/Images/GuanShiYinBack.png", "player_sprite");
	auto e = std::make_unique<Entity>("Player");
	pos = { 0.f, 0.f };
	scale = { 100.f, 100.f };
	e->addComponent<Transform2D>(pos, scale, 0.f);
	e->addComponent<Mesh>("Box", "player_sprite", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);
	e->addComponent<BoxCollider2D>(scale.x / 2, scale.y / 2);
	e->addComponent<Player>();
	enSystem->rootEntity->transform->AddChild(e->transform);
	enSystem->entities.push_back(std::move(e));

	auto n_path = std::make_unique<Entity>("N_Path");
	scale = { (float)AEGfxGetWindowWidth(), collidersize };
	pos = { 0.f, (float)AEGfxGetWindowHeight() / 2 - scale.y/2};
	n_path->addComponent<Transform2D>(pos, scale, 0.f);
	n_path->addComponent<Mesh>("Box", Color(255, 255, 255, 0.3), 100, MeshType::BOX_B);
	n_path->addComponent<BoxCollider2D>(scale.x/2, scale.y/2);
	n_path->addComponent<SceneEdge>();
	enSystem->rootEntity->transform->AddChild(n_path->transform);
	enSystem->entities.push_back(std::move(n_path));

	auto e_path = std::make_unique<Entity>("E_Path");	
	scale = { collidersize, (float)AEGfxGetWindowHeight() };
	pos = { (float)AEGfxGetWindowWidth()/2 - scale.x/2, 0.f };
	e_path->addComponent<Transform2D>(pos, scale, 0.f);
	e_path->addComponent<Mesh>("Box", Color(255, 255, 255, 0.3), 100, MeshType::BOX_B);
	e_path->addComponent<BoxCollider2D>(scale.x / 2, scale.y / 2);
	e_path->addComponent<SceneEdge>();
	enSystem->rootEntity->transform->AddChild(e_path->transform);
	enSystem->entities.push_back(std::move(e_path));

	auto s_path = std::make_unique<Entity>("S_Path");
	scale = { (float)AEGfxGetWindowWidth(), collidersize };
	pos = { 0.f, scale.y/2 - (float)AEGfxGetWindowHeight()/2};
	s_path->addComponent<Transform2D>(pos, scale, 0.f);
	s_path->addComponent<Mesh>("Box", Color(255, 255, 255, 0.3), 100, MeshType::BOX_B);
	s_path->addComponent<BoxCollider2D>(scale.x / 2, scale.y / 2);
	s_path->addComponent<SceneEdge>();
	enSystem->rootEntity->transform->AddChild(s_path->transform);
	enSystem->entities.push_back(std::move(s_path));

	auto w_path = std::make_unique<Entity>("W_Path");
	scale = { collidersize, (float)AEGfxGetWindowHeight() };
	pos = { scale.x/2 - (float)AEGfxGetWindowWidth() / 2, 0.f };
	w_path->addComponent<Transform2D>(pos, scale, 0.f);
	w_path->addComponent<Mesh>("Box", Color(255, 255, 255, 0.3), 100, MeshType::BOX_B);
	w_path->addComponent<BoxCollider2D>(scale.x / 2, scale.y / 2);
	w_path->addComponent<SceneEdge>();
	enSystem->rootEntity->transform->AddChild(w_path->transform);
	enSystem->entities.push_back(std::move(w_path));

	auto SE_Manager = std::make_unique<Entity>("SceneEdgeManager");
	SE_Manager->addComponent<Transform2D>();
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
void LevelScene::Unload()
{
	JSONSerializer serializer{};
	map.SaveNavigationData(serializer);
	EntityManager::getInstance().needsCleanup = true;
	for (auto& e : enSystem->entities) {
		e->toDestroy = true;
	}
}
