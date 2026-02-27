#pragma once
#include <string>
#include "../EventHandler/CombatEventHandler.hpp"
#include "../Globals/Globals.hpp"
#include "../Extern/AlphaEngine/include/AEEngine.h"

class Character;

enum struct BLESSING_ID
{
	NONE,
	MINOR_ATK_BUFF,
	MINOR_DEF_BUFF,
	MINOR_HP_BUFF
};

enum struct BLESSING_TYPE
{
	ATTRIBUTE_BOOST,
	TRIGGERED_BLESSING
};

enum struct BLESSING_RARITY
{
	COMMON,
	RARE,
	LEGENDARY,
	MYTHICAL
};


class Blessing
{
public:
	//The ID of the blessing
	BLESSING_ID id;

	//The name of the blessing
	std::string blessingName;

	//A description of the blessing to display during selection
	std::string blessingDesc;

	//The type of blessing, whether it is a attribute buff or a trigger type
	BLESSING_TYPE blessingType;

	//The rarity of the blessing. Used for the RNG weightage
	BLESSING_RARITY blessingRarity;

	//The icon of the blessing
	AEGfxTexture* logo;
	Blessing();
	Blessing(BLESSING_ID, std::string, std::string, BLESSING_TYPE, BLESSING_RARITY, AEGfxTexture*);
	virtual void Apply(Character* target) = 0;
	virtual void RemoveBuff(Character* target) = 0;
	virtual ~Blessing() = default;
};

class AttributeBlessing : public Blessing
{
public:
	Game::ATTRIBUTE_TYPE attType;
	float value;
	void Apply(Character* target) override;
	void RemoveBuff(Character* target) override;
	AttributeBlessing(BLESSING_ID id,
		std::string name,
		std::string desc,
		BLESSING_RARITY rarity,
		AEGfxTexture* logo,
		Game::ATTRIBUTE_TYPE type,
		float val)
		: Blessing(id, name, desc, BLESSING_TYPE::ATTRIBUTE_BOOST, rarity, logo),
		attType(type),
		value(val) {}

};

class TriggerBlessing : public Blessing
{
public:
	EventType triggerType;
	std::function<void(const EventData& data)> triggerEffect;
	int blessingCooldown;
	int cooldown;
	void Apply(Character* target) override;
	void RemoveBuff(Character* target) override;

	TriggerBlessing(BLESSING_ID id,
		std::string name,
		std::string desc,
		BLESSING_RARITY rarity,
		AEGfxTexture* logo,
		EventType trigger,
		std::function<void(const EventData&)> effect,
		int cd)
		: Blessing(id, name, desc, BLESSING_TYPE::TRIGGERED_BLESSING, rarity, logo),
		triggerType(trigger),
		triggerEffect(effect),
		blessingCooldown(cd),
		cooldown(0) {
	}
};