#include "Modifier.hpp"
#include "../Character/Character.hpp"

#include <iostream>

Game::WUXING_ELEMENT StatusEffect::GetModifierElement() const
{
    switch (this->effectType)
    {
        case (EFFECT_TYPE::BURN):
        {
            return Game::WUXING_ELEMENT::FIRE;
        }
        case (EFFECT_TYPE::POISON):
        {
            return Game::WUXING_ELEMENT::WOOD;
        }
        default:
        {
            return Game::WUXING_ELEMENT::NORMAL;
        }
    }
}

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
    Game::DamageInfo info;
    info.damage = damage * stackCount;
    info.source = source;
    info.elementType = GetModifierElement();
    target->TakeDamage(info);
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

bool InitModifierDatabase(JSONSerializer& serializer, std::string fileName)
{
    rapidjson::Document doc = serializer.ReadDocument(fileName);
    if (doc.IsNull())
    {
        std::cout << "Unable to load modifier database as Document is nullptr" << std::endl;
        return false;
    }

    const rapidjson::Value& modifiers = doc["modifiers"];
    for (rapidjson::Value::ConstValueIterator p = modifiers.Begin(); p != modifiers.End(); ++p)
    {
        MODIFIER_ID id = static_cast<MODIFIER_ID>((*p)["id"].GetInt());
        std::string name = (*p)["name"].GetString();
        int duration = (*p)["duration"].GetInt();
        EFFECT_TYPE type = static_cast<EFFECT_TYPE>((*p)["type"].GetInt());
        STACK_BEHAVIOUR behaviour = static_cast<STACK_BEHAVIOUR>((*p)["behaviour"].GetInt());
        bool self = static_cast<bool>((*p)["self"].GetInt());

        if (type == EFFECT_TYPE::ATTRIBUTE_MODIFIER)
        {
            float value = (*p)["value"].GetFloat();
            Game::ATTRIBUTE_TYPE attType = static_cast<Game::ATTRIBUTE_TYPE>((*p)["attribute"].GetInt());
            modifierDatabase.emplace(id,
                std::make_unique<AttributeModifier>(name, duration, type, nullptr, id, value, attType, behaviour, self));
        }
        else
        {
            float damage = (*p)["damage"].GetFloat();
            modifierDatabase.emplace(id,
                std::make_unique<StatusEffect>(name, duration, type, nullptr, id, damage, behaviour, 1, self));
        }
    }
    return true;
}