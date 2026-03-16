#pragma once
#include "MapClass.hpp"
#include "../BaseSystems/JSONSerializer/JSONSerializer.hpp"

#include <vector>

class NavigationData
{
public:
	Map viewMap{};
	Map playMap{};
	int xPos, yPos; //x, y position on playMap (set to 0 on default)

	void GenerateNavigationData(MapType type, int xLen, int yLen);
	bool SaveNavigationData(JSONSerializer serializer);
	bool LoadNavigationData(JSONSerializer& serializer);

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