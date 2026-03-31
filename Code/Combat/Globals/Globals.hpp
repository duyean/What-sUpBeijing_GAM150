#pragma once
#include <random>
#include <unordered_map>
//global combat enums

class Character;

namespace Game
{
	enum struct CHARACTER_ID
	{
		DEBUFFER_CHICK,
		DPS_DUDE,
		BUFFER_ASSASSIN,
		OP_VOID_ASSASSIN,
		TOTAL,
	};

	static constexpr int DEF_CONSTANT = 5000; //The Damage Reduction from DEF will be 0.5 at this DEF value
	static std::random_device seedling;
	static std::mt19937 gen(seedling());
	static std::unordered_map<CHARACTER_ID, std::string> charIDToString = { {CHARACTER_ID::DEBUFFER_CHICK, "Char3"}, 
		{CHARACTER_ID::DPS_DUDE, "Char2"}, {CHARACTER_ID::BUFFER_ASSASSIN, "Guy"}, {CHARACTER_ID::OP_VOID_ASSASSIN, "Char4"}};


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

	enum WUXING_ELEMENT
	{
		FIRE,
		EARTH,
		WOOD,
		WATER,
		METAL,
		NORMAL
	};

	enum FACTION
	{
		NONE,
		PLAYER,
		ENEMY
	};

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

	struct DamageInfo
	{
		float damage = 0;
		bool isCritical = false;
		Character* source = nullptr;
		WUXING_ELEMENT elementType = NORMAL;
	};
}