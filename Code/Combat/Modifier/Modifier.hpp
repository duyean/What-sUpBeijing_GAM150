/*!
@file Modifier.hpp
@author Wayne Lion (lion.w)
@course CSD11451
@section B
@Final Project
@date 25/2/26
@brief
This file contains the functions for Modifiers in combat
*//*______________________________________________________________________*/

#pragma once
#include <string>
#include <memory>
#include "AEEngine.h"
#include <unordered_map>
#include "../Globals/Globals.hpp"
#include "../../BaseSystems/JSONSerializer/JSONSerializer.hpp"

class Character;

//Enum to store the type of modifier
enum EFFECT_TYPE
{
	ATTRIBUTE_MODIFIER,
	STUN,
	BURN,
	POISON,
};

//Enum to store the behaviour when applying same modifiers
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
	BLESSING_CRIT_DMG_BUFF = -2,
	BLESSING_ENRAGED_BUFF = -3,
	GENERIC_DMG_BOOST = 10,
	GENERIC_VULN = 11,
	//Custom Modifiers
};

/*!***********************************************************************
* \class Modifier
* \brief
* The class that handles Modifiers in combat
*************************************************************************/
class Modifier
{
public:
	//The name of the effect
	std::string name;

	//How long the effect lasts in turns
	int duration;

	//What type of modifier is it
	EFFECT_TYPE effectType;

	//A description of the modifier that is shown in tooltips
	std::string description;

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

	//Default constructor
	inline Modifier() :name("Modifier"), description(""), effectType(ATTRIBUTE_MODIFIER), icon(""), ID(NONE), duration(3), stackBehaviour(REFRESH), stackCount(1), source(nullptr), selfCast(false), hidden(false) {};
	
	//Customised constructor
	inline Modifier(std::string name, int duration, EFFECT_TYPE type, std::string desc, std::string icon, MODIFIER_ID id, STACK_BEHAVIOUR stackBeh, int stackCount = 1, bool selfCast = false, bool hide = false) :
		name(name), duration(duration), effectType(type), description(desc), icon(icon), ID(id), stackBehaviour(stackBeh), stackCount(stackCount), source(nullptr), selfCast(selfCast), hidden(hide) {
	};

	//Virtual destructor
	virtual ~Modifier() = default;

	/*!***********************************************************************
	* \brief
	* Pure virtual function to apply the modifier effects to the Character
	* \param[in] target
	* The target to apply the modifier to
	*************************************************************************/
	virtual void Apply(Character* target) = 0;

	/*!***********************************************************************
	* \brief
	* Prototype Pattern: Clone a blessing from the database
	* \return
	* A copied modifier from the database
	*************************************************************************/
	virtual std::unique_ptr<Modifier> Clone() const = 0;
};

/*!***********************************************************************
* \class AttributeModifier
* \brief
* A derived modifier class that only modifies Character attributes
*************************************************************************/
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

	//Overriden method to clone AttributeModifier from the database
	std::unique_ptr<Modifier> Clone() const override;

	//Default constructor
	inline AttributeModifier() : Modifier("Name", 3, ATTRIBUTE_MODIFIER, "", "", GENERIC_, REFRESH), value(0.0f), attributeType(Game::ATK) {};

	//Customised constructor
	inline AttributeModifier(std::string name, int duration, EFFECT_TYPE type, std::string desc, std::string icon, MODIFIER_ID id, float value, Game::ATTRIBUTE_TYPE attType, STACK_BEHAVIOUR b, bool self, bool hide = false) :
		Modifier(name, duration, type, desc, icon, id, b, 1, self, hide), value(value), attributeType(attType) {
	};
};

/*!***********************************************************************
* \class StatusEffect
* \brief
* A derived modifier class that handles damage over time effects
*************************************************************************/
class StatusEffect : public Modifier
{
public:
	//The damage to deal at the start of turn. Scales with stackCount.
	float damage;

	//Override function to apply the effect
	void Apply(Character* target) override;

	/*!***********************************************************************
	* \brief
	* Gets the modifier element of the damage over time effect
	* \return
	* The element of the modifier dot effect
	*************************************************************************/
	Game::WUXING_ELEMENT GetModifierElement() const;

	//Override for Clone method from Modifier
	std::unique_ptr<Modifier> Clone() const override;

	//Default constructor
	inline StatusEffect() : Modifier("Name", 3, ATTRIBUTE_MODIFIER, "", "", GENERIC_, STACK), damage(0.0f) {};

	//Customised constructor
	inline StatusEffect(std::string name, int duration, EFFECT_TYPE type, std::string desc, std::string icon, MODIFIER_ID id, float damage, STACK_BEHAVIOUR be, int stackCount = 1, bool self = false, bool hide = false) :
		Modifier(name, duration, type, desc, icon, id, be, stackCount, self, hide), damage(damage) {
	};
};

//The modifier database to store generic versions of modifiers
extern std::unordered_map<MODIFIER_ID, std::unique_ptr<Modifier>> modifierDatabase;

/*!***********************************************************************
* \brief
* Initialise the Modifier database from JSON
* \param[in] serializer
* A reference to the JSON serializer
* \param fileName
* The name of the JSON Modifier File
* \return
* A boolean that determines if the operation was successful
*************************************************************************/
extern bool InitModifierDatabase(JSONSerializer& serializer, std::string fileName);