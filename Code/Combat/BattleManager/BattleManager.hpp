#pragma once
#include <vector>
#include "../Character/Character.hpp"

class BattleManager
{

	std::vector<Character*> battleUnits;
	int currentActiveUnit;
	bool inBattle;
	int enemyCount;

	enum BATTLE_OUTCOME
	{
		VICTORY,
		DEFEAT
	};

	BATTLE_OUTCOME outcome;

public:

	void LoadBattleUnit(Character* unit);
	void StartBattle();
	void ProcessDeadUnit(Character* deadUnit);
	void Update(float _dt);
};