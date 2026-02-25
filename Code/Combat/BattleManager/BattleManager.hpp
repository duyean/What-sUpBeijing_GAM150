#pragma once
#include <vector>
#include "../../Engine_WZBJ_Pak.hpp"
#include "../Character/Character.hpp"
#include "../Code/Combat/EventHandler/CombatEventHandler.hpp"

class BattleManager : public SoloBehavior
{
	std::vector<Character*> battleUnits;
	int currentActiveUnit;
	Character* lastTargetedUnit;
	bool inBattle;
	int enemyCount;
	bool wait;
	float delay;

	enum BATTLE_OUTCOME
	{
		NONE,
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
	void ProcessTargeting();
	bool PointInMesh(const s32& mouseX, const s32& mouseY, const Transform2D* transform);

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;
};