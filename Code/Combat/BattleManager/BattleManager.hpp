#pragma once
#include <vector>
#include "../../Engine_WZBJ_Pak.hpp"
#include "../Character/Character.hpp"
#include "../Code/Combat/EventHandler/CombatEventHandler.hpp"
#include "../Code/SoloBehavior/RunManager.hpp"

#include "../../BaseSystems/Engine/EntityManager.hpp"
#include "../Code/SoloBehavior/TransitionScreen.hpp"

class BattleManager : public SoloBehavior
{
	//A vector of all the current units in battle
	std::vector<Character*> battleUnits;

	//The original unsorted player units for the Party UI
	std::vector<Character*> playerUnits;

	//An integer to index the current acting unit
	int currentActiveUnit;

	//The pointer to the acting unit
	Character* activeUnit;

	//Pointer to the last enemy the player targeted
	Character* lastTargetedUnit;

	//Get the current turn
	int currentTurn;

	//Boolean to indicate whether a battle is ongoing
	bool inBattle;

	//Number of enemies in battle
	int enemyCount;

	//Number of player characters in battle
	int playerCount;

	//Boolean to wait for input
	bool wait;

	//Float for delayed executions
	float delay;

	enum BATTLE_OUTCOME
	{
		NONE,
		VICTORY,
		DEFEAT
	};

	//Enum to determine the outcome of the battle
	BATTLE_OUTCOME outcome;

	EntityManager* enSystem = nullptr;
	TransitionScreen* ts = nullptr;
public:
	//Constructor
	BattleManager();

	/// <summary>
	/// Loads a Character into the battleUnits vector
	/// </summary>
	/// <param name="unit">Pointer to the character joining the battle</param>
	void LoadBattleUnit(Character* unit);

	/// <summary>
	/// Start the battle
	/// </summary>
	void StartBattle();

	/// <summary>
	/// Function to process a Character dying in battle
	/// </summary>
	/// <param name="deadUnit">A pointer to the Character that died</param>
	void ProcessDeadUnit(Character* deadUnit);

	/// <summary>
	/// Function handle target selection during battle
	/// </summary>
	void ProcessTargeting();

	/// <summary>
	/// Clean up after a battle has ended
	/// </summary>
	void ResetBattle();

	/// <summary>
	/// Helper function for target selection
	/// </summary>
	bool PointInMesh(const s32& mouseX, const s32& mouseY, const Transform2D* transform);

	bool InBattle() const;
	int GetCurrentTurn() const;
	Character* GetActiveUnit();
	Character* GetlastTargetedUnit();
	std::vector<Character*> GetPlayerParty() const;


	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;
};