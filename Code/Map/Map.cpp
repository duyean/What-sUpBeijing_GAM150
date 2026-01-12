#pragma once
#include "MapClass.hpp"

void Map::GenerateMap(MapType type, int xLen, int yLen)
{

}

void Map::DebugPrint(MapNode node)
{

}

void Map::Debugprint(MapNode node, bool showCleared)
{

}

Map::Map()
{
	GenerateMap(MapType::Debug, 5, 5);
}

Map::~Map()
{
}