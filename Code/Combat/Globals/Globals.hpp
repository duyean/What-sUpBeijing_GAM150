#pragma once
#include <random>
//global combat enums

class Character;

namespace Game
{
	static constexpr int DEF_CONSTANT = 500; //The Damage Reduction from DEF will be 0.5 at this DEF value
	static std::random_device seedling;
	static std::mt19937 gen(seedling());

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
	};

	struct DamageInfo
	{
		float damage = 0;
		bool isCritical = false;
		Character* source = nullptr;
		WUXING_ELEMENT elementType = NORMAL;
	};
}