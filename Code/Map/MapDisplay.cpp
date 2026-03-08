#pragma once

#include "MapDisplay.hpp"

//written by day, all map code to ask him what is going on

void MapDisplay::awake()
{
	enSystem = &EntityManager::getInstance();
	int count = 0;

	for (int x = 0; x < map.playMap.mapNodes[0].size(); x++) { for (int y = 0; x < map.playMap.mapNodes.size(); y++) {
		mapNodesReal.push_back(enSystem->FindByNameGLOBAL("MapNode_" + std::to_string(x) + "_" + std::to_string(y)));
		mapNodesFog.push_back(enSystem->FindByNameGLOBAL("MapFog_" + std::to_string(x) + "_" + std::to_string(y)));
		switch (map.playMap.mapNodes[y][x].type)
		{
			case NodeType::EnemyEncounter:
				mapNodesReal[count]->addComponent<Mesh>("Box", textureDir[2], 50, MeshType::BOX_T);
				break;
			case NodeType::RandomEvent:	//both events have same sprite
			case NodeType::FixedEvent:
				mapNodesReal[count]->addComponent<Mesh>("Box", textureDir[3], 50, MeshType::BOX_T);
				break;
			case NodeType::Entry:
				mapNodesReal[count]->addComponent<Mesh>("Box", textureDir[4], 50, MeshType::BOX_T);
				break;
			case NodeType::Exit:
				mapNodesReal[count]->addComponent<Mesh>("Box", textureDir[5], 50, MeshType::BOX_T);
				break;
			default:
				mapNodesReal[count]->addComponent<Mesh>("Box", textureDir[1], 50, MeshType::BOX_T);
		}
		mapNodesFog[count]->addComponent<Mesh>("Box", textureDir[0], 50, MeshType::BOX_T);
		mapNodesReal[count]->isActive = false;
		if (map.playMap.mapNodes[y][x].type == NodeType::VisionClear)
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
		for (int x = 0; x < map.playMap.mapNodes[0].size(); x++) { for (int y = 0; x < map.playMap.mapNodes.size(); y++) {
			if (map.viewMap.mapNodes[y][x].type != NodeType::VisionFog)
			{
				mapNodesReal[count]->isActive = true;
				mapNodesFog[count]->isActive = false;
			}
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