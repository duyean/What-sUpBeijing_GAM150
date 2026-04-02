#pragma once
#include "MapClass.hpp"
#include "../BaseSystems/JSONSerializer/JSONSerializer.hpp"

/*!************************************************************************
* \file NavigationDataClass.hpp
* \author Daniel Tan
* \par DP email: t.daniel@digipen.edu
* \par Course: CSD1451
* \par Section: B
* \brief
*   This file defines the NavigationData class, 
*	which contains the current map information and player position information that is used to control the map display and player movement through the map.
**************************************************************************/

#include <vector>

/*!***********************************************************************
* \class NodeType
* \brief
*   The NavigationData class, which contains the current map information and 
*	player position information that is used to control the map display and player movement through the map.
*************************************************************************/
class NavigationData
{
public:
	Map viewMap{};
	Map playMap{};
	int xPos, yPos; //x, y position on playMap (set to 0 on default)

	/*!***********************************************************************
	* \brief
	*  Generates a complete set of map data of the given type and dimensions, and stores it in the viewMap and playMap variables. 
	*  As well as setting the player position to the starting node of the playMap.
	* \param[in] type
	*  MapType enum/ID to be used for generation of the map data
	* \param[in] xLen
	*  Horizontal width of the map to be generated (in unique grid values, NOT PIXEL POSITION)
	* \param[in] yLen
	*  Vertical height of the map to be generated (in unique grid values, NOT PIXEL POSITION)
	* \return
	*  void (The result is saved to this class itself. No return value is necessary.)
	*************************************************************************/
	void GenerateNavigationData(MapType type, int xLen, int yLen);
	/*!***********************************************************************
	* \brief
	*  Saves the current map data in the viewMap and playMap variables as well as player position to multiple JSON files, using the given JSONSerializer
	* \param[in] seralizer
	*  JsonSerializer object used to save the map
	* \return
	*  bool > true if the generation was successful, false if it failed (e.g. invalid map type)
	*************************************************************************/
	bool SaveNavigationData(JSONSerializer serializer);
	/*!***********************************************************************
	* \brief
	*  Loads map data in the viewMap and playMap variables as well as player position from multiple JSON files to this class, using the given JSONSerializer
	* \param[in] &seralizer
	*  JsonSerializer object used to load the map
	* \return
	*  bool > true if the generation was successful, false if it failed (e.g. invalid map type)
	*************************************************************************/
	bool LoadNavigationData(JSONSerializer& serializer);

	/*!***********************************************************************
	* \brief
	*  Default Constructor
	*************************************************************************/
	NavigationData();
	/*!***********************************************************************
	* \brief
	*  Default Destructor
	*************************************************************************/
	~NavigationData();

	/*!***********************************************************************
	* \brief
	*  Copy Constructor
	*************************************************************************/
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