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
#include "../Code/SoloBehavior/PauseMenu.hpp"
#include "../Audio_WZBJ_Pak.hpp"
#include "../BaseSystems/Engine/Bounce.hpp"
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
	std::cout << "CURRENT MAP: " << RunManager::Instance().GetMapType() << std::endl;

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

	float	NODE_SIZE			=	36.f;
	float	minimapOffX			=	478.f;
	float	minimapOffY			=	276.f;
	int		depthWall			=	202;
	float	thickWall			=	3.f;

	//map entities
	for (int x = map.playMap.mapNodes[0].size() - 1; x >= 0 ; x--) { for (int y = map.playMap.mapNodes.size() - 1; y >= 0; y--) {
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
	switch (RunManager::Instance().GetMapType())
	{
	case CityStreets:
		bg->addComponent<Mesh>("Box", "OP_BG", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);
		break;
	case OuterPalace:
		bg->addComponent<Mesh>("Box", "OP_BG", Color(200, 200, 255, 1.f), 100, MeshType::BOX_T);
		break;
	case InnerPalace:
		bg->addComponent<Mesh>("Box", "OP_BG", Color(255, 200, 200, 1.f), 100, MeshType::BOX_T);
		break;
	}
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
	e->addComponent<BoxCollider2D>(scale.x / 1.5, scale.y / 1.5);
	e->addComponent<Player>();
	//e->addComponent<Bounce>(0.f, 2.f, 0.1f, 0.07f);
	enSystem->rootEntity->transform->AddChild(e->transform);
	enSystem->entities.push_back(std::move(e));


	meshSystem->CreateTexture("Assets/UI/PathArrow.png", "path_arrow_sprite");

	auto n_path = std::make_unique<Entity>("N_Path");
	scale = { (float)AEGfxGetWindowWidth(), collidersize };
	pos = { 0.f, (float)AEGfxGetWindowHeight() / 2 - scale.y/2};
	n_path->addComponent<Transform2D>(pos, scale, 0.f);
	//n_path->addComponent<Mesh>("Box", Color(255, 255, 255, 0.3), 100, MeshType::BOX_B);
	n_path->addComponent<BoxCollider2D>(scale.x/ 1.5, scale.y/ 1.5);
	n_path->addComponent<SceneEdge>();
	enSystem->rootEntity->transform->AddChild(n_path->transform);
	
	auto n_path_sprite = std::make_unique<Entity>("N_Path_sprite");
	scale = { 0.05f, 0.5f }; pos = { 0.f, 0.f };
	n_path_sprite->addComponent<Transform2D>(pos, scale, 0.f);
	n_path_sprite->addComponent<Mesh>("Box", "path_arrow_sprite", Color(50, 50, 50, 1.f), 102, MeshType::BOX_T);
	n_path->transform->AddChild(n_path_sprite->transform);

	enSystem->entities.push_back(std::move(n_path));
	enSystem->entities.push_back(std::move(n_path_sprite));
	

	auto e_path = std::make_unique<Entity>("E_Path");	
	scale = { collidersize, (float)AEGfxGetWindowHeight() };
	pos = { (float)AEGfxGetWindowWidth()/2 - scale.x/2, 0.f };
	e_path->addComponent<Transform2D>(pos, scale, 0.f);
	//e_path->addComponent<Mesh>("Box", Color(255, 255, 255, 0.3), 100, MeshType::BOX_B);
	e_path->addComponent<BoxCollider2D>(scale.x / 1.5, scale.y / 1.5);
	e_path->addComponent<SceneEdge>();
	enSystem->rootEntity->transform->AddChild(e_path->transform);

	auto e_path_sprite = std::make_unique<Entity>("E_Path_sprite");
	scale = {0.6f, 0.05f }; pos = { 0.f, 0.f };
	e_path_sprite->addComponent<Transform2D>(pos, scale, -90.f);
	e_path_sprite->addComponent<Mesh>("Box", "path_arrow_sprite", Color(50, 50, 50, 1.f), 102, MeshType::BOX_T);
	e_path->transform->AddChild(e_path_sprite->transform);

	enSystem->entities.push_back(std::move(e_path));
	enSystem->entities.push_back(std::move(e_path_sprite));


	auto s_path = std::make_unique<Entity>("S_Path");
	scale = { (float)AEGfxGetWindowWidth(), collidersize };
	pos = { 0.f, scale.y/2 - (float)AEGfxGetWindowHeight()/2};
	s_path->addComponent<Transform2D>(pos, scale, 0.f);
	s_path->addComponent<BoxCollider2D>(scale.x / 1.5, scale.y / 1.5);
	s_path->addComponent<SceneEdge>();
	enSystem->rootEntity->transform->AddChild(s_path->transform);

	auto s_path_sprite = std::make_unique<Entity>("S_Path_sprite");
	scale = { 0.05f, 0.5f }; pos = { 0.f, 0.f };
	s_path_sprite->addComponent<Transform2D>(pos, scale, 180.f);
	s_path_sprite->addComponent<Mesh>("Box", "path_arrow_sprite", Color(50, 50, 50, 1.f), 102, MeshType::BOX_T);
	s_path->transform->AddChild(s_path_sprite->transform);

	enSystem->entities.push_back(std::move(s_path));
	enSystem->entities.push_back(std::move(s_path_sprite));


	auto w_path = std::make_unique<Entity>("W_Path");
	scale = { collidersize, (float)AEGfxGetWindowHeight() };
	pos = { scale.x/2 - (float)AEGfxGetWindowWidth() / 2, 0.f };
	w_path->addComponent<Transform2D>(pos, scale, 0.f);
	w_path->addComponent<BoxCollider2D>(scale.x / 1.5, scale.y / 1.5);
	w_path->addComponent<SceneEdge>();
	enSystem->rootEntity->transform->AddChild(w_path->transform);

	auto w_path_sprite = std::make_unique<Entity>("W_Path_sprite");
	scale = { 0.6f, 0.05f }; pos = { 0.f, 0.f };
	w_path_sprite->addComponent<Transform2D>(pos, scale, 90.f);
	w_path_sprite->addComponent<Mesh>("Box", "path_arrow_sprite", Color(50, 50, 50, 1.f), 102, MeshType::BOX_T);
	w_path->transform->AddChild(w_path_sprite->transform);

	enSystem->entities.push_back(std::move(w_path));
	enSystem->entities.push_back(std::move(w_path_sprite));

	auto notif = std::make_unique<Entity>("Notification");
	pos = { 0,  0 + ((float)AEGfxGetWindowHeight()/2.f - 200.f)};
	scale = {1.f, 1.f };
	notif->addComponent<Transform2D>(pos, scale, 0.f);
	notif->addComponent<TextBox>("PRESS SPACE TO GO BACK TO BASE!", 1.f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);
	enSystem->rootEntity->transform->AddChild(notif->transform);
	enSystem->entities.push_back(std::move(notif));

	auto ps = std::make_unique<Entity>("PauseScreen");
	pos = { 0.f, 0.f };
	scale = { (float)AEGfxGetWindowWidth(), (float)AEGfxGetWindowHeight() };
	ps->addComponent<Transform2D>(pos, scale, 0.f);
	ps->addComponent<PauseMenu>();
	enSystem->rootEntity->transform->AddChild(ps->transform);
	enSystem->entities.push_back(std::move(ps));

	auto SE_Manager = std::make_unique<Entity>("SceneEdgeManager");
	SE_Manager->addComponent<Transform2D>();
	SE_Manager->addComponent<EdgeManager>(map);
	enSystem->entities.push_back(std::move(SE_Manager));

	RunManager::Instance().game_paused = false;

	MapType mapType = RunManager::Instance().GetMapType();
	switch (mapType)
	{
	case CityStreets:
		AudioManager::GetInstance()->StopAllTracks(true, AudioManager::AUDIO_LEVEL1_BGM);
		AudioManager::GetInstance()->PlayTrack(AudioManager::AUDIO_LEVEL1_BGM, true);
		break;
	case OuterPalace:
		AudioManager::GetInstance()->StopAllTracks(true, AudioManager::AUDIO_LEVEL2_BGM);
		AudioManager::GetInstance()->PlayTrack(AudioManager::AUDIO_LEVEL2_BGM, true);
		break;
	case InnerPalace:
		AudioManager::GetInstance()->StopAllTracks(true, AudioManager::AUDIO_LEVEL3_BGM);
		AudioManager::GetInstance()->PlayTrack(AudioManager::AUDIO_LEVEL3_BGM, true);
		break;
	}
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
	map.~NavigationData();
}
