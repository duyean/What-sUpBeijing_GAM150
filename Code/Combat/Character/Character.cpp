#include "Character.hpp"
#include "../CombatUIManager.hpp"
#include <iostream>
#include "../EventHandler/CombatEventHandler.hpp"
#include "../Code/SoloBehavior/RunManager.hpp"
#include "../Code/BaseSystems/Engine/MeshGen.hpp"

void Character::DealDamage(Character* target, float coefficient)
{
	if (coefficient <= 0) //If coefficient is 0, the move doesn't do any damage
	{
		return;
	}

	std::uniform_real_distribution<> randFloat(0.0f, 1.0f);
	float critRoll = randFloat(Game::gen);
	bool isCrit = (critRoll < this->critRate);
	float finalDamage = (this->atk * coefficient) * (isCrit ? 1 + critDMG : 1) * (1 + this->dmgBonus);
	Game::DamageInfo info = Game::DamageInfo();
	info.damage = finalDamage;
	info.isCritical = isCrit;
	info.elementType = this->element;
	info.source = this;

	EventData evt{ info.source, this, (int)finalDamage };
	CombatEventHandler::Instance().Dispatch(EventType::DealtDamage, evt);

	if (isCrit)
	{
		CombatEventHandler::Instance().Dispatch(EventType::DealtCriticalHit, evt);
	}

	target->TakeDamage(info);
}

void Character::TakeDamage(Game::DamageInfo& damageInfo)
{
	float defDMGReduction = def / (def + Game::DEF_CONSTANT);
	float finalDamageTaken = damageInfo.damage * (1 - defDMGReduction) * (1 - dmgReduction);
	damageInfo.damage = finalDamageTaken;
	hp -= finalDamageTaken;
	hp = AEClamp(hp, 0, maxHP);
	AEVec2 offset = { AERandFloat() * 20 - 10, 50};
	CombatUIManager::Instance().CreateDamageNumber(this->entity->transform->getPosition() + offset, damageInfo);

	//Event Handler
	EventData evt{ damageInfo.source, this, (int)finalDamageTaken};
	CombatEventHandler::Instance().Dispatch(EventType::TookDamage, evt);

	if (hp <= 0)
	{
		Death();
	}
}

bool Character::LoadCharacter(JSONSerializer& serializer, std::string fileName)
{
	rapidjson::Document doc = serializer.ReadDocument(fileName);
	if (doc.IsNull())
	{
		std::cout << "Unable to load a character as Document is nullptr" << std::endl;
		return false;
	}

	this->name = doc["name"].GetString(); // name
	this->element = static_cast<Game::WUXING_ELEMENT>(doc["element"].GetInt()); // element
	this->baseMaxHP = doc["baseHP"].GetFloat(); // base hp
	this->baseATK = doc["baseATK"].GetFloat(); // base attack
	this->baseDEF = doc["baseDEF"].GetFloat(); // base defense
	this->faction = static_cast<Game::FACTION>(doc["faction"].GetInt()); // faction
	this->initiative = doc["initiative"].GetInt();
	this->characterModelTexture = doc["texture"].GetString();
	this->characterModelTexture2 = doc["texture2"].GetString();
	this->characterIconTexture = doc["icontexture"].GetString();
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

	return true;
}

void Character::Init(void)
{
	meshSystem = &MeshGen::getInstance();
	printf("Init: %s\n", name.c_str());
	//Load Blessings
	if (faction == Game::PLAYER)
	{
		for (auto& blessing : RunManager::Instance().GetBlessings())
		{
			blessing.get()->Apply(this);
		}
	}
	//Scale enemy difficulty
	else
	{
		baseMaxHP *= 1 + 1 * RunManager::Instance().GetEnemyDifficulty();
		baseATK *= 1 + 0.35 * RunManager::Instance().GetEnemyDifficulty();
		baseDEF *= 1 + 0.2 * RunManager::Instance().GetEnemyDifficulty();
	}
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
		if (faction == Game::PLAYER)
		{
			entity->getComponent<Mesh>()->pTex = meshSystem->getTexture(characterModelTexture2.c_str());
		}
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
					if (modifier->selfCast)
					{
						AddModifier(std::move(modifier));
					}
					else
					{
						target->AddModifier(std::move(modifier));
					}
				}
			}
		}
		AEVec2 pos{ 0.0, AEGfxGetWindowHeight() * 0.25 };
		CombatUIManager::Instance().CreateMessageText(pos, move->name, (faction == Game::FACTION::PLAYER) ? Color(0, 255, 0, 1) : Color(255, 0, 0, 1));
		DealDamage(target, move->coefficient);
		EndTurn();
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
	bool renderText = !modifier->hidden;
	std::string modifierName = modifier->name;
	AEVec2 offset = { 0, -150 };
	auto modExists = std::find_if(
		effectList.begin(),
		effectList.end(),
		[&](const std::unique_ptr<Modifier>& m) { return m->ID == modifier->ID && m->hidden == modifier->hidden; }
	);

	if (modExists != effectList.end()) //Player already has an existing modifier
	{
		switch (modifier->stackBehaviour)
		{
			case (STACK_BEHAVIOUR::NO_STACK):
			{
				//Nothing happens, maybe print text to show player effect cannot stack?
				renderText = false;
				break;
			}
			case (STACK_BEHAVIOUR::REFRESH):
			{
				(*modExists)->duration = modifier->duration; //Refresh the duration
				break;
			}
			case (STACK_BEHAVIOUR::STACK):
			{
				(*modExists)->stackCount += modifier->stackCount;
				(*modExists)->stackCount = std::min((*modExists)->stackCount, 5);
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

		effectList.emplace_back(std::move(modifier));
	}

	if (renderText)
	{
		CombatUIManager::Instance().CreateMessageText(this->entity->transform->getPosition() + offset, modifierName);
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

		if (isDead)
		{
			break;
		}

		if (modifier)
		{
			modifier->duration--; //Tick down all effectsq
		}
	}

	effectList.erase(
		std::remove_if(effectList.begin(), effectList.end(),
			[](const std::unique_ptr<Modifier>& m) { return m->duration <= 0; }),
		effectList.end() //Remove all modifiers whose duration <= 0
	);

	//No need call UpdateAttributes as StartTurn does it.
}

std::vector<std::unique_ptr<Modifier>> const& Character::GetModifierList() const
{
	return effectList;
}

void Character::StartTurn(void)
{
	ProcessModifiers();
	if (isDead)
	{
		turnFinished = true;
		endingTurn = true;
		return;
	}
	UpdateAttributes();
	turnFinished = false;
	endingTurn = false;
	if (faction == Game::PLAYER)
	{
		entity->getComponent<Mesh>()->isActive = true;
		entity->getComponent<Mesh>()->pTex = meshSystem->getTexture(characterModelTexture.c_str());
	}
	std::cout << "It is " << name << "\'s turn\nHP: " << hp << " / " << maxHP << std::endl;
}

void Character::AIAttack()
{
	if (isDead)
	{
		return;
	}
	std::uniform_int_distribution<> randMove(MOVE_SLOT_1, MOVE_SLOT_4);
	MOVE_SLOT slotSelected = static_cast<MOVE_SLOT>(randMove(Game::gen));
	auto& moveToUse = moveList[slotSelected];
	Move* move = &Move::moveDatabase[moveToUse];
	if (move->targetGroup == Game::MOVE_TARGET_GROUP::OPPOSITE)
	{
		if (!targets.empty())
		{
			std::uniform_int_distribution<> randTarget(0, targets.size() - 1);
			Character* target = targets[randTarget(Game::gen)];
			target->entity->getComponent<Mesh>()->isActive = true;
			target->timer = 2.0f;
			UseMove(slotSelected, target);
		}
	}
	else
	{
		UseMove(slotSelected, this);
	}
}

void Character::EndTurn(void)
{
	endingTurn = true;
	timer = 2.0f;
}

void Character::Death(void)
{
	if (onDeath)
	{
		effectList.clear();
		std::cout << name << " has died!\n";
		isDead = true;
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
	/*
	This is a temp fix for when the a TookDamage event triggers that resulted in adding a modifier, which causes
	a vector reallocation mid loop in ProcessModifiers.
	*/
	effectList.reserve(128);
}

void Character::awake()
{

} 

void Character::update()
{
	if (endingTurn)
	{
		if (timer > 0.f)
		{
			entity->getComponent<Mesh>()->pTex = meshSystem->getTexture(characterModelTexture2.c_str());
			timer -= 1.0f * AEFrameRateControllerGetFrameTime();
		}

		if (timer <= 0.5f)
		{
			entity->getComponent<Mesh>()->pTex = meshSystem->getTexture(characterModelTexture.c_str());

			if (timer <= 0)
			{
				if (faction == Game::PLAYER)
				{
					entity->getComponent<Mesh>()->isActive = false;
				}
				turnFinished = true;
			}
		}
	}
}

void Character::fixedUpdate()
{

}

void Character::destroy()
{

}