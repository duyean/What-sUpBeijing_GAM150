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
	auto mod = std::make_unique<AttributeModifier>("blessing", 99, EFFECT_TYPE::ATTRIBUTE_MODIFIER, logo, GENERIC_, value, attType, UNIQUE, true);
	target->AddModifier(std::move(mod));
	std::cout << "Added Blessing: " << blessingName << std::endl;
}

void AttributeBlessing::RemoveBuff(Character* target) {}

void TriggerBlessing::Apply(Character* target)
{
	CombatEventHandler::Instance().Register(triggerType, [this, target](const EventData& data)
		{
			if (data.target == target)
			{
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
}