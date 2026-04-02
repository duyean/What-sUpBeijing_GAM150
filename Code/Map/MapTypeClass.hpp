#pragma once

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