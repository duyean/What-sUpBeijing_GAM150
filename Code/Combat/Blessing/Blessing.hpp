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
	MINOR_HP_BUFF,
	MINOR_CRITRATE_BUFF,
	MINOR_CRITDMG_BUFF,
	MAJOR_ATK_BUFF,
	MAJOR_DEF_BUFF,
	MAJOR_HP_BUFF,
	MAJOR_CRITRATE_BUFF,
	MAJOR_CRITDMG_BUFF,
	MINOR_DMG_BOOST_BUFF,
	MAJOR_DMG_BOOST_BUFF,
	MINOR_DMG_RED_BUFF,
	MAJOR_DMG_RED_BUFF,
	GAIN_ATK_ON_DAMAGE_TAKEN,
	GAIN_CRIT_DMG_ON_CRIT_HIT
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

	// The texture of the blessing. Used for rendering in shop
	std::string textureName;

	//The icon of the blessing
	std::string logo;
	Blessing();
	Blessing(BLESSING_ID, std::string, std::string, BLESSING_TYPE, BLESSING_RARITY, std::string, std::string);

	virtual std::unique_ptr<Blessing> Clone() const = 0;

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
		std::string logo,
		Game::ATTRIBUTE_TYPE type,
		float val,
		std::string texture = "Temp_Texture")
		: Blessing(id, name, desc, BLESSING_TYPE::ATTRIBUTE_BOOST, rarity, logo, texture),
		attType(type),
		value(val) {}

	std::unique_ptr<Blessing> Clone() const override;

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
		std::string logo,
		EventType trigger,
		std::function<void(const EventData&)> effect,
		int cd,
		std::string texture = "Temp_Texture")
		: Blessing(id, name, desc, BLESSING_TYPE::TRIGGERED_BLESSING, rarity, logo, texture),
		triggerType(trigger),
		triggerEffect(effect),
		blessingCooldown(cd),
		cooldown(0) {
	}

	std::unique_ptr<Blessing> Clone() const override;
};

extern std::unordered_map<BLESSING_ID, std::unique_ptr<Blessing>> blessingDatabase;
extern void InitBlessingDatabase();