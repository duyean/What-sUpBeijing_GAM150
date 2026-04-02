#pragma once

/*!************************************************************************
* \file MapTypeClass.hpp
* \author Daniel Tan
* \par DP email: t.daniel@digipen.edu
* \par Course: CSD1451
* \par Section: B
* \brief
*   This file defines a set of map types that can be used in the game, 
*	an ID system that contains all the different map types that can be generated.
**************************************************************************/

/*!***********************************************************************
* \class MapType
* \brief
*	The MapType enum, which contains all the different ID types of maps that can be generated in the game, 
*	as well as a special ID for the unique fog overlay map.
*************************************************************************/
enum MapType
{
	//for debugging
	Debug,

	//gameplay maps
	CityStreets,
	OuterPalace,
	InnerPalace,
	NUM_MAPTYPES,
	SilentStreets, //easter egg map (Empty Map with only boss at end)

	//fog overlay map 
	OverlayFog = -1
};