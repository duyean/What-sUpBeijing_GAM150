#pragma once
#include "MapNodeClass.hpp"
#include "MapTypeClass.hpp"
#include "../BaseSystems/JSONSerializer/JSONSerializer.hpp"

/*!************************************************************************
* \file MapClass.hpp
* \author Daniel Tan
* \par DP email: t.daniel@digipen.edu
* \par Course: CSD1451
* \par Section: B
* \brief
*   This file defines the Map class, containing a Map Type enum as well as a 
*	nested vector of MapNodes. 
*	It also contains functions for generating, saving, and loading maps.
**************************************************************************/

#include <vector>

/*!***********************************************************************
* \class Map
* \brief
*  The Map class  
*************************************************************************/
class Map
{
public:
	std::vector<std::vector <MapNode>> mapNodes{};
	MapType mapType;

	//NOTE: xLen and yLen are unique grid value, NOT PIXEL POSITION!

	/*!***********************************************************************
	* \brief
	*  Generates a map of the given type and dimensions, and stores it in the mapNodes vector
	* \param[in] type
	*  The map type used to generate
	* \param[in] xLen
	*  The width of the map to generate
	* \param[in] yLen
	*  The height of the map to generate
	* \return
	*  void
	*************************************************************************/
	void GenerateMap(MapType type, int xLen, int yLen);
	/*!***********************************************************************
	* \brief
	*  Prints the current map to the console for debugging purposes
	* \param[in] Map
	*  Literally the map
	* \return
	*  void
	*************************************************************************/
	static void DebugPrint(Map map);
	/*!***********************************************************************
	* \brief
	*  Save the map to a JSON file with the given filename, using the given JSONSerializer
	* \param[in] JSONSerializer
	*  JSONSerializer object used to save the map
	* \param[in] fileName
	* name of the file to save to, should be in the format "filename.json"
	* \return
	*  bool, true if the save was successful, false if it failed (e.g. file could not be opened)
	*************************************************************************/
	bool SaveMap(JSONSerializer serializer, std::string fileName);
	/*!***********************************************************************
	* \brief
	*  Load the map from a JSON file with the given filename, using the given JSONSerializer
	* \param[in] &JSONSerializer
	*  JSONSerializer object used to save the map
	* \param[in] fileName
	* name of the file to save to, should be in the format "filename.json"
	* \return
	*  bool, true if the save was successful, false if it failed (e.g. file could not be opened)
	*************************************************************************/
	bool LoadMap(JSONSerializer& serializer, std::string fileName);

	/*!***********************************************************************
	* \brief
	*  Default Constructor
	*************************************************************************/
	Map();
	/*!***********************************************************************
	* \brief
	*  Default Destructor
	*************************************************************************/
	~Map();

	/*!***********************************************************************
	* \brief
	*  Copy Constructor
	*************************************************************************/
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