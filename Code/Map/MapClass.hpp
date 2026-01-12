#pragma once
#include "MapNodeClass.hpp"
#include "MapTypeClass.hpp"

#include <vector>

class Map
{
public:
	std::vector<std::vector <MapNode>> mapNodes;
	MapType mapType;

	//NOTE: xLen and yLen are unique grid value, NOT PIXEL POSITION!
	void GenerateMap(MapType type, int xLen, int yLen);
	void DebugPrint(MapNode node);
	void Debugprint(MapNode node, bool showCleared);

	Map();
	~Map();

	Map& operator=(const Map & other)
	{
		if (this != &other)
		{
			mapNodes = other.mapNodes;
			mapType = other.mapType;
		}
		return *this;
	}
};