#include "BattleManager.hpp"
#include <algorithm>
#include <iostream>
#include "../CombatUIManager.hpp"

BattleManager* BattleManager::instance;

void BattleManager::awake()
{
	if (!instance)
	{
		instance = this;
	}
}

void BattleManager::init()
{

}

BattleManager::BattleManager()
{

}

void BattleManager::LoadBattleUnit(Character* unit)
{
	if (!unit)
	{
		printf("Warning: Attempted to add a null character to battle!\n");
		return;
	}
	unit->Init();
	battleUnits.push_back(unit);
}

void BattleManager::StartBattle()
{
	//Sort the list based on initiative in descending order
	std::sort(battleUnits.begin(), battleUnits.end(), [](const Character* a, const Character* b) {return a->GetInitiative() > b->GetInitiative();});
	for (Character* unit : battleUnits)
	{
		unit->SetOnDeath([this](Character* dead) {ProcessDeadUnit(dead);});
		if (unit->GetFaction() == Game::FACTION::ENEMY)
		{
			enemyCount++;
		}
	}
	currentActiveUnit = 0;
	inBattle = true;
	AEVec2 pos = { 0.f, 225 };
	CombatUIManager::instance->CreateMessageText(pos, "Battle Start");
}

void BattleManager::update()
{
	if (!inBattle)
	{
		return;
	}

	Character* activeUnit = battleUnits[currentActiveUnit];
	if (!wait)
	{
		activeUnit->StartTurn();
		wait = true;
	}

	if (activeUnit->GetFaction() == Game::PLAYER)
	{
		//activeUnit->Draw();
	}

	if (!activeUnit->TurnFinished() && wait)
	{
		//Register Inputs
		if (AEInputCheckTriggered(AEVK_Z))
		{
			activeUnit->UseMove(MOVE_SLOT_1, activeUnit);
		}
		else if (AEInputCheckTriggered(AEVK_X))
		{
			activeUnit->UseMove(MOVE_SLOT_2, activeUnit);
		}
	}

	if (activeUnit->TurnFinished() && wait)
	{
		currentActiveUnit++;
		if (currentActiveUnit >= battleUnits.size())
		{
			currentActiveUnit = 0;
		}
		wait = false;
	}
}

void BattleManager::fixedUpdate()
{

}

void BattleManager::ProcessDeadUnit(Character* dead)
{
	if (dead->GetFaction() == Game::FACTION::ENEMY)
	{
		enemyCount--;
		if (enemyCount <= 0)
		{
			inBattle = false;
			outcome = VICTORY;
			AEVec2 pos = { 0.f, 225 };
			CombatUIManager::instance->CreateMessageText(pos, "Battle Over!");
		}
	}
}

void BattleManager::destroy()
{
	battleUnits.clear();

}