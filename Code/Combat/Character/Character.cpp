#include "Character.hpp"
#include "../CombatUIManager.hpp"
#include <iostream>

void Character::DealDamage(Character* target, float coefficient)
{
	float critRoll = AERandFloat();
	bool isCrit = (critRoll < this->critRate);
	float finalDamage = (this->atk * coefficient) * (isCrit ? 1 + critDMG : 1) * (1 + this->dmgBonus);
	Game::DamageInfo info = Game::DamageInfo();
	info.damage = finalDamage;
	info.isCritical = isCrit;
	info.elementType = this->element;
	info.source = this;
	target->TakeDamage(info);
}

void Character::TakeDamage(Game::DamageInfo damageInfo)
{
	float defDMGReduction = def / (def + Game::DEF_CONSTANT);
	float finalDamageTaken = damageInfo.damage * (1 - defDMGReduction) * (1 - dmgReduction);
	hp -= finalDamageTaken;
	AEVec2 offset = { 0, 50 };
	CombatUIManager::instance->CreateDamageNumber(this->entity->transform->getPosition(), damageInfo);
	//if (damageInfo.isCritical)
	//{
	//	std::cout << "A critical hit!\n";
	//}
	//std::cout << name << " took " << finalDamageTaken << " damage from " << damageInfo.source->name << std::endl;
	if (hp <= 0)
	{
		Death();
	}
}

void Character::LoadCharacter(JSONSerializer& serializer, std::string fileName)
{
	rapidjson::Document doc = serializer.ReadDocument(fileName);
	if (doc.IsNull())
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
	this->moveList.insert(std::pair<MOVE_SLOT, MOVE_ID>(MOVE_SLOT_1, static_cast<MOVE_ID>(doc["moves"]["0"].GetInt())));
	this->moveList.insert(std::pair<MOVE_SLOT, MOVE_ID>(MOVE_SLOT_2, static_cast<MOVE_ID>(doc["moves"]["1"].GetInt())));
	this->moveList.insert(std::pair<MOVE_SLOT, MOVE_ID>(MOVE_SLOT_3, static_cast<MOVE_ID>(doc["moves"]["2"].GetInt())));
	this->moveList.insert(std::pair<MOVE_SLOT, MOVE_ID>(MOVE_SLOT_4, static_cast<MOVE_ID>(doc["moves"]["3"].GetInt())));

	std::cout << this->name << " = "
		<< this->element << " element, "
		<< this->baseMaxHP << " HP, "
		<< this->baseATK << " ATK, "
		<< this->baseDEF << " DEF, "
		<< this->faction << " faction"
		<< std::endl;
}

void Character::Init(void)
{
	//Load Blessings
	UpdateAttributes();
	hp = maxHP;
}

void Character::UseMove(MOVE_SLOT slot, Character* target)
{
	if (target == nullptr) //If no target is specified, assume self-cast
	{
		target = this;
	}

	auto move_id = moveList[slot]; //Find the move via slot
	Move* move = &Move::moveDatabase[move_id];
	if (move)
	{
		std::cout << name << " used " << move->name << " on " << target->name << std::endl;
		if (move->moveModifiers.size() > 0)
		{
			for (auto modifier_id : move->moveModifiers)
			{
				auto proto = modifierDatabase.find(modifier_id);
				if (proto != modifierDatabase.end())
				{
					auto modifier = proto->second->Clone();
					modifier->source = this;
					if (auto* status = dynamic_cast<StatusEffect*>(modifier.get())) //Check if it is a dot buff
					{
						status->damage = atk * move->dot_coefficient;
					}
					target->AddModifier(std::move(modifier));
				}
			}
		}
		DealDamage(target, move->coefficient);
		turnFinished = true;
	}
}

void Character::UpdateAttributes(void)
{
	atkBonus = defBonus = maxHPBonus = 0; //Reset stats first
	critRate = 0.05f; //5% Base Crit Rate
	critDMG = 0.5f; //50% Base Crit DMG
	for (auto& mod : effectList)
	{
		if (mod->effectType == ATTRIBUTE_MODIFIER)
		{
			mod->Apply(this);
		}
	}
	maxHP = baseMaxHP * (1 + maxHPBonus);
	atk = baseATK * (1 + atkBonus);
	def = baseDEF * (1 + defBonus);
}

void Character::AddModifier(std::unique_ptr<Modifier> modifier)
{
	auto modExists = std::find_if(
		effectList.begin(),
		effectList.end(),
		[&](const std::unique_ptr<Modifier>& m) { return m->ID == modifier->ID; }
	);

	if (modExists != effectList.end()) //Player already has an existing modifier
	{
		switch (modifier->stackBehaviour)
		{
			case (STACK_BEHAVIOUR::NO_STACK):
			{
				//Nothing happens, maybe print text to show player effect cannot stack?
				break;
			}
			case (STACK_BEHAVIOUR::REFRESH):
			{
				(*modExists)->duration = modifier->duration; //Refresh the duration
				break;
			}
			case (STACK_BEHAVIOUR::STACK):
			{
				(*modExists)->stackCount += modifier->stackCount; //Add extra stack count, maybe cap it?
				(*modExists)->duration = std::max(modifier->duration, (*modExists)->duration); //Pick longest duration
				break;
			}
			case (STACK_BEHAVIOUR::UNIQUE):
			{
				effectList.emplace_back(std::move(modifier)); //Add a whole separate modifier
				break;
			}
		}
	}
	else
	{
		std::cout << name << " gained modifier " << modifier->name << std::endl;
		effectList.emplace_back(std::move(modifier));
	}
	UpdateAttributes();
}

void Character::ProcessModifiers(void)
{
	for (auto& modifier : effectList)
	{
		if (modifier->effectType != ATTRIBUTE_MODIFIER)
		{
			modifier->Apply(this); //Apply DOT Effects
		}
		modifier->duration--; //Tick down all effects
	}

	effectList.erase(
		std::remove_if(effectList.begin(), effectList.end(),
			[](const std::unique_ptr<Modifier>& m) { return m->duration <= 0; }),
		effectList.end() //Remove all modifiers whose duration <= 0
	);

	//No need call UpdateAttributes as StartTurn does it.
}

void Character::StartTurn(void)
{
	ProcessModifiers();
	UpdateAttributes();
	turnFinished = false;
	std::cout << "It is " << name << "\'s turn\nHP: " << hp << " / " << maxHP << std::endl;
}

void Character::EndTurn(void)
{
	turnFinished = true;
}

void Character::Death(void)
{
	if (onDeath)
	{
		std::cout << name << " has died!\n";
		onDeath(this);
	}
}

void Character::ModifyAttribute(Game::ATTRIBUTE_TYPE type, float value)
{
	switch (type)
	{
	case Game::ATK:
		atkBonus += value;
		break;
	case Game::DEF:
		defBonus += value;
		break;
	case Game::HP:
		maxHPBonus += value;
		break;
	}
}

void Character::init()
{
	Init();
}

void Character::awake()
{

}

void Character::update()
{

}

void Character::fixedUpdate()
{

}

void Character::destroy()
{

}