/*!
@file Move.hpp
@author Wayne Lion (lion.w)
@course CSD11451
@section B
@Final Project
@date 25/2/26
@brief
This file contains the interface for a Move that Characters use
*//*______________________________________________________________________*/

#pragma once
#include <string>
#include <vector>
#include "../Combat/Globals/Globals.hpp"
#include "Modifier/Modifier.hpp"
#include "../BaseSystems/JSONSerializer/JSONSerializer.hpp"

//Enum to store MOVE SLOTS
enum struct MOVE_SLOT
{
	NONE = -1,
	MOVE_SLOT_1,
	MOVE_SLOT_2,
	MOVE_SLOT_3,
	MOVE_SLOT_4
};

//Enum to store MOVE_IDs
enum MOVE_ID
{
	MOVE_BASIC_ATK = 0,
	MOVE_BURN_MOVE = 1,
};

/*!***********************************************************************
* \class Move
* \brief
* Class to store the data of a move
*************************************************************************/
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

	//A short description of the move which is shown in tooltips
	std::string brief;

	//A full description of the move.
	std::string description;

	//The resource required to use the mmove, if negative, the party gains said resource instead.
	//Enemies do not use this mechanic
	int moveCost;

	/*
	Store MODIFIER_IDs (declared in Modifier.hpp) to
	have this move apply the effect to the target
	*/
	std::vector<MODIFIER_ID> moveModifiers {};

	//Determines which targets the Move will target
	Game::MOVE_TARGET_GROUP targetGroup;

	//Default constructor
	Move() : targetGroup(Game::OPPOSITE), moveCost(0)
	{
		coefficient = dot_coefficient = 0;
		name = description = brief = "";
		moveCost = 0;
	}

	//Customised constructor
	Move(std::string name, float coefficient, float dot_coeff, std::string brief, std::string desc, Game::MOVE_TARGET_GROUP target, int cost) :
		name(name), coefficient(coefficient), dot_coefficient(dot_coeff), brief(brief), description(desc), targetGroup(target), moveCost(cost) {};

	//Default destructor
	~Move() = default;

	//A map to store all the MOVES used in the game
	static std::unordered_map<MOVE_ID, Move> moveDatabase;

	/*!***********************************************************************
	* \brief
	* Initialise the MOVE DATABASE from the JSON file
	* \param serializer
	* A reference to the JSON serializer
	* \param fileName
	* The name of the Moves JSON file
	*************************************************************************/
	static void InitMoveDatabase(JSONSerializer& serializer, std::string fileName);
};