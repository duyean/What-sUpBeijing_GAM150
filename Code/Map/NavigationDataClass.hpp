#pragma once
#include "MapClass.hpp"
#include "../BaseSystems/JSONSerializer/JSONSerializer.hpp"

#include <vector>

class NavigationData
{
public:
	Map viewMap;
	Map playMap;
	int xPos, yPos; //x, y position on playMap

	static NavigationData GenerateNavigationData(MapType type, int xLen, int yLen);
	static bool SaveNavigationData(NavigationData data, JSONSerializer serializer, std::string fileName);
	static bool LoadNavigationData(NavigationData& data, JSONSerializer& serializer, std::string fileName);

	NavigationData();
	~NavigationData();

	NavigationData & operator=(const NavigationData& other)
	{
		if (this != &other)
		{
			viewMap = other.viewMap;
			playMap = other.playMap;
			xPos = other.xPos;
			yPos = other.yPos;
		}
		return *this;
	}
};