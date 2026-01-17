#pragma once
#include <random> //used for random generation
#include <iostream> //used to debug print the map to console

#include "../Maps_WZBJ_Pak.hpp"
//All Map Related code by Dan (Day). Ask if anything is broken.

Map Map::GenerateMap(MapType type, int xLen, int yLen)
{
	Map outMap;
	outMap.mapType = type;
	printf("Map Type Set\n");

	//set map height
	outMap.mapNodes.resize(yLen);
	for (int y = 0; y < yLen; y++)
	{
		//set map width (per width row in nested list)
		outMap.mapNodes[y].resize(xLen);
		for (int x = 0; x < xLen; x++)
		{
			MapNode newNode;
			// Block out all the Grid Walls first.
			newNode.n = newNode.s = newNode.w = newNode.e = 1;
			newNode.type = NodeType::Debug; // Default type before further generation.
			outMap.mapNodes[y][x] = newNode;
		}
	}
	//Create base framework: DONE!
	printf("Base Framework Made\n");
	
	//random seeding
	std::random_device seedling; //random generation seed
	std::mt19937 gen(seedling()); //Mersenne Twister (idk wtf this is bro i just googled rng for c++)

	//set ranges for random generation
	int mapHeight = yLen - 1, mapWidth = xLen - 1;

	std::uniform_int_distribution<> randHeight(1, mapHeight);
	std::uniform_int_distribution<> randWidth(1, mapWidth);
	std::uniform_int_distribution<> randDirction(1, 4);
	
	//select a random point on the map
	int currentX = randWidth(gen), currentY = randHeight(gen);
	outMap.mapNodes[currentY][currentX].type = NodeType::Empty; //set starting point to empty node

	printf("Random Seeding Start\n");
	//map generation pathbuilding maze
	bool noDebugTiles = false;
	while (!noDebugTiles)
	{
		//move point until no longer hitting debug panels
		bool stuck = false;
		while (!stuck)
		{
			int move = randDirction(gen); //generate random direction
			switch (move) 
			{
				case 1: //north
					if (currentY - 1 >= 0)
						if (NodeType::Debug == outMap.mapNodes[currentY - 1][currentX].type)
						{
							outMap.mapNodes[currentY][currentX].n = false;
							outMap.mapNodes[currentY - 1][currentX].s = false;
							outMap.mapNodes[currentY - 1][currentX].type = NodeType::Empty;
							currentY--;
							break;
						}
				case 2: //south
					if (currentY + 1 <= mapHeight)
						if (NodeType::Debug == outMap.mapNodes[currentY + 1][currentX].type)
						{
							outMap.mapNodes[currentY][currentX].s = false;
							outMap.mapNodes[currentY + 1][currentX].n = false;
							outMap.mapNodes[currentY + 1][currentX].type = NodeType::Empty;
							currentY++;
							break;
						}
				case 3: //east
					if (currentX + 1 <= mapWidth)
						if (NodeType::Debug == outMap.mapNodes[currentY][currentX + 1].type)
						{
							outMap.mapNodes[currentY][currentX].e = false;
							outMap.mapNodes[currentY][currentX + 1].w = false;
							outMap.mapNodes[currentY][currentX + 1].type = NodeType::Empty;
							currentX++;
							break;
						}
				case 4: //west
					if (currentX - 1 >= 0)
						if (NodeType::Debug == outMap.mapNodes[currentY][currentX - 1].type)
						{
							outMap.mapNodes[currentY][currentX].w = false;
							outMap.mapNodes[currentY][currentX - 1].e = false;
							outMap.mapNodes[currentY][currentX - 1].type = NodeType::Empty;
							currentX--;
							break;
						}
				default: //all nodes surrounding are already generated
					stuck = true;
			}
		}
		//select generated tile and try again
		while (true)
		{
			currentX = randWidth(gen), currentY = randHeight(gen);
			if (outMap.mapNodes[currentY][currentX].type == NodeType::Empty) break;
		}

		//check for full maze completion
		noDebugTiles = true;
		int counter = 0;
		for (int y = 0; y < yLen; y++){ for (int x = 0; x < xLen; x++){
			if (outMap.mapNodes[y][x].type == NodeType::Debug) { noDebugTiles = false;}
			counter++;
		}	}
		printf("Debug Tiles Remaining: %d\n", counter);
	}	//repeat until all debug panels are cleared.
	printf("Random Seeding End\n");
	
	return outMap;
}

void Map::DebugPrint(Map map)
{
	int height = map.mapNodes.size() * 3, length = map.mapNodes[0].size() * 3;
	for (int y = 0; y < height; y++) {for (int x = 0; x < length; x++) {
		int yPos = y % 3, xPos = x % 3;
		char out = '#'; //standard character for wall
		if (yPos == 1) //height check
		{
			switch (xPos)
			{
				case 0: //west
					if (map.mapNodes[y / 3][x / 3].w == false) out = ' ';
					break;
				case 2: //east
					if (map.mapNodes[y / 3][x / 3].e == false) out = ' ';
					break;
				default:
					out = ' ';
			}
		}
		else if (xPos == 1)
		{
			switch (yPos)
			{
				case 0: //north
					if (map.mapNodes[y / 3][x / 3].n == false) out = ' ';
					break;
				case 2: //south
					if (map.mapNodes[y / 3][x / 3].s == false) out = ' ';
					break;
				default:
					out = ' ';
			}
		}
		printf("%c", out);
		}
	printf("\n");
	}
	printf("end of map debug printing.\n");
}

Map::Map()
{
	//
}

Map::~Map()
{
}