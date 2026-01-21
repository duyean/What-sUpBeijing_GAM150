#include "Character.hpp"
#include <iostream>

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
	if (hp <= 0)
	{
		Death();
	}
}

void Character::LoadCharacter(JSONSerializer &serializer, const char *fileName)
{
	rapidjson::Document doc = serializer.ReadDocument(fileName);
	if (doc == nullptr)
	{
		std::cout << "Unable to load a character as Document is nullptr" << std::endl;
		return;
	}

	this->name = doc["name"].GetString(); // name
	this->element = static_cast<Game::WUXING_ELEMENT>(doc["element"].GetInt()); // element
	this->baseMaxHP = doc["baseHP"].GetFloat(); // base hp
	this->baseATK = doc["baseATK"].GetFloat(); // base attack
	this->baseDEF = doc["baseDEF"].GetFloat(); // base defense
	this->faction = static_cast<Game::FACTION>(doc["faction"].GetInt()); // faction
	// move list
	// this->moveList.insert(MOVE_SLOT_1, );

	std::cout << this->name << " = " 
		<< this->element << " element, "
		<< this->baseMaxHP << " HP, " 
		<< this->baseATK << " ATK, " 
		<< this->baseDEF << " DEF, "
		<< this->faction << " faction"
		<< std::endl;
}

void Character::UseMove(MOVE_SLOT slot, Character* target)
{
	if (target == nullptr) //If no target is specified, assume self-cast
	{
		target = this;
	}

	auto it = moveList.find(slot); //Find the move via slot
	if (it != moveList.end())
	{
		DealDamage(target, it->second.coefficient);
		if (it->second.moveModifiers.size() > 0)
		{
			for (Game::Modifier& mod : it->second.moveModifiers)//If adding debuff chance, can edit here
			{
				target->AddModifier(mod);
			}
		}
	}
}

void Character::UpdateAttributes(void)
{
	atkBonus = defBonus = maxHPBonus = 0;
	critRate = 0.05f; //5% Base Crit Rate
	critDMG = 0.5f; //50% Base Crit DMG
	for (Game::Modifier& mod : effectList)
	{
		if (mod.effectType == Game::ATTRIBUTE_MODIFIER)
		{
			Game::AttributeModifier* attribute = dynamic_cast<Game::AttributeModifier*>(&mod);
			if (attribute != nullptr)
			{
				switch (attribute->attributeType) //All are additive
				{
					case (Game::ATK):
					{
						atkBonus += attribute->value;
						break;
					}
					case (Game::DEF):
					{
						defBonus += attribute->value;
						break;
					}
					case (Game::HP):
					{
						maxHPBonus += attribute->value;
						break;
					}
				}
			}
		}
	}
	maxHP = baseMaxHP * (1 + maxHPBonus);
	atk = baseATK * (1 + atkBonus);
	def = baseDEF * (1 + defBonus);
}

void Character::AddModifier(Game::Modifier modifier)
{
	auto modExists = std::find_if(effectList.begin(), effectList.end(), [modifier](const Game::Modifier& m) {return m.ID == modifier.ID;});
	if (modExists != effectList.end()) //Player already has an existing modifier
	{
		modExists->duration = modifier.duration;
	}
	else
	{
		effectList.emplace_back(modifier);
	}
	UpdateAttributes();
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
	ProcessModifiers();
	UpdateAttributes();
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