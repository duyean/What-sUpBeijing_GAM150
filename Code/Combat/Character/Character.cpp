#include "Character.hpp"
#include "../CombatUIManager.hpp"
#include <iostream>
#include "../EventHandler/CombatEventHandler.hpp"
#include "../Code/SoloBehavior/RunManager.hpp"
#include "../Code/BaseSystems/Engine/MeshGen.hpp"
#include "../Code/Audio_WZBJ_Pak.hpp"
#include "../../BaseSystems/Engine/Tinter.hpp"
#include "../../BaseSystems/Engine/CameraVFX.hpp"
#include "../../SoloBehavior/JumpToPoint.hpp"
Character::Character() : meshSystem(nullptr), endingTurn(false), name(""), element(Game::WUXING_ELEMENT::FIRE),
hp(0), baseMaxHP(0), maxHPBonus(0), maxHP(0), enemyLevel(0),
baseATK(0), atkBonus(0), atk(0),
baseDEF(0), defBonus(0), def(0),
critRate(0), critDMG(0), dmgBonus(0),
effectList(), dmgReduction(0), initiative(0),
turnFinished(false), isDead(false), faction(Game::NONE),
moveList(), targets(), characterIconTexture(""),
characterModelTexture(""), characterModelTexture2(""), onDeath(nullptr)
{ };

void Character::DealDamage(Character* target, float coefficient)
{
	if (coefficient <= 0) //If coefficient is 0, the move doesn't do any damage
	{
		return;
	}

	std::uniform_real_distribution<float> randFloat(0.0f, 1.0f);
	float critRoll = randFloat(Game::gen);
	bool isCrit = (critRoll < this->critRate);
	float finalDamage = (this->atk * coefficient) * (isCrit ? 1 + critDMG : 1) * (1 + this->dmgBonus);
	Game::DamageInfo info = Game::DamageInfo();
	info.damage = finalDamage;
	info.isCritical = isCrit;
	info.elementType = this->element;
	info.source = this;

	EventData evt{ info.source, this, finalDamage };
	CombatEventHandler::Instance().Dispatch(EventType::DealtDamage, evt);

	if (isCrit)
	{
		CombatEventHandler::Instance().Dispatch(EventType::DealtCriticalHit, evt);
		EntityManager::getInstance().rootEntity->getComponent<CameraVFX>()->TriggerShake();
	}

	target->TakeDamage(info);
}

void Character::TakeDamage(Game::DamageInfo& damageInfo)
{
	float defDMGReduction = def / (def + Game::DEF_CONSTANT);
	float finalDamageTaken = damageInfo.damage * (1 - defDMGReduction) * (1 / (dmgReduction + 1));
	damageInfo.damage = finalDamageTaken;
	hp -= finalDamageTaken;
	hp = AEClamp(hp, 0, maxHP);
	AEVec2 offset = { AERandFloat() * 20 - 10, entity->transform->getScale().y * 0.5f};
	CombatUIManager::Instance().CreateDamageNumber(this->entity->transform->getPosition() + offset, damageInfo);

	//Event Handler
	EventData evt{ damageInfo.source, this, finalDamageTaken};
	CombatEventHandler::Instance().Dispatch(EventType::TookDamage, evt);
	entity->getComponent<Tinter>()->Trigger();
	if (hp <= 0)
	{
		Death();
		AudioManager::GetInstance()->PlaySFX(AudioManager::SFX_BATTLE_DEATH);
		return;
	}
	std::uniform_int_distribution<int> trackRand(0, 1);
	int trackNo = trackRand(Game::gen);
	if (trackNo)
		AudioManager::GetInstance()->PlaySFX(AudioManager::SFX_BATTLE_HURT);
	else
		AudioManager::GetInstance()->PlaySFX(AudioManager::SFX_BATTLE_HURT2);
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
	this->moveList.insert(std::pair<MOVE_SLOT, MOVE_ID>(MOVE_SLOT::MOVE_SLOT_1, static_cast<MOVE_ID>(doc["moves"]["0"].GetInt())));
	this->moveList.insert(std::pair<MOVE_SLOT, MOVE_ID>(MOVE_SLOT::MOVE_SLOT_2, static_cast<MOVE_ID>(doc["moves"]["1"].GetInt())));
	this->moveList.insert(std::pair<MOVE_SLOT, MOVE_ID>(MOVE_SLOT::MOVE_SLOT_3, static_cast<MOVE_ID>(doc["moves"]["2"].GetInt())));
	this->moveList.insert(std::pair<MOVE_SLOT, MOVE_ID>(MOVE_SLOT::MOVE_SLOT_4, static_cast<MOVE_ID>(doc["moves"]["3"].GetInt())));

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
		int partyLevel = RunManager::Instance().GetPartyLevel();
		baseMaxHP *= 1 + 0.25f * (partyLevel - 1);
		baseATK *= 1 + 0.05f * (partyLevel - 1);
		baseDEF *= 1 + 0.06f * (partyLevel - 1);
		for (auto& blessing : RunManager::Instance().GetBlessings())
		{
			blessing.get()->Apply(this);
		}
	}
	//Scale enemy difficulty
	else
	{
		std::uniform_int_distribution<int> dist(0, 3);
		enemyLevel = RunManager::Instance().GetEnemyDifficulty() + dist(Game::gen);
		enemyLevel = std::max(0, enemyLevel);
		baseMaxHP *= static_cast<float>(std::pow(1.25f, enemyLevel));
		baseATK *= 1 + 0.25f * enemyLevel;
		baseDEF *= 1 + 0.10f * enemyLevel;
	}
	UpdateAttributes();
	hp = maxHP;
}

void Character::UseMove(MOVE_SLOT slot, std::vector<Character*> targets_list)
{
	bool renderMove = true;
	for (auto ch : targets_list)
	{
		UseMove(slot, ch, renderMove);
		renderMove = false;
	}
}

void Character::UseMove(MOVE_SLOT slot, Character* target, bool renderMoveName)
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

		if (renderMoveName)
		{
			AEVec2 pos{ 0, (f32)(AEGfxGetWindowHeight() * 0.25) };
			CombatUIManager::Instance().CreateMessageText(pos, move->name, (faction == Game::FACTION::PLAYER) ? Color(0, 255, 0, 1) : Color(255, 0, 0, 1));
		}
		DealDamage(target, move->coefficient);
		
		spriteState = SPRITE_STATE::ATTACKING;
		spriteTimer = 2.0f;
		EndTurn();

		switch (static_cast<int>(move_id))
		{
		case 0:
			AudioManager::GetInstance()->PlaySFX(AudioManager::SFX_ATTACK_BASIC);
			break;
		case 1:
			AudioManager::GetInstance()->PlaySFX(AudioManager::SFX_ATTACK_SCORCH);
			break;
		case 2:
			AudioManager::GetInstance()->PlaySFX(AudioManager::SFX_ATTACK_EMPOWER);
			break;
		case 3:
			AudioManager::GetInstance()->PlaySFX(AudioManager::SFX_ATTACK_APS);
			break;
		case 4:
			AudioManager::GetInstance()->PlaySFX(AudioManager::SFX_ATTACK_FLAMESTRIKE);
			break;
		case 5:
			AudioManager::GetInstance()->PlaySFX(AudioManager::SFX_ATTACK_COMBUST);
			break;
		case 6:
			AudioManager::GetInstance()->PlaySFX(AudioManager::SFX_ATTACK_CATACLYSM);
			break;
		case 7:
			AudioManager::GetInstance()->PlaySFX(AudioManager::SFX_ATTACK_WATERSURGE);
			break;
		case 8:
			AudioManager::GetInstance()->PlaySFX(AudioManager::SFX_ATTACK_HYDRORUSH);
			break;
		case 9:
			AudioManager::GetInstance()->PlaySFX(AudioManager::SFX_ATTACK_TIDALWAVE);
			break;
		}
	}
}

void Character::UpdateAttributes(void)
{
	atkBonus = defBonus = maxHPBonus = 0; //Reset stats first
	critRate = 0.05f; //5% Base Crit Rate
	critDMG = 0.5f; //50% Base Crit DMG
	dmgBonus = 0;
	dmgReduction = 0;
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
	dmgReduction = std::max(-0.90f, dmgReduction);
}

void Character::AddModifier(std::unique_ptr<Modifier> modifier)
{
	bool renderText = !modifier->hidden;
	std::string modifierName = modifier->name;
	AEVec2 offset = { 0, entity->transform->getScale().y * -0.25f};
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
				(*modExists)->stackCount = std::min((*modExists)->stackCount, 15);
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
		CombatUIManager::Instance().CreateMessageText(this->entity->transform->getPosition() + offset, modifierName, Color(255, 255, 255, 1.0f), 0.75f);
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
		//reset position
		entity->transform->setPosition(AEVec2(-500.f, -150.f));
		spriteTimer = 999;
		spriteState = SPRITE_STATE::IDLE;
	}
	std::cout << "It is " << name << "\'s turn\nHP: " << hp << " / " << maxHP << std::endl;
}

void Character::AIAttack()
{
	if (isDead)
	{
		return;
	}
	std::uniform_int_distribution<int> randMove(static_cast<int>(MOVE_SLOT::MOVE_SLOT_1), static_cast<int>(MOVE_SLOT::MOVE_SLOT_4));
	MOVE_SLOT slotSelected = static_cast<MOVE_SLOT>(randMove(Game::gen));
	auto& moveToUse = moveList[slotSelected];
	Move* move = &Move::moveDatabase[moveToUse];
	if (move->targetGroup == Game::MOVE_TARGET_GROUP::OPPOSITE)
	{
		if (!targets.empty())
		{
			std::uniform_int_distribution<size_t> randTarget(0, targets.size() - 1);
			Character* target = targets[randTarget(Game::gen)];
			target->spriteState = SPRITE_STATE::IDLE;
			target->spriteTimer = 2.0f;
			if (faction == Game::FACTION::ENEMY)
			{
				entity->getComponent<JumpToPoint>()->Trigger(AEVec2{ -500.f, -150.f }, 500.f, 0.5f);
			}
			UseMove(slotSelected, target);
		}
	}
	else if (move->targetGroup == Game::MOVE_TARGET_GROUP::AOE_OPPOSITE)
	{
		int count = 0;
		for (auto& target : targets)
		{
			target->spriteState = SPRITE_STATE::IDLE;
			if (faction == Game::FACTION::ENEMY)
			{
				target->entity->transform->setPosition(AEVec2(-700.f + (count * 200.f), -150.f));
				count++;
			}
			target->spriteTimer = 2.0f;

		}
		if (faction == Game::FACTION::ENEMY)
		{
			entity->getComponent<JumpToPoint>()->Trigger(AEVec2{ -500.f, -150.f }, 500.f, 0.5f);
		}
		UseMove(slotSelected, targets);

	}
	else
	{
		if (faction == Game::FACTION::ENEMY)
		{
			entity->getComponent<JumpToPoint>()->Trigger(AEVec2{ entity->transform->getPosition().x, entity->transform->getPosition().y + 50.f}, 500.f, 0.5f);
		}
		UseMove(slotSelected, this);

	}
}

void Character::EndTurn(void)
{
	endingTurn = true;
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
	case Game::CRIT_RATE:
		critRate += value;
		break;
	case Game::CRIT_DAMAGE:
		critDMG += value;
		break;
	case Game::ATTRIBUTE_TYPE::DMG_BONUS:
		dmgBonus += value;
		break;
	case Game::ATTRIBUTE_TYPE::DMG_REDUCTION:
		dmgReduction += value;
		break;
	}
}

float Character::GetStat(Game::ATTRIBUTE_TYPE type) const
{
	switch (type)
	{
		case (Game::ATTRIBUTE_TYPE::ATK):
		{
			return atk;
		}
		case (Game::ATTRIBUTE_TYPE::DEF):
		{
			return def;
		}
		case (Game::ATTRIBUTE_TYPE::HP):
		{
			return maxHP;
		}
		case (Game::ATTRIBUTE_TYPE::CRIT_RATE):
		{
			return critRate;
		}
		case (Game::ATTRIBUTE_TYPE::CRIT_DAMAGE):
		{
			return critDMG;
		}
		case (Game::ATTRIBUTE_TYPE::DMG_BONUS):
		{
			return dmgBonus;
		}
		case (Game::ATTRIBUTE_TYPE::DMG_REDUCTION):
		{
			return dmgReduction;
		}
		default:
		{
			return 0.0f;
		}
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
	//if (endingTurn)
	//{
	//	if (spriteTimer > 0.f)
	//	{
	//		entity->getComponent<Mesh>()->pTex = meshSystem->getTexture(characterModelTexture2.c_str());
	//		spriteTimer -= 1.0f * static_cast<float>(AEFrameRateControllerGetFrameTime());
	//	}

	//	if (spriteTimer <= 0.5f)
	//	{
	//		entity->getComponent<Mesh>()->pTex = meshSystem->getTexture(characterModelTexture.c_str());

	//		if (spriteTimer <= 0)
	//		{
	//			if (faction == Game::PLAYER)
	//			{
	//				entity->getComponent<Mesh>()->isActive = false;
	//			}
	//			turnFinished = true;
	//		}
	//	}
	//}

	if (spriteTimer > 0)
	{
		entity->getComponent<Mesh>()->isActive = true;
		switch (spriteState)
		{
			case SPRITE_STATE::IDLE:
			{
				entity->getComponent<Mesh>()->pTex = meshSystem->getTexture(characterModelTexture.c_str());
				break;
			}
			case SPRITE_STATE::ATTACKING:
			{
				entity->getComponent<Mesh>()->pTex = meshSystem->getTexture(characterModelTexture2.c_str());
				if (spriteTimer <= 0.5f)
				{
					entity->getComponent<Mesh>()->pTex = meshSystem->getTexture(characterModelTexture.c_str());
				}
				break;
			}
		}
		spriteTimer -= 1.0f * static_cast<float>(AEFrameRateControllerGetFrameTime());
	}
	else
	{
		if (faction == Game::FACTION::PLAYER)
		{
			entity->getComponent<Mesh>()->isActive = false;
		}
		turnFinished = true;
	}
}

void Character::fixedUpdate()
{

}

void Character::destroy()
{

}