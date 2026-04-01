/*!************************************************************************
* \file BattleManager.hpp
* \author Wayne Lion Wei Jynn
* \par DP email: lion.w\@digipen.edu
* \par Course: CSD1451-b
* \brief
*   This file implements the Battle Manager for our game
**************************************************************************/

#pragma once
#include <vector>
#include "../../Engine_WZBJ_Pak.hpp"
#include "../Character/Character.hpp"
#include "../Code/Combat/EventHandler/CombatEventHandler.hpp"
#include "../Code/SoloBehavior/RunManager.hpp"

#include "../../BaseSystems/Engine/EntityManager.hpp"
#include "../Code/SoloBehavior/TransitionScreen.hpp"

/*!***********************************************************************
* \class BattleManager
* \brief
*  The SoloBehavior object for BattleManager
*************************************************************************/
class BattleManager : public SoloBehavior
{
	//A vector of all the current units in battle
	std::vector<Character*> battleUnits;

	//The original unsorted player units for the Party UI
	std::vector<Character*> playerUnits;

	//The vector to store indices to handle permadeath
	std::vector<size_t> toRemoveIndices;

	//Pointer to a targeting reticle Entity
	Entity* targetingReticle;

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

	//Action point system to prevent powerful move spamming
	int actionPoint, maxActionPoints;

	//Constructor
	BattleManager();

	/*!***********************************************************************
	* \brief
	*  Add a Character to battle
	* \param[in] unit
	*  A pointer to the character to load
	*************************************************************************/
	void LoadBattleUnit(Character* unit);

	/*!***********************************************************************
	* \brief
	*  Start the battle, loading important data
	*************************************************************************/
	void StartBattle();

	/*!***********************************************************************
	* \brief
	*  Handles when a Character has died in battle
	* \param[in] deadUnit
	*  The pointer to character that perished
	*************************************************************************/
	void ProcessDeadUnit(Character* deadUnit);

	/*!***********************************************************************
	* \brief
	*  Process player targeting during player's turn
	*************************************************************************/
	void ProcessTargeting();

	/*!***********************************************************************
	* \brief
	*  Handles clean up after a battle has ended
	*************************************************************************/
	void ResetBattle();

	/*!***********************************************************************
	* \brief
	*  Helper function for targeting by clicking on an enemy
	* \param[in] mouseX
	*  The X coordinate of the mouse
	* \param[in] mouseY
	*  The Y coordinate of the mouse
	* \param[in] transform
	*  The transform to check for clicks
	*************************************************************************/
	bool PointInMesh(const s32& mouseX, const s32& mouseY, const Transform2D* transform);

	/*!***********************************************************************
	* \brief
	*  Checks if a battle is ongoing.
	* \return
	*  True if a battle is ongoing
	*************************************************************************/
	bool InBattle() const;

	/*!***********************************************************************
	* \brief
	*  Gets the current turn of battle
	* \return
	*  The number of turns that have passed
	*************************************************************************/
	int GetCurrentTurn() const;

	/*!***********************************************************************
	* \brief
	*  Gets the current acting unit
	* \return
	*  A pointer to the Character that is acting
	*************************************************************************/
	Character* GetActiveUnit();

	/*!***********************************************************************
	* \brief
	*  Gets the unit the player last targeted
	* \return
	*  A pointer to the Character that the player last targeted
	*************************************************************************/
	Character* GetlastTargetedUnit();

	/*!***********************************************************************
	* \brief
	*  Gets all enemies in battle
	* \return
	*  A vector to all enemies in battle
	*************************************************************************/
	std::vector<Character*> GetAllEnemies();

	/*!***********************************************************************
	* \brief
	*  Gets all player characters in battle
	* \return
	*  A vector to all player characters
	*************************************************************************/
	std::vector<Character*> GetPlayerParty() const;

	/*!***********************************************************************
	* \brief
	*  Assigns the targeting reticle entity
	* \param[in] en
	*  The targeting reticle entity 
	*************************************************************************/
	void SetTargetingReticle(Entity* en);

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;
};