#include "Character.hpp"

void Character::DealDamage(Character* target, float coefficient)
{
	float critRoll = AERandFloat();
	float finalDamage = (this->atk * coefficient) * ((critRoll < this->critRate) ? 1 + critDMG : 1) * (1 + this->dmgBonus);
	target->TakeDamage(finalDamage);
}

void Character::TakeDamage(float incomingDamage)
{

}