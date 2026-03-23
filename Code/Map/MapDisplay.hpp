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
	Entity* mapCharIcon = {};
	std::vector<Entity*> mapNodesReal = {};
	std::vector<Entity*> mapNodesFog = {};
	int x, y;

	#define TEXTURE_COUNT 9

	string textureDir[TEXTURE_COUNT] =
	{
	"../../Assets/Images/MapIcons/FogTile.png",			//fog no vision
	"../../Assets/Images/MapIcons/Tile.png",			//standard tile
	"../../Assets/Images/MapIcons/Exclamation.png",		//enemy encounter
	"../../Assets/Images/MapIcons/Question.png",		//random encounter
	"../../Assets/Images/MapIcons/Entrance.png",		//map start
	"../../Assets/Images/MapIcons/Exit.png",			//boss fight
	"../../Assets/Images/MapIcons/Wall.png",			//shop (TEMPORARY PLS REPLACE)
	"../../Assets/Images/MapIcons/Sprite.png",			//player sprite 
	"../../Assets/Images/MapIcons/FixedEvent.png"		//fixed encounter
	};

	string textureName[TEXTURE_COUNT] =
	{
	"FogTile",			//fog no vision
	"BaseTile",			//standard tile
	"EncounterTile",	//enemy encounter
	"EventTile",		//random encounter
	"EntranceTile",		//map start
	"ExitTile",			//boss fight
	"ShopTile",			//shop
	"PlayerIcon",		//player sprite 
	"FixedEventTile"	//fixed encounter
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