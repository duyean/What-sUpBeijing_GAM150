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

Blessing::Blessing() : id(BLESSING_ID::NONE), blessingName("name"), blessingDesc("desc"),
blessingType(BLESSING_TYPE::ATTRIBUTE_BOOST), blessingRarity(BLESSING_RARITY::COMMON), logo(nullptr) 
{
}

Blessing::Blessing(BLESSING_ID id, std::string name, std::string desc, BLESSING_TYPE type, BLESSING_RARITY rarity, AEGfxTexture* icon) : id(id), 
blessingName(name), blessingDesc(desc), blessingType(type), blessingRarity(rarity), logo(icon)
{
}

void AttributeBlessing::Apply(Character* target)
{
	//Create a new modifier based on the attribute type and add it to the player
	auto mod = std::make_unique<AttributeModifier>("Blessing Buff", 99, EFFECT_TYPE::ATTRIBUTE_MODIFIER, logo, GENERIC_, value, attType, UNIQUE, true);
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