#include "Modifier.hpp"
#include "../Character/Character.hpp"

void AttributeModifier::Apply(Character* target)
{
    if (!target)
    {
        return;
    }
    target->ModifyAttribute(attributeType, value * stackCount);
}

void StatusEffect::Apply(Character* target)
{
    if (!target)
    {
        return;
    }
    target->TakeDamage(damage * stackCount);
}

Game::ATTRIBUTE_TYPE AttributeModifier::GetAttributeType(void) const
{
    return attributeType;
}

std::unique_ptr<Modifier> StatusEffect::Clone() const
{
    return std::make_unique<StatusEffect>(*this);
}

std::unique_ptr<Modifier> AttributeModifier::Clone() const
{
    return std::make_unique<AttributeModifier>(*this);
}

std::unordered_map<MODIFIER_ID, std::unique_ptr<Modifier>> modifierDatabase;

void InitModifierDatabase()
{
    modifierDatabase.emplace(
        GENERIC_DOT_BURN,
        std::make_unique<StatusEffect>("Burn", 3, BURN, nullptr, GENERIC_DOT_BURN, 0.0f, STACK)
    );

    modifierDatabase.emplace(
        GENERIC_DOT_POISON,
        std::make_unique<StatusEffect>("Poison", 3, POISON, nullptr, GENERIC_DOT_POISON, 0.0f, STACK)
    );
}