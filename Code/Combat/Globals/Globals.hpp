#pragma once
#include "AEEngine.h"

//global combat enums and classes

namespace Game
{
	static int DEF_CONSTANT = 500; //The Damage Reduction from DEF will be 0.5 at this DEF value

	enum FACTION
	{
		PLAYER,
		ENEMY
	};

	enum EFFECT_TYPE
	{
		ATTRIBUTE_BUFF,
		ATTRIBUTE_DEBUFF,
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

	class Modifier
	{
	public:
		const char* name;
		int duration;
		EFFECT_TYPE effectType;
		AEGfxTexture icon;
		virtual ~Modifier() {};
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