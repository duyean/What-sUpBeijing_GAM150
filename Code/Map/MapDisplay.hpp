#pragma once
#include "../SceneHandler_WZBJ_Pak.hpp"
#include "../Engine_WZBJ_Pak.hpp"
#include "NavigationData.hpp"

/*!************************************************************************
* \file MapDisplay.hpp
* \author Daniel Tan
* \par DP email: t.daniel@digipen.edu
* \par Course: CSD1451
* \par Section: B
* \brief
*   This file defines the MapDisplay class, which inherits the SoloBehavior component class 
*   and is responsible for displaying the map on screen using the NavigationData class as a reference.
*   It also contains functions for updating the map display as the player moves through the map.
**************************************************************************/

using namespace std;

class EntityManager;
class MeshGen;

/*!***********************************************************************
* \class Map
* \brief
*  The MapDisplay class, responsible for controlling the Map Display on screen using the NavigationData class as a reference.
*************************************************************************/
class MapDisplay : public SoloBehavior
{
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
	"../../Assets/Images/MapIcons/Shop.png",			//shop node
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
	/*!***********************************************************************
	* \brief
	* Runs on component creation, used for initial setup before init. Should not rely on other components being awake or init at this point.
	* \return
	*  void
	*************************************************************************/
	void awake() override;
	/*!***********************************************************************
	* \brief
	* Runs before first update, after awake.
	* \return
	*  void
	*************************************************************************/
	void init() override;
	/*!***********************************************************************
	* \brief
	* Runs every frame, used for game logic updates. Should only rely on other components being awake and init at this point.
	* \return
	*  void
	*************************************************************************/
	void update() override;
	/*!***********************************************************************
	* \brief
	* Runs every fixed timestep, used for physics updates. Should only rely on other components being awake and init at this point.
	* \return
	*  void
	*************************************************************************/
	void fixedUpdate() override;
	/*!***********************************************************************
	* \brief
	* Runs on component destruction, used for cleanup. Should not rely on other components still existing at this point.
	* \return
	*  void
	*************************************************************************/
	void destroy() override;

	/*!***********************************************************************
	* \brief
	* Constructor for MapDisplay, takes a reference to a NavigationData object to use as the basis for the map display. Initializes member variables.
	* \return
	*  void
	*************************************************************************/
	MapDisplay(NavigationData& _map) : mapNodesReal{ nullptr }, mapNodesFog{ nullptr }, map{ _map }, x{0}, y{0} {}
	/*!***********************************************************************
	* \brief
	* Destructor for MapDisplay, currently does not need to do anything as there are no dynamically allocated resources that need to be cleaned up. 
	* If any are added in the future, they should be cleaned up here. -day
	* \return
	*  void
	*************************************************************************/
	~MapDisplay() {}
};