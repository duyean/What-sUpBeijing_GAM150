#pragma once
#include <string>
#include <memory>
#include "AEEngine.h"
#include <unordered_map>
#include "../Globals/Globals.hpp"
#include "../../BaseSystems/JSONSerializer/JSONSerializer.hpp"

class Character;

enum EFFECT_TYPE
{
	ATTRIBUTE_MODIFIER,
	STUN,
	BURN,
	POISON,
};

enum STACK_BEHAVIOUR
{
	NO_STACK, //The incoming modifier is ignored
	REFRESH, //The existing modifier's duration is set to the new modifier
	STACK, //The existing modifier's stack count is incremented and duration is refreshed
	UNIQUE //Adds the new modifier, ignoring the existing one
};

//This enum will be used for handling same buff situations and used to query from the effect database.
enum MODIFIER_ID
{
	GENERIC_ = -1,
	NONE = 0,
	GENERIC_DOT_BURN = 1,
	GENERIC_DOT_POISON = 2,
	GENERIC_EMPOWER_BUFF = 3,
	GENERIC_EXPOSED_DEBUFF = 4,
	CHAR1_COMBUST_BUFF = 5,
	SUPERHEAT_DOT = 6,
	GENERIC_WEAKEN_DEBUFF = 7,
	BLESSING_CRIT_DMG_BUFF = 8,
	BLESSING_ENRAGED_BUFF = 9
	//Custom Modifiers
};

class Modifier
{
public:
	//The name of the effect
	std::string name;

	//How long the effect lasts in turns
	int duration;

	//What type of modifier is it
	EFFECT_TYPE effectType;

	//An UI icon for the effect
	std::string icon;

	//The ID of the modifier to handle stacking
	MODIFIER_ID ID;

	//How do handle same effect
	STACK_BEHAVIOUR stackBehaviour;

	//Who applied the effect
	Character* source;

	//Will this modifier be applied on the source or the target
	bool selfCast;

	//How many stacks this effect have
	int stackCount;

	//Whether to show this modifier when it is added
	bool hidden;

	inline Modifier() :name("Modifier"), effectType(ATTRIBUTE_MODIFIER), icon(""), ID(NONE), duration(3), stackBehaviour(REFRESH), stackCount(1), source(nullptr), selfCast(false), hidden(false) {};
	inline Modifier(std::string name, int duration, EFFECT_TYPE type, std::string icon, MODIFIER_ID id, STACK_BEHAVIOUR stackBeh, int stackCount = 1, bool selfCast = false, bool hide = false) :
		name(name), duration(duration), effectType(type), icon(icon), ID(id), stackBehaviour(stackBeh), stackCount(stackCount), source(nullptr), selfCast(selfCast), hidden(hide) {
	};
	virtual ~Modifier() = default;
	virtual void Apply(Character* target) {};
	virtual std::unique_ptr<Modifier> Clone() const = 0;
};

class AttributeModifier : public Modifier
{
public:
	//The percentage to modify the attribute by. 0.2 means 20%
	float value;

	//The attribute to modify
	Game::ATTRIBUTE_TYPE attributeType;

	//Overriden method from Modifier class
	void Apply(Character* target) override;

	//Getter
	Game::ATTRIBUTE_TYPE GetAttributeType(void) const;
	std::unique_ptr<Modifier> Clone() const override;
	inline AttributeModifier() : Modifier("Name", 3, ATTRIBUTE_MODIFIER, "", GENERIC_, REFRESH), value(0.0f), attributeType(Game::ATK) {};
	inline AttributeModifier(std::string name, int duration, EFFECT_TYPE type, std::string icon, MODIFIER_ID id, float value, Game::ATTRIBUTE_TYPE attType, STACK_BEHAVIOUR b, bool self, bool hide = false) :
		Modifier(name, duration, type, icon, id, b, 1, self, hide), value(value), attributeType(attType) {
	};
};

class StatusEffect : public Modifier
{
public:
	//The damage to deal at the start of turn. Scales with stackCount.
	float damage;

	void Apply(Character* target) override;
	Game::WUXING_ELEMENT GetModifierElement() const;
	std::unique_ptr<Modifier> Clone() const override;
	inline StatusEffect() : Modifier("Name", 3, ATTRIBUTE_MODIFIER, "", GENERIC_, STACK), damage(0.0f) {};
	inline StatusEffect(std::string name, int duration, EFFECT_TYPE type, std::string icon, MODIFIER_ID id, float damage, STACK_BEHAVIOUR be, int stackCount = 1, bool self = false, bool hide = false) :
		Modifier(name, duration, type, icon, id, be, stackCount, self, hide), damage(damage) {
	};
};

//The modifier database to store generic versions of modifiers
extern std::unordered_map<MODIFIER_ID, std::unique_ptr<Modifier>> modifierDatabase;
extern bool InitModifierDatabase(JSONSerializer& serializer, std::string fileName);