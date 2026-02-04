#pragma once
enum class NodeType
{
	//standard nodes
	Debug =				 0, //can also represent ungenerated node
	Empty =				 1,
	EnemyEncounter =	 2,
	RandomEvent =		 4,
	FixedEvent =		 5,

	//special nodes
	Entry =				-1,
	Exit =				-2,  //also represents boss node!!!

	//overlay nodes
	VisionFog =			-11,
	VisionClear =		-12	
};

class MapNode
{
public:
	bool n, s, e, w; //connections
	NodeType type;
};

