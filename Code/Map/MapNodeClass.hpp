#pragma once
enum class NodeType
{
	Debug =				 0, //can also represent ungenerated node
	Empty =				 1,
	EnemyEncounter =	 2,
	RandomEvent =		 4,
	FixedEvent =		 5,

	//special nodes
	Entry =				-1,
	Exit =				-2  //also represents boss node!!!
};

class MapNode
{
public:
	bool n, s, e, w; //connections
	NodeType type;
};

