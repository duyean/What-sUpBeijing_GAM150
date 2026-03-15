/*!
@file Blessing.cpp
@author Wayne Lion (lion.w)
@course CSD11451
@section B
@Final Project
@date 25/2/26
@brief
This file contains the implementation for a Blessing object for our game.
*//*______________________________________________________________________*/

#include "Blessing.hpp"
#include "../Character/Character.hpp"

Blessing::Blessing() : id(BLESSING_ID::NONE), blessingName("name"), blessingDesc("desc"), textureName("Temp_Texture"),
blessingType(BLESSING_TYPE::ATTRIBUTE_BOOST), blessingRarity(BLESSING_RARITY::COMMON), logo("") 
{
}

Blessing::Blessing(BLESSING_ID id, std::string name, std::string desc, BLESSING_TYPE type, BLESSING_RARITY rarity, std::string icon, std::string texture = "Temp_Texture") : id(id),
blessingName(name), blessingDesc(desc), blessingType(type), blessingRarity(rarity), logo(icon), textureName(texture)
{
}

void AttributeBlessing::Apply(Character* target)
{
	//Create a new modifier based on the attribute type and add it to the player
	auto mod = std::make_unique<AttributeModifier>("Blessing Buff", 99, EFFECT_TYPE::ATTRIBUTE_MODIFIER, logo, GENERIC_, value, attType, STACK, true, true);
	target->AddModifier(std::move(mod));
}

void AttributeBlessing::RemoveBuff(Character* target)
{
	/*
	This function is empty as Attribute Blessings last forever and all modifiers
	are wiped after battle
	*/
}

void TriggerBlessing::Apply(Character* target)
{
	//Register a listener for this blessing via the CombatEVentHandler
	CombatEventHandler::Instance().Register(triggerType, [this, target](const EventData& data)
		{
			//Ensure the right target triggers it
			if (data.target == target)
			{
				//Prevent spamming of this blessing
				if (cooldown <= 0)
				{
					triggerEffect(data);
					cooldown = blessingCooldown;
				}
			}
		});
}

void TriggerBlessing::RemoveBuff(Character* target)
{
	cooldown = 999;
	/*
	Note: There is no need to unregister the listener as the CombatEventHandler will
	unregister all listeners at the end of battle. Therefore, setting the cooldown to
	an arbitrary large number allows the blessing to be "deactivated" mid combat.
	*/
}

std::unique_ptr<Blessing> AttributeBlessing::Clone() const
{
	return std::make_unique<AttributeBlessing>(*this);
}

std::unique_ptr<Blessing> TriggerBlessing::Clone() const
{
	return std::make_unique<TriggerBlessing>(*this);
}

std::unordered_map<BLESSING_ID, std::unique_ptr<Blessing>> blessingDatabase;
void InitBlessingDatabase()
{
	blessingDatabase.clear();

	blessingDatabase.emplace(BLESSING_ID::MINOR_ATK_BUFF,
		std::make_unique<AttributeBlessing>(BLESSING_ID::MINOR_ATK_BUFF, "Minor ATK Boost", "ATK +15%", BLESSING_RARITY::COMMON, "", Game::ATK, 0.15f, "ATK_Minor_Texture"));

	blessingDatabase.emplace(BLESSING_ID::MINOR_DEF_BUFF,
		std::make_unique<AttributeBlessing>(BLESSING_ID::MINOR_DEF_BUFF, "Minor DEF Boost", "DEF +10%", BLESSING_RARITY::COMMON, "", Game::DEF, 0.10f, "DEF_Minor_Texture"));

	blessingDatabase.emplace(BLESSING_ID::MINOR_HP_BUFF,
		std::make_unique<AttributeBlessing>(BLESSING_ID::MINOR_HP_BUFF, "Minor HP Boost", "HP +25%", BLESSING_RARITY::COMMON, "", Game::HP, 0.25f, "HP_Minor_Texture"));

	blessingDatabase.emplace(BLESSING_ID::MINOR_CRITRATE_BUFF,
		std::make_unique<AttributeBlessing>(BLESSING_ID::MINOR_CRITRATE_BUFF, "CRIT Rate Boost", "CRIT Rate +10%", BLESSING_RARITY::COMMON, "", Game::CRIT_RATE, 0.10f, "CRITRATE_Minor_Texture"));

	blessingDatabase.emplace(BLESSING_ID::MINOR_CRITDMG_BUFF,
		std::make_unique<AttributeBlessing>(BLESSING_ID::MINOR_CRITDMG_BUFF, "CRIT DMG Boost", "CRIT DMG +20% ", BLESSING_RARITY::COMMON, "", Game::CRIT_DAMAGE, 0.20f, "CRITDMG_Minor_Texture"));

	blessingDatabase.emplace(BLESSING_ID::MAJOR_ATK_BUFF,
		std::make_unique<AttributeBlessing>(BLESSING_ID::MAJOR_ATK_BUFF, "Major ATK Boost", "ATK +50%", BLESSING_RARITY::LEGENDARY, "", Game::ATK, 0.50f, "ATK_Major_Texture"));

	blessingDatabase.emplace(BLESSING_ID::MAJOR_DEF_BUFF,
		std::make_unique<AttributeBlessing>(BLESSING_ID::MAJOR_DEF_BUFF, "Major DEF Boost", "DEF +25%", BLESSING_RARITY::LEGENDARY, "", Game::DEF, 0.25f, "DEF_Major_Texture"));

	blessingDatabase.emplace(BLESSING_ID::MAJOR_HP_BUFF,
		std::make_unique<AttributeBlessing>(BLESSING_ID::MAJOR_HP_BUFF, "Major HP Boost", "HP +75%", BLESSING_RARITY::LEGENDARY, "", Game::HP, 0.75f, "HP_Major_Texture"));

	blessingDatabase.emplace(BLESSING_ID::MAJOR_CRITRATE_BUFF,
		std::make_unique<AttributeBlessing>(BLESSING_ID::MAJOR_CRITRATE_BUFF, "Precision Strike", "CRIT RATE +25%", BLESSING_RARITY::LEGENDARY, "", Game::CRIT_RATE, 0.25f, "CRITRATE_Major_Texture"));

	blessingDatabase.emplace(BLESSING_ID::MAJOR_CRITDMG_BUFF,
		std::make_unique<AttributeBlessing>(BLESSING_ID::MAJOR_CRITDMG_BUFF, "Ferocity", "CRIT DMG +50%", BLESSING_RARITY::LEGENDARY, "", Game::CRIT_DAMAGE, 0.50f, "CRITDMG_Major_Texture"));

	blessingDatabase.emplace(BLESSING_ID::GAIN_ATK_ON_DAMAGE_TAKEN,
		std::make_unique<TriggerBlessing>(BLESSING_ID::GAIN_ATK_ON_DAMAGE_TAKEN, "Berserker", "Gain 10% ATK every time you take DMG.", BLESSING_RARITY::MYTHICAL,
			"", EventType::TookDamage,
			[](const EventData& data)
			{
				auto mod = std::make_unique<AttributeModifier>("Enraged", 999, EFFECT_TYPE::ATTRIBUTE_MODIFIER, "", GENERIC_, 0.25f,
					Game::ATK, STACK, true);
				data.target->AddModifier(std::move(mod));
			}, -1));

	blessingDatabase.emplace(BLESSING_ID::GAIN_CRIT_DMG_ON_CRIT_HIT,
		std::make_unique<TriggerBlessing>(BLESSING_ID::GAIN_CRIT_DMG_ON_CRIT_HIT, "Snowball", "Gain 20% CRIT DMG when landing a critical hit.", BLESSING_RARITY::MYTHICAL,
			"", EventType::DealtCriticalHit,
			[](const EventData& data)
			{
				auto mod = std::make_unique<AttributeModifier>("Snowball", 999, EFFECT_TYPE::ATTRIBUTE_MODIFIER, "", GENERIC_, 0.20f,
					Game::CRIT_DAMAGE, STACK, true);
				data.target->AddModifier(std::move(mod));
			}, -1));
}