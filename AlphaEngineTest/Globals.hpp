#pragma once
#include "AEEngine.h"

namespace Game
{
	static int DEF_CONSTANT = 500; //The Damage Reduction from DEF will be 0.5 at this DEF value

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
		CRIT_DAMAGE
	};

	class Modifier
	{
		const char* name;
		int duration;
		EFFECT_TYPE effectType;
		AEGfxTexture icon;
	};

	class AttributeModifier : public Modifier
	{
		float value;
		ATTRIBUTE_TYPE attributeType;
	};

	class StatusEffect : public Modifier
	{
		float damage;
	};
}