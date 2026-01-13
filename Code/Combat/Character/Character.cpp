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
	if (hp <= 0)
	{
		Death();
	}
}

void Character::UpdateAttributes(void)
{
	maxHP = baseMaxHP * (1 + maxHPBonus);
	atk = baseATK * (1 + atkBonus);
	def = baseDEF * (1 + defBonus);
}

void Character::ProcessModifiers(void)
{
	for (Game::Modifier& modifier : effectList)
	{
		switch (modifier.effectType)
		{
			case (Game::EFFECT_TYPE::BURN):
			case (Game::EFFECT_TYPE::POISON):
			case (Game::EFFECT_TYPE::STUN):
			{
				if (Game::StatusEffect* effect = dynamic_cast<Game::StatusEffect*>(&modifier))
				{
					TakeDamage(effect->damage);
				}
				break;
			}
		}
		modifier.duration--;
	}

	effectList.erase(std::remove_if(effectList.begin(), effectList.end(), [](const Game::Modifier& m) { return m.duration <= 0;}), effectList.end());

}

void Character::StartTurn(void)
{
	UpdateAttributes();
	ProcessModifiers();
	turnFinished = false;
}

void Character::EndTurn(void)
{
	turnFinished = true;
}

void Character::Death(void)
{
	if (onDeath)
	{
		onDeath(this);
	}
}