#pragma once
#include <string>

class Character;

enum BLESSING_ID
{
	MINOR_ATK_BUFF,
	MINOR_DEF_BUFF,
	MINOR_HP_BUFF
};

enum BLESSING_TYPE
{
	ATTRIBUTE_BOOST,
	TRIGGERED_BLESSING
};

enum BLESSING_RARITY
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

	virtual void Apply(Character* target) {};
	virtual void RemoveBuff(Character* target) {};
	virtual ~Blessing() = default;
};

class AttributeBlessing : public Blessing
{

};

class TriggerBlessing : public Blessing
{

};