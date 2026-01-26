#pragma once
//global combat enums

namespace Game
{
	static constexpr int DEF_CONSTANT = 500; //The Damage Reduction from DEF will be 0.5 at this DEF value

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
		METAL
	};

	enum FACTION
	{
		NONE,
		PLAYER,
		ENEMY
	};
}