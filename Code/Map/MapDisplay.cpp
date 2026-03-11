#pragma once

#include "MapDisplay.hpp"

//written by day, all map code to ask him what is going on

void MapDisplay::awake()
{
	enSystem = &EntityManager::getInstance();
	meSystem = &MeshGen::getInstance();
	int count = 0;
	int depth = 2000;
	mapNodesReal.clear();
	mapNodesFog.clear();

	for (int textureIndex = 0; textureIndex < TEXTURE_COUNT; textureIndex++)
	{
		meSystem->CreateTexture(textureDir[textureIndex].c_str(), textureName[textureIndex].c_str());
	}

	for (int x = 0; x < map.playMap.mapNodes[0].size(); x++) { for (int y = 0; y < map.playMap.mapNodes.size(); y++) {
		mapNodesReal.push_back(enSystem->FindByNameGLOBAL("MapNode_" + std::to_string(x) + "_" + std::to_string(y)));
		mapNodesFog.push_back(enSystem->FindByNameGLOBAL("MapFog_" + std::to_string(x) + "_" + std::to_string(y)));
		switch (map.playMap.mapNodes[y][x].type)
		{
			case NodeType::EnemyEncounter:
				mapNodesReal[count]->addComponent<Mesh>("Box", textureName[2].c_str(), Color(255, 255, 255, 1.0f), depth, MeshType::BOX_T);
				break;
			case NodeType::RandomEvent:	//both events have same sprite
			case NodeType::FixedEvent:
				mapNodesReal[count]->addComponent<Mesh>("Box", textureName[3].c_str(), Color(255, 255, 255, 1.0f), depth, MeshType::BOX_T);
				break;
			case NodeType::Entry:
				mapNodesReal[count]->addComponent<Mesh>("Box", textureName[4].c_str(), Color(255, 255, 255, 1.0f), depth, MeshType::BOX_T);
				break;
			case NodeType::Exit:
				mapNodesReal[count]->addComponent<Mesh>("Box", textureName[5].c_str(), Color(255, 255, 255, 1.0f), depth, MeshType::BOX_T);
				break;
			default:
				mapNodesReal[count]->addComponent<Mesh>("Box", textureName[1].c_str(), Color(255, 255, 255, 1.0f), depth, MeshType::BOX_T);
		}
		mapNodesFog[count]->addComponent<Mesh>("Box", textureName[0].c_str(), Color(255, 255, 255, 1.0f), depth, MeshType::BOX_T);
		mapNodesReal[count]->isActive = false;
		if (map.viewMap.mapNodes[y][x].type == NodeType::VisionClear)
		{
			mapNodesReal[count]->isActive = true;
			mapNodesFog[count]->isActive = false;
		}
		count++;
	}	}
}

void MapDisplay::init()
{
	x = map.xPos;
	y = map.yPos;
}

void MapDisplay::update()
{
	if (x != map.xPos || y != map.yPos)	//check if map updates
	{
		int count = 0;
		for (int j = 0; j < map.playMap.mapNodes[0].size(); j++) { for (int k = 0; k < map.playMap.mapNodes.size(); k++) {
			if (map.viewMap.mapNodes[k][j].type != NodeType::VisionFog)
			{
				mapNodesReal[count]->isActive = true;
				mapNodesFog[count]->isActive = false;
			}
			count++;
		}	}
		x = map.xPos;
		y = map.yPos;
	}
}

void MapDisplay::fixedUpdate()
{
}

void MapDisplay::destroy()
{
}