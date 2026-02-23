#pragma once
#include <random> //used for random generation
#include <iostream> //used to debug print the map to console
#include <fstream> //used to save and load the map to json files

//mass include files
#include "../Maps_WZBJ_Pak.hpp"
#include "../JSONSerializer_WZBJ_Pak.hpp"
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

void GetCurrentNodeInfo(NavigationData data)
{
	//used for easier parsing
	NodeType currentNodeType = data.playMap.mapNodes[data.yPos][data.xPos].type;
	//print node info to console for debug purposes
	printf("Current Node Type: %d\n", static_cast<int>(currentNodeType));
	printf("Current Node Position: %d, %d\n", data.xPos, data.yPos);
	printf("Current Node Connections: \n");
	printf("North: %d\n", !data.playMap.mapNodes[data.yPos][data.xPos].n);
	printf("South: %d\n", !data.playMap.mapNodes[data.yPos][data.xPos].s);
	printf("East: %d\n", !data.playMap.mapNodes[data.yPos][data.xPos].e);
	printf("West: %d\n", !data.playMap.mapNodes[data.yPos][data.xPos].w);
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
	viewMap = Map();
	playMap = Map();
	xPos = yPos = 0;
}

NavigationData::~NavigationData()
{

}