#pragma once
#include "../SceneHandler_WZBJ_Pak.hpp"
#include "../Engine_WZBJ_Pak.hpp"
#include "NavigationData.hpp"

using namespace std;

class EntityManager;
class MeshGen;

class MapDisplay : public SoloBehavior
{
private:

public:
	NavigationData& map;
	std::vector<Entity*> mapNodesReal;
	std::vector<Entity*> mapNodesFog;
	int x, y;

	#define TEXTURE_COUNT 6

	string textureDir[TEXTURE_COUNT] =
	{
	"../Assets/Image/MapIcons/FogTile.png",			//fog no vision
	"../Assets/Image/MapIcons/Tile.png",			//standard tile
	"../Assets/Image/MapIcons/Exclaimation.png",	//enemy encounter
	"../Assets/Image/MapIcons/Question.png",		//random encounter
	"../Assets/Image/MapIcons/Entrance.png",		//map start
	"../Assets/Image/MapIcons/Exit.png"				//boss fight
	};

	string textureName[TEXTURE_COUNT] =
	{
	"FogTile",			//fog no vision
	"BaseTile",			//standard tile
	"EncounterTile",	//enemy encounter
	"EventTile",		//random encounter
	"EntranceTile",		//map start
	"ExitTile"			//boss fight
	};

	EntityManager* enSystem = nullptr;
	MeshGen* meSystem = nullptr;

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	MapDisplay(NavigationData& _map) : mapNodesReal{ nullptr }, mapNodesFog{ nullptr }, map{ _map }, x{0}, y{0} {}
	~MapDisplay() {}
};