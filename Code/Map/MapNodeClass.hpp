#pragma once

class MapNode
{
public:
	bool contentCleared;
	NodeType type;
};

enum NodeType
{
	Debug = 0,
	Empty = 1,
	EnemyEncounter = 2,
	RandomEvent = 3,
	FixedEvent = 4
};