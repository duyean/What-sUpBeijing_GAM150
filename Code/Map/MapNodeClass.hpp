#pragma once
enum class NodeType
{
	Debug = 0,
	Empty = 1,
	EnemyEncounter = 2,
	RandomEvent = 3,
	FixedEvent = 4
};

class MapNode
{
public:
	bool navigable;
	NodeType type;
};

