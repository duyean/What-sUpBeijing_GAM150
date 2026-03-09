#pragma once
#include <random> //used for random generation
#include <iostream> //used to debug print the map to console
#include <fstream> //used to save and load the map to json files

//mass include files
#include "../Maps_WZBJ_Pak.hpp"
#include "../JSONSerializer_WZBJ_Pak.hpp"
#include "../Scenes/SceneHandler/GameStateManager.hpp"
#include "../Code/SoloBehavior/RunManager.hpp"
//All Map Related code by Dan (Day). Ask if anything is broken.

void NavigationData::GenerateNavigationData(MapType type, int xLen, int yLen)
{
	this->playMap.GenerateMap(type, xLen, yLen);

	//copy play map size to view map
	this->viewMap = this->playMap; 

	//set up view map based on play map
	this->viewMap.mapType = MapType::OverlayFog; //for debug purposes if needed
	for (int x = 0; x < xLen; x++) for (int y = 0; y < yLen; y++)
	{
		//default all view map nodes to fog
		this->viewMap.mapNodes[y][x].type = NodeType::VisionFog; 

		//find entry node position
		if (this->playMap.mapNodes[y][x].type == NodeType::Entry)
		{
			this->xPos = x;
			this->yPos = y;

			//reveal entry node
			this->viewMap.mapNodes[y][x].type = NodeType::VisionClear; 

			//reveal any node movable to from entry node
			if (!this->viewMap.mapNodes[y][x].e)	this->viewMap.mapNodes[y][x + 1].type = NodeType::VisionClear;
			if (!this->viewMap.mapNodes[y][x].w)	this->viewMap.mapNodes[y][x - 1].type = NodeType::VisionClear;
			if (!this->viewMap.mapNodes[y][x].n)	this->viewMap.mapNodes[y - 1][x].type = NodeType::VisionClear;
			if (!this->viewMap.mapNodes[y][x].s)	this->viewMap.mapNodes[y + 1][x].type = NodeType::VisionClear;
		}
	}

	std::cout << "Play Map:\n";
	Map::DebugPrint(playMap);
	std::cout << "View Map:\n";
	Map::DebugPrint(viewMap);

	JSONSerializer serializer{};
	SaveNavigationData(serializer);
}

void TravelNode(NavigationData& data, int newX, int newY)
{
	//set current node to clear vision
	data.viewMap.mapNodes[newY][newX].type = NodeType::VisionClear;

	//reveal any node movable to from current node
	if (!data.viewMap.mapNodes[newY][newX].e)	data.viewMap.mapNodes[newY][newX + 1].type = NodeType::VisionClear;
	if (!data.viewMap.mapNodes[newY][newX].w)	data.viewMap.mapNodes[newY][newX - 1].type = NodeType::VisionClear;
	if (!data.viewMap.mapNodes[newY][newX].n)	data.viewMap.mapNodes[newY - 1][newX].type = NodeType::VisionClear;
	if (!data.viewMap.mapNodes[newY][newX].s)	data.viewMap.mapNodes[newY + 1][newX].type = NodeType::VisionClear;

	//set new player position
	data.xPos = newX;
	data.yPos = newY;

	//used for easier parsing
	NodeType currentNodeType = data.playMap.mapNodes[newY][newX].type;

	//trigger node if something is present
	switch (currentNodeType)
	{
		case NodeType::Empty:
			//Nothing should happen here.
			break;

		case NodeType::EnemyEncounter:
			//RunManager::Instance().SetBattleType(BATTLE_TYPE::NORMAL);
			//GameStateManager::GetInstance()->NextScene(GameStateManager::BATTLE_SCENE);
			break;

		case NodeType::RandomEvent:
			//write function for trigger random event here
			
			//triggerRandomEvent();
			break;

		case NodeType::FixedEvent:
			//write function for trigger fixed event here
			
			//triggerFixedEvent(data.playMap.mapType);
			//mapType data is used to decide what kind of event triggers
			break;

		case NodeType::Entry:
			//write function for returning to base here
			break;

		case NodeType::Exit:
			//write function for triggering boss battle here

			//StartBossBattle(data.playMap.mapType);
			//mapType data is used to decide what kind of boss spawns


			RunManager::Instance().SetBattleType(BATTLE_TYPE::BOSS);
			GameStateManager::GetInstance()->NextScene(GameStateManager::BATTLE_SCENE);
			break;
	}

}

void GetCurrentNodeInfo(NavigationData data)
{
	//used for easier parsing
	NodeType currentNodeType = data.playMap.mapNodes[data.yPos][data.xPos].type;
	//print node info to console for debug purposes
	printf("Current Node Type: %d\n", static_cast<int>(currentNodeType));
	printf("Current Node Position: %d, %d\n", data.xPos, data.yPos);
	printf("Current Node Connections: \n");
	printf("North: %s\n", data.playMap.mapNodes[data.yPos][data.xPos].n ? "Wall" : "Path" );
	printf("South: %s\n", data.playMap.mapNodes[data.yPos][data.xPos].s ? "Wall" : "Path");
	printf("East: %s\n", data.playMap.mapNodes[data.yPos][data.xPos].e ? "Wall" : "Path");
	printf("West: %s\n", data.playMap.mapNodes[data.yPos][data.xPos].w ? "Wall" : "Path");
}

bool NavigationData::SaveNavigationData(JSONSerializer serializer)
{
	//to be filled in by mr JSON
	if (!playMap.SaveMap(serializer, "Assets/Map/PlayMap.json")) return 0;
	if (!viewMap.SaveMap(serializer, "Assets/Map/ViewMap.json")) return 0;

	std::ofstream ofs("Assets/Map/NavData.json");
	if (!ofs.is_open())
	{
		std::cout << "Cannot open Assets/Map/NavData.json" << std::endl;
		return false;
	}

	rapidjson::OStreamWrapper os(ofs);
	rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(os);

	writer.StartObject();
		writer.Key("x");
		writer.Int(xPos);
		writer.Key("y");
		writer.Int(yPos);
	writer.EndObject();
	return 1;
}

bool NavigationData::LoadNavigationData(JSONSerializer& serializer)
{
	//to be filled in by mr JSON
	if (!playMap.LoadMap(serializer, "Assets/Map/PlayMap.json")) return 0;
	if (!viewMap.LoadMap(serializer, "Assets/Map/ViewMap.json")) return 0;

	rapidjson::Document doc = serializer.ReadDocument("Assets/Map/NavData.json");
	if (doc.IsNull())
	{
		std::cout << "Unable to load the Map as Document is nullptr" << std::endl;
		return false;
	}
	xPos = doc["x"].GetInt();
	yPos = doc["y"].GetInt();

	std::cout << "Play Map:\n";
	Map::DebugPrint(playMap);
	std::cout << "View Map:\n";
	Map::DebugPrint(viewMap);
	return 1;
}

NavigationData::NavigationData()
{
	viewMap = Map();
	playMap = Map();
	xPos = yPos = 0;
}

NavigationData::~NavigationData()
{

}