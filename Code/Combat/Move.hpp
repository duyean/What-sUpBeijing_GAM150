#pragma once
#include <string>
#include <vector>
#include "../Combat/Globals/Globals.hpp"

enum MOVE_SLOT
{
	MOVE_SLOT_1,
	MOVE_SLOT_2,
	MOVE_SLOT_3,
	MOVE_SLOT_4
};



class Move
{
public:
	//The name of the move
	std::string name;

	//How much damage to deal, set to 0.0 for non-damaging moves. Affects healing moves as well.
	float coefficient;

	//A short description of the move. (Shown in tooltip?)
	std::string brief;

	//A full description of the move. (Shown in character page)
	std::string description;

	//Extra effects to the move
	std::vector<Game::Modifier> moveModifiers;

	//Which group the move targets
	Game::FACTION targetGroup;

	~Move() = default;
};