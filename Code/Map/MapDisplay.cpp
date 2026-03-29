#pragma once

#include "MapDisplay.hpp"

//written by day, all map code to ask him what is going on

void MapDisplay::awake()
{
	enSystem = &EntityManager::getInstance();
	meSystem = &MeshGen::getInstance();
	int count = 0;
	int depthBack	= 200;
	int depthFront	= 201;
	int depthPlayer = 202;
	mapNodesReal.clear();
	mapNodesFog.clear();
	
	mapCharIcon = enSystem->FindByNameGLOBAL("MapDisplayCharacter");

	for (int textureIndex = 0; textureIndex < TEXTURE_COUNT; textureIndex++)
	{
		meSystem->CreateTexture(textureDir[textureIndex].c_str(), textureName[textureIndex].c_str());
	}

	mapCharIcon->addComponent<Mesh>("Box", textureName[7].c_str(), Color(255, 255, 255, 1.0f), depthPlayer, MeshType::BOX_T);

	for (int xi = 0; xi < map.playMap.mapNodes[0].size(); xi++) { for (int yi = 0; yi < map.playMap.mapNodes.size(); yi++) {
		mapNodesReal.push_back(enSystem->FindByNameGLOBAL("MapNode_" + std::to_string(xi) + "_" + std::to_string(yi)));
		mapNodesFog.push_back(enSystem->FindByNameGLOBAL("MapFog_" + std::to_string(xi) + "_" + std::to_string(yi)));
		int ti = 1; //default tile = 1, texture index
		switch (map.playMap.mapNodes[yi][xi].type)
		{
			case NodeType::EnemyEncounter:
				ti = 2;
				break;
			case NodeType::RandomEvent:	
				ti = 3;
				break;
			case NodeType::FixedEvent:
				ti = 8;
				break;
			case NodeType::Entry:
				ti = 4;
				break;
			case NodeType::Exit:
				ti = 5;
				break;
			case NodeType::Shop:
				ti = 6;
		}
		mapNodesReal[count]->addComponent<Mesh>("Box", textureName[ti].c_str(), Color(255, 255, 255, 1.0f), depthFront, MeshType::BOX_T);
		//SEPERATE FRONT AND BACK
		mapNodesFog[count]->addComponent<Mesh>("Box", textureName[0].c_str(), Color(255, 255, 255, 1.0f), depthBack, MeshType::BOX_T);
		mapNodesReal[count]->isActive = false;
		if (map.viewMap.mapNodes[yi][xi].type == NodeType::VisionClear)
		{
			mapNodesReal[count]->isActive = true;
			mapNodesFog[count]->getComponent<Mesh>()->setTexture(textureName[1].c_str());
			if (xi == map.xPos && yi == map.yPos) mapCharIcon->transform->setPosition(mapNodesReal[count]->transform->getPosition());
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
		for (int xi = 0; xi < map.playMap.mapNodes[0].size(); xi++) { for (int yi = 0; yi < map.playMap.mapNodes.size(); yi++) {
			if (map.viewMap.mapNodes[yi][xi].type != NodeType::VisionFog)
			{
				mapNodesReal[count]->isActive = true;
				mapNodesFog[count]->getComponent<Mesh>()->setTexture(textureName[1].c_str());
				if (map.playMap.mapNodes[yi][xi].type == NodeType::Empty)
					mapNodesReal[count]->getComponent<Mesh>()->setTexture(textureName[1].c_str());
			}
			if (map.xPos == xi && map.yPos == yi)
			{
				mapCharIcon->transform->setPosition(mapNodesReal[count]->transform->getPosition());
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