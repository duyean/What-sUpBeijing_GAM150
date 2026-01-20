#pragma once
#include "AEEngine.h"

//global combat enums and classes

namespace Game
{
	static int DEF_CONSTANT = 500; //The Damage Reduction from DEF will be 0.5 at this DEF value

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
		PLAYER,
		ENEMY
	};

	enum EFFECT_TYPE
	{
		ATTRIBUTE_MODIFIER,
		STUN,
		BURN,
		POISON,
	};

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

	//This enum will be used for handling same buff situations
	enum MODIFIER_ID
	{
		NONE,
		GENERIC_DOT_BURN,
		GENERIC_DOT_POISON,
		GENERIC_STUN,
		GENERIC_MODIFIER,
		//Custom Modifiers
	};

	class Modifier
	{
	public:
		const char* name;
		int duration;
		EFFECT_TYPE effectType;
		AEGfxTexture icon;
		MODIFIER_ID ID;
		virtual ~Modifier() = default;
	};

	class AttributeModifier : public Modifier
	{
	public:
		float value;
		ATTRIBUTE_TYPE attributeType;
	};

	class StatusEffect : public Modifier
	{
	public:
		float damage;
	};
}