/*!
@file Blessing.hpp
@author Wayne Lion (lion.w)
@course CSD11451
@section B
@Final Project
@date 25/2/26
@brief
This file contains the interface for a Blessing object for our game.
*//*______________________________________________________________________*/

#pragma once
#include <string>
#include "../EventHandler/CombatEventHandler.hpp"
#include "../Globals/Globals.hpp"
#include "../Extern/AlphaEngine/include/AEEngine.h"

class Character;

//Enum to store the blessing ID
enum struct BLESSING_ID
{
	NONE,
	MINOR_ATK_BUFF,
	MINOR_DEF_BUFF,
	MINOR_HP_BUFF
};

//Enum to determine what kind of blessing
enum struct BLESSING_TYPE
{
	ATTRIBUTE_BOOST,
	TRIGGERED_BLESSING
};

//Enum to determine the rarity of this blessing
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

	//Virtual function to apply this blessing effect
	virtual void Apply(Character* target) = 0;

	//Virtual function to remove this blessing effect
	virtual void RemoveBuff(Character* target) = 0;
	virtual ~Blessing() = default;
};

class AttributeBlessing : public Blessing
{
public:
	//Determines the attribute to affect
	Game::ATTRIBUTE_TYPE attType;

	//Determines the intensity of the blessing effect
	float value;

	//Override for virtual function
	void Apply(Character* target) override;

	//Override for virtual function
	void RemoveBuff(Character* target) override;

	//Constructor
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
	//Determines what kind of event to trigger this blessing
	EventType triggerType;

	//Determines the actual effect of this blessing
	std::function<void(const EventData& data)> triggerEffect;

	//Determines how frequently this blessing can be triggered
	int blessingCooldown;

	//The counter for the cooldown
	int cooldown;

	//Override
	void Apply(Character* target) override;

	//Override
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