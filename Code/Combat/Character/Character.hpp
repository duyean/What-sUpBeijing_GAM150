#include "AEEngine.h"
#include <vector>

class Character
{
private:
	//How much health the unit has
	float hp;

	//How much maximum health the unit has
	float maxHP;

	//The offensive power of the unit
	float atk;

	//The defensive power of the unit
	float def;

	//Determines the probability of critical hits and bonus damage dealt
	float critRate, critDMG;
	
	//Separate multiplier for outgoing damage
	float dmgBonus;
	//Storing the status effects of the unit
	//std::vector<StatusEffect> effectList;

	//A separate multipler for reducing damage
	float dmgReduction;

	//Determines turn order when combat begins
	int initiatve;

public:
	virtual void TakeDamage(float incomingDamage);
	virtual void DealDamage(Character* target, float coefficient);
};