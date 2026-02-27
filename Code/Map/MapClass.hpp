#pragma once
#include "MapNodeClass.hpp"
#include "MapTypeClass.hpp"
#include "../BaseSystems/JSONSerializer/JSONSerializer.hpp"

#include <vector>

class Map
{
public:
	std::vector<std::vector <MapNode>> mapNodes{};
	MapType mapType;

	//NOTE: xLen and yLen are unique grid value, NOT PIXEL POSITION!
	void GenerateMap(MapType type, int xLen, int yLen);
	static void DebugPrint(Map map);
	static bool SaveMap(Map map, JSONSerializer serializer, std::string fileName);
	static bool LoadMap(Map map, JSONSerializer& serializer, std::string fileName);

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