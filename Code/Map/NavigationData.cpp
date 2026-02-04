#pragma once
#include <random> //used for random generation
#include <iostream> //used to debug print the map to console
#include <fstream> //used to save and load the map to json files

//mass include files
#include "../Maps_WZBJ_Pak.hpp"
#include "../JSONSerializer_WZBJ_Pak.hpp"
//All Map Related code by Dan (Day). Ask if anything is broken.

NavigationData NavigationData::GenerateNavigationData(MapType type, int xLen, int yLen)
{
	NavigationData outData;
	outData.playMap = Map::GenerateMap(type, xLen, yLen);

	//copy play map size to view map
	outData.viewMap = outData.playMap; 

	//set up view map based on play map
	outData.viewMap.mapType = MapType::OverlayFog; //for debug purposes if needed
	for (int x = 0; x < xLen; x++) for (int y = 0; y < yLen; y++)
	{
		//default all view map nodes to fog
		outData.viewMap.mapNodes[y][x].type = NodeType::VisionFog; 

		//find entry node position
		if (outData.playMap.mapNodes[y][x].type == NodeType::Entry)
		{
			outData.xPos = x;
			outData.yPos = y;

			//reveal entry node
			outData.viewMap.mapNodes[y][x].type = NodeType::VisionClear; 

			//reveal any node movable to from entry node
			if (!outData.viewMap.mapNodes[y][x].e)	outData.viewMap.mapNodes[y][x + 1].type = NodeType::VisionClear;
			if (!outData.viewMap.mapNodes[y][x].w)	outData.viewMap.mapNodes[y][x - 1].type = NodeType::VisionClear;
			if (!outData.viewMap.mapNodes[y][x].n)	outData.viewMap.mapNodes[y - 1][x].type = NodeType::VisionClear;
			if (!outData.viewMap.mapNodes[y][x].s)	outData.viewMap.mapNodes[y + 1][x].type = NodeType::VisionClear;
		}
	}

	return outData;
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
			//write function for trigger enemy encounter here 
			
			//StartBattleEncounter(data.playMap.mapType); 
			//mapType data is used to decide what kind of enemies spawn
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

			//ReturnToBase();
			break;

		case NodeType::Exit:
			//write function for triggering boss battle here

			//StartBossBattle(data.playMap.mapType);
			//mapType data is used to decide what kind of boss spawns
			break;
	}

}

bool NavigationData::SaveNavigationData(NavigationData data, JSONSerializer serializer, std::string fileName)
{
	//to be filled in by mr JSON
	return 0;
}

bool NavigationData::LoadNavigationData(NavigationData& data, JSONSerializer& serializer, std::string fileName)
{
	//to be filled in by mr JSON
	return 0;
}

NavigationData::NavigationData()
{
	NavigationData::playMap = Map::GenerateMap(MapType::Debug, 3, 3);
	viewMap = playMap;
	xPos = 0;
	yPos = 0;
}

NavigationData::~NavigationData()
{

}