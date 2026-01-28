#include "Modifier.hpp"
#include "../Character/Character.hpp"

#include <iostream>

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
    info.elementType = Game::NORMAL;
    info.source = source;
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
        modifierDatabase.emplace(static_cast<MODIFIER_ID>((*p)["id"].GetInt()),
            std::make_unique<StatusEffect>((*p)["name"].GetString(),
                (*p)["duration"].GetInt(),
                static_cast<EFFECT_TYPE>((*p)["type"].GetInt()),
                nullptr,
                static_cast<MODIFIER_ID>((*p)["id"].GetInt()),
                (*p)["damage"].GetFloat(),
                static_cast<STACK_BEHAVIOUR>((*p)["behaviour"].GetInt())));

        std::cout << "Modifier id = " << (*p)["id"].GetInt()
            << "\nname = " << (*p)["name"].GetString()
            << "\nduration = " << (*p)["duration"].GetInt()
            << "\neffect type = " << (*p)["type"].GetInt()
            << "\ndamage = " << (*p)["damage"].GetFloat()
            << "\nstack behaviour = " << (*p)["behaviour"].GetInt() << std::endl;
    }
    return true;
}