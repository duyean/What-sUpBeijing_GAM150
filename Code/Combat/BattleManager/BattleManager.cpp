#include "BattleManager.hpp"
#include <algorithm>

void BattleManager::LoadBattleUnit(Character* unit)
{
	if (!unit)
	{
		printf("Warning: Attempted to add a null character to battle!\n");
		return;
	}
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

	while (inBattle) //Probably put this in an Update loop
	{
		battleUnits[currentActiveUnit]->StartTurn();
		if (battleUnits[currentActiveUnit]->TurnFinished())
		{
			currentActiveUnit++;
			if (currentActiveUnit > (battleUnits.size() - 1))
			{
				currentActiveUnit = 0;
			}
		}
	}
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
		}
	}
}