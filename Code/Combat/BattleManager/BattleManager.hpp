#pragma once
#include <vector>
#include "../Character/Character.hpp"
#include "../../Engine_WZBJ_Pak.hpp"

class BattleManager : public SoloBehavior
{
	std::vector<Character*> battleUnits;
	Character* testEnemy, *testPlayer;
	int currentActiveUnit;
	bool inBattle;
	int enemyCount;
	bool wait;

	enum BATTLE_OUTCOME
	{
		VICTORY,
		DEFEAT
	};

	BATTLE_OUTCOME outcome;

public:
	static BattleManager* instance;
	BattleManager();
	void LoadBattleUnit(Character* unit);
	void StartBattle();
	void ProcessDeadUnit(Character* deadUnit);

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;
};