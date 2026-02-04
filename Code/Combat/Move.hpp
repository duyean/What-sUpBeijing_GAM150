#pragma once
#include <string>
#include <vector>
#include "../Combat/Globals/Globals.hpp"
#include "Modifier/Modifier.hpp"
#include "../BaseSystems/JSONSerializer/JSONSerializer.hpp"

enum MOVE_SLOT
{
	MOVE_SLOT_1,
	MOVE_SLOT_2,
	MOVE_SLOT_3,
	MOVE_SLOT_4
};

enum MOVE_ID
{
	MOVE_BASIC_ATK = 0,
	MOVE_BURN_MOVE = 1,
};

class Move
{
public:
	//The name of the move
	std::string name;

	/*
	How much damage to deal.

	0.2 means deal 20% ATK as damage, also affects healing type moves.

	Leave this value at 0 for non-damaging moves
	*/
	float coefficient = 0.f;

	/*
	This value is arbitrary if the move does not
	apply a DOT Effect.

	0.2 means 20% ATK as damage every turn
	*/
	float dot_coefficient;

	//A short description of the move. (Shown in tooltip?)
	std::string brief;

	//A full description of the move. (Shown in character page)
	std::string description;

	/*
	Store MODIFIER_IDs (declared in Modifier.hpp) to
	have this move apply the effect to the target
	*/
	std::vector<MODIFIER_ID> moveModifiers {};

	/*
	Which group the move targets:
	SELF(0) -> Self-Casted
	ALLY(1) -> Target Ally
	OPPOSITE(2) -> Target Enemy
	*/
	Game::MOVE_TARGET_GROUP targetGroup;

	Move()
	{
		coefficient = dot_coefficient = 0;
		name = description = brief = "";
	}
	Move(std::string name, float coefficient, float dot_coeff, std::string brief, std::string desc, Game::MOVE_TARGET_GROUP target) :
		name(name), coefficient(coefficient), dot_coefficient(dot_coeff), brief(brief), description(desc), targetGroup(target) {};
	~Move() = default;

	static std::unordered_map<MOVE_ID, Move> moveDatabase;
	static void InitMoveDatabase(JSONSerializer& serializer, std::string fileName);
};