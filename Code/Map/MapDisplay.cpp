#pragma once

#include "MapDisplay.hpp"

void MapDisplay::awake()
{
	enSystem = &EntityManager::getInstance();

	for (int x = 0; x < map.playMap.mapNodes[0].size(); x++) { for (int y = 0; x < map.playMap.mapNodes.size(); y++) {
		mapNodesReal.push_back(enSystem->FindByNameGLOBAL("MapNode_" + std::to_string(x) + "_" + std::to_string(y)));
	}	}
}