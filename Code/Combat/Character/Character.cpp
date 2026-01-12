#include "Character.hpp"

void Character::DealDamage(Character* target, float coefficient)
{
	float critRoll = AERandFloat();
	float finalDamage = (this->atk * coefficient) * ((critRoll < this->critRate) ? 1 + critDMG : 1) * (1 + this->dmgBonus);
	target->TakeDamage(finalDamage);
}

void Character::TakeDamage(float incomingDamage)
{
	float defDMGReduction = def / (def + Game::DEF_CONSTANT);
	float finalDamageTaken = incomingDamage * (1 - defDMGReduction) * (1 - dmgReduction);
	hp -= finalDamageTaken;
	//Check death here or something
}

void Character::UpdateAttributes(void)
{
	maxHP = baseMaxHP * (1 + maxHPBonus);
	atk = baseATK * (1 + atkBonus);
	def = baseDEF * (1 + defBonus);
}