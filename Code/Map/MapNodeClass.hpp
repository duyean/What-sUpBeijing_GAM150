#pragma once
enum class NodeType
{
	Debug , //can also represent ungenerated node
	Empty,
	EnemyEncounter,
	RandomEvent,
	FixedEvent
};

class MapNode
{
public:
	bool n, s, e, w; //connections
	NodeType type;
};

