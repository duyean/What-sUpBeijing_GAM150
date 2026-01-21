#pragma once
#include <random> //used for random generation
#include <iostream> //used to debug print the map to console

//mass include files
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

	std::uniform_int_distribution<> randHeight(0, mapHeight);
	std::uniform_int_distribution<> randWidth(0, mapWidth);
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
			if (outMap.mapNodes[y][x].type == NodeType::Debug) { noDebugTiles = false; counter++; printf("Ungenerated Tile At: %d, %d\n", x, y); }
		}	}
		printf("Ungenerated Tiles Remaining: %d\n", counter);
	}	//repeat until all debug panels are cleared.
	printf("Random Seeding End\n");

	Map travelPath = outMap; //copy of map for pathfinding

	printf("Finding Random Edge Node.\n");
	//mark one random edge node as entry
	while (true)
	{
		currentX = randWidth(gen), currentY = randHeight(gen);
		if (isEndNode(outMap.mapNodes[currentY][currentX]))
		{
			outMap.mapNodes[currentY][currentX].type = NodeType::Entry;
			break;
	}	}
	printf("Entry Node Designated.\n");

	std::vector<std::vector<int>> endNodes; //x, y, distance from entry
	std::vector<std::vector<int>> traveller; //travellers
	endNodes.push_back({ currentY, currentX, 0 });
	traveller.push_back({ currentY, currentX, 0 });

	printf("Printing Map Display pre-Exploration\n");
	Map::DebugPrint(outMap);

	printf("Exploring Nodes for generation.\n");
	bool allNodesExplored = false;
	while (!allNodesExplored)
	{
		currentX = traveller[0][1], currentY = traveller[0][0];
		MapNode currentNode = travelPath.mapNodes[currentY][currentX];
		//variables for ease of use.

		bool foundNewNode = false;
		travelPath.mapNodes[currentY][currentX].type = NodeType::Debug; //mark current node as traveled
		printf("Travelling Node %d, %d.\n", currentX, currentY);

		//find new nodes to travel to. If found, add to traveller list with incremented travel count.
		if (!currentNode.n)
		{
			printf("North Node Possible Path!\n");
			if (travelPath.mapNodes[currentY - 1][currentX].type == NodeType::Empty)
			{
				foundNewNode = true;
				traveller.push_back({ currentY - 1, currentX, traveller[0][2] + 1 });
		}	}
		if (!currentNode.s)
		{	
			printf("South Node Possible Path!\n");
			if (travelPath.mapNodes[currentY + 1][currentX].type == NodeType::Empty)
			{
				foundNewNode = true;
				traveller.push_back({ currentY + 1, currentX, traveller[0][2] + 1 });
		}	}
		if (!currentNode.e)
		{	
			printf("East Node Possible Path!\n");
			if (travelPath.mapNodes[currentY][currentX + 1].type == NodeType::Empty)
			{
				foundNewNode = true;	
				traveller.push_back({ currentY, currentX + 1, traveller[0][2] + 1 });
		}	}
		if (!currentNode.w)
		{	
			printf("West Node Possible Path!\n");
			if (travelPath.mapNodes[currentY][currentX - 1].type == NodeType::Empty)
			{
				foundNewNode = true;
				traveller.push_back({ currentY, currentX - 1, traveller[0][2] + 1 });
		}	}

		
		for (int i = 0; i < traveller.size(); i++)
		{
			//debug print all travellers currents in action
			printf("Traveller %d: %d, %d (Distance: %d)\n", i, traveller[i][1], traveller[i][0], traveller[i][2]);

			//designate travelled paths
			travelPath.mapNodes[traveller[i][0]][traveller[i][1]].type = NodeType::Debug;
		}

		if (!foundNewNode)
		{
			//edge case, no new nodes found becasue map generated cyclical (ask day for more info)
			if (isEndNode(currentNode))
			{	bool alreadyListed = false;
				for (int i = 0; i < endNodes.size(); i++)
				{	if (endNodes[i][0] == currentX && endNodes[i][1] == currentY)
					{
						alreadyListed = true;
						break;
				}	}
				//push end node if not already listed
				if (!alreadyListed) endNodes.push_back({ traveller[0] });
		}	}

		//delete the current traveller node since it has located all possible new nodes
		printf("deleting traveller at: %d, %d (Distance: %d)\n", traveller[0][1], traveller[0][0], traveller[0][2]);
		traveller.erase(traveller.begin());


		//check if all nodes explored
		allNodesExplored = true;
		for (int y = 0; y < yLen; y++) {for (int x = 0; x < xLen; x++) {
				if (travelPath.mapNodes[y][x].type != NodeType::Debug) { allNodesExplored = false;}
		}	}
	}
	printf("All Nodes Explored!\n");

	//print debug map after exploration
	printf("Printing Map Display post-Exploration\n");
	Map::DebugPrint(travelPath);

	int largestIndex = 0;

	printf("Designating Exit Node.\n");
	//select the saved index for the farthest end node 
	for (int i = 1; i < endNodes.size(); i++)
	{
		printf("End Node %d, %d, distance: %d, accepted.\n", endNodes[i][1], endNodes[i][0], endNodes[i][2]);
		if (endNodes[i][2] > endNodes[largestIndex][2]) largestIndex = i;
	}

	outMap.mapNodes[endNodes[largestIndex][0]][endNodes[largestIndex][1]].type = NodeType::Exit;
	printf("Exit Node Designation complete.\n");

	//erase debug map
	printf("Erasing Exploration Debug Map.\n");
	travelPath.mapNodes.clear();

	//remove entry and exit nodes from endNode list
	endNodes.erase(endNodes.begin() + largestIndex);
	endNodes.erase(endNodes.begin());

	//designate map-specific fixed-event node on one of the remaining end nodes
	printf("Generating Map-Specific Event Node.\n");
	int eventNodeIndex = std::uniform_int_distribution<>(0, static_cast<int>(endNodes.size()) - 1)(gen);
	
	switch (type)
	{
		case MapType::Debug:
			printf("No Map-Specific Event Node Generated for Debug Map.\n");
			break;
		case MapType::CityStreets:
		{
			printf("No Map-Specific Event Node Generated for City Streets Map.\n");
			break;
		}
		case MapType::OuterPalace:
		{
			outMap.mapNodes[endNodes[eventNodeIndex][0]][endNodes[eventNodeIndex][1]].type = NodeType::FixedEvent;
			printf("Outer Palace Event Node Designated at %d, %d.\n", endNodes[eventNodeIndex][1], endNodes[eventNodeIndex][0]);
			break;
		}
		case MapType::InnerPalace:
		{
			outMap.mapNodes[endNodes[eventNodeIndex][0]][endNodes[eventNodeIndex][1]].type = NodeType::FixedEvent;
			printf("Specific Event Node Designated at %d, %d.\n", endNodes[eventNodeIndex][1], endNodes[eventNodeIndex][0]);
			break;
		}
		default:
			printf("No Map-Specific Event Node Generated for Unknown MapType Map.\n");
			break;
	}
	
	//setup for designation of remaining nodes
	std::uniform_int_distribution<> randPercent(1, 100);

	//designate remaining nodes as random event or enemy encounter at a chance
	printf("Designating Remaining Nodes as Random Events or Enemy Encounters.\n");

	for (int y = 0; y < yLen; y++) { for (int x = 0; x < xLen; x++) {
		if (outMap.mapNodes[y][x].type == NodeType::Empty)
		{
			int rollPanel = randPercent(gen);
			if (rollPanel <= 70) //30% chance of random event
			{
				int rollType = randPercent(gen);

				if (rollType <= 65) //65% chance of encounter 
					outMap.mapNodes[y][x].type = NodeType::EnemyEncounter;
				else	
					outMap.mapNodes[y][x].type = NodeType::RandomEvent;
	}	}	}	}
	
	return outMap;
}

void Map::DebugPrint(Map map)
{
	//printing in blocks of 3x3 characters per node for representation
	size_t height = map.mapNodes.size() * 3, length = map.mapNodes[0].size() * 3;
	for (int y = 0; y < height; y++) {for (int x = 0; x < length; x++) {
		int yPos = y % 3, xPos = x % 3;
		char out = '#'; //standard character for wall
		MapNode currentNode = map.mapNodes[y / 3][x / 3];
		bool centerNode = false;

		if (yPos == 1) //height check
		{
			switch (xPos)
			{
				case 0: //west
					if (currentNode.w == false) out = ' ';
					break;
				case 2: //east
					if (currentNode.e == false) out = ' ';
					break;
				default:
					centerNode = true;
			}
		}
		else if (xPos == 1)
		{
			switch (yPos)
			{
				case 0: //north
					if (currentNode.n == false) out = ' ';
					break;
				case 2: //south
					if (currentNode.s == false) out = ' ';
					break;
				default:
					centerNode = true;
					
			}
		}
		if (centerNode)
		{
			switch (currentNode.type)
			{
				case NodeType::Debug:
					out = 'D';
					break;
				case NodeType::Empty:
					out = ' ';
					break;
				case NodeType::EnemyEncounter:
					out = 'E';
					break;
				case NodeType::RandomEvent:
					out = 'R';
					break;
				case NodeType::FixedEvent:
					out = 'F';
					break;
				case NodeType::Entry:
					out = 'N';
					break;
				case NodeType::Exit:
					out = 'X';
					break;
			}
		}

		printf("%c", out);
		}
	printf("\n");
	}
	printf("end of map debug printing.\n");
}

bool isEndNode(MapNode node)
{
	int count = 0;
	if (node.n) count++;
	if (node.s) count++;
	if (node.e) count++;
	if (node.w) count++;
	if (count<3) return false;
	return true;
}

Map::Map()
{
	Map::mapType = MapType::Debug;
	Map::mapNodes.clear();
	//bruh
}

Map::~Map()
{
}