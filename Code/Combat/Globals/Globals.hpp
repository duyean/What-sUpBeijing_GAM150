/*!
@file Globals.hpp
@author Wayne Lion (lion.w)
@course CSD11451
@section B
@Final Project
@date 25/2/26
@brief
This file contains global combat enums used for the game
*//*______________________________________________________________________*/

#pragma once
#include <random>
#include <unordered_map>
//global combat enums

class Character;

namespace Game
{
	//Enum to store character IDs
	enum struct CHARACTER_ID
	{
		DEBUFFER_CHICK,
		DPS_DUDE,
		BUFFER_ASSASSIN,
		OP_VOID_ASSASSIN,
		TOTAL,
	};

	//The Damage Reduction from DEF will be 0.5 at this DEF value
	static constexpr int DEF_CONSTANT = 5000; 

	//The seed for RNG functions
	static std::random_device seedling;

	//The generator for RNG functions
	static std::mt19937 gen(seedling());

	//Data to store CHARACTER IDs to the strings for their corresponding JSON file
	static std::unordered_map<CHARACTER_ID, std::string> charIDToString = { {CHARACTER_ID::DEBUFFER_CHICK, "Char3"}, 
		{CHARACTER_ID::DPS_DUDE, "Char2"}, {CHARACTER_ID::BUFFER_ASSASSIN, "Guy"}, {CHARACTER_ID::OP_VOID_ASSASSIN, "Char4"}};

	//Enum to store ATTRIBUTE TYPES
	enum ATTRIBUTE_TYPE
	{
		ATK,
		DEF,
		HP,
		CRIT_RATE,
		CRIT_DAMAGE,
		DMG_BONUS,
		DMG_REDUCTION
	};

	//Enum to store the element of the character for combat
	enum WUXING_ELEMENT
	{
		FIRE,
		EARTH,
		WOOD,
		WATER,
		METAL,
		NORMAL
	};

	//Enum to store the FACTION of a Character
	enum FACTION
	{
		NONE,
		PLAYER,
		ENEMY
	};

	//Enum to store the MOVE's TARGETING
	enum MOVE_TARGET_GROUP
	{
		//The move can target the caster only
		SELF = 0,
		//The move can target one of the units on the same team as the caster
		ALLY,
		//The move can target the opposing team only
		OPPOSITE,
		//The move targets all units on the opposing team
		AOE_OPPOSITE,
		//The move targets all allies on the team
		AOE_ALLY
	};

	//A struct to store Damage information
	struct DamageInfo
	{
		float damage = 0;
		bool isCritical = false;
		Character* source = nullptr;
		WUXING_ELEMENT elementType = NORMAL;
	};
}