/*!
@file RunManager.hpp
@author Wayne Lion (lion.w)
@course CSD11451
@section B
@Final Project
@date 25/2/26
@brief
This file contains the interface for a Run Manager for our game.
*//*______________________________________________________________________*/

#pragma once
#include "../Code/Engine_WZBJ_Pak.hpp"
#include "../Combat/Blessing/Blessing.hpp"
//#include "../Map/MapClass.hpp"
#include "../Maps_WZBJ_Pak.hpp"
#include <memory>

//Forward declare the character class
class Character;

//enum of the different battle types to be used in battle scene
enum struct BATTLE_TYPE
{
	NORMAL,
	BOSS,
	MINI_BOSS,
};

class RunManager
{
	//Stores the current characters in the player's party
	std::vector<Game::CHARACTER_ID> party;

	//Stores the current blessings obtained upon the current run
	std::vector<std::unique_ptr<Blessing>> runBlessings;

	//Determine the enemy's scaling over a run
	int enemyDifficulty;

	//Determines the player's level
	int partyLevel;

	//Stores the shop currency over a run
	int currency;

	//battle type to set when changing to the battle scene
	BATTLE_TYPE bt;

	MapType currMapType;
	MapType prevMapType;
public:
	RunManager();
	~RunManager();

	const std::vector<Game::CHARACTER_ID>& GetParty() const;

	//Singleton accessor for this class
	static RunManager& Instance();

	//Starts a new run
	void StartRun();

	//Reset Tutorial Pages
	void ResetTutorials();

	// Resets everything in the save
	void ResetSave();

	//Add a blessing to the current run
	void AddBlessing(std::unique_ptr<Blessing> blessing);

	// Remove currency when buying items
	bool RemoveCurrency(int curr);

	inline int GetEnemyDifficulty() const { return enemyDifficulty; }
	inline int GetPartyLevel() const { return partyLevel; }
	inline void ModifyCurrency(int v) { currency += v; AEClamp(f32(currency), 0.f, f32(currency)); }
	inline void ModifyEnemyDifficulty(int v) { enemyDifficulty += v; }
	inline void ModifyPartyLevel(int v) { partyLevel += v; }
	inline int GetCurrency() const { return currency; }
	void SetBattleType(BATTLE_TYPE type = BATTLE_TYPE::NORMAL);

	BATTLE_TYPE GetBattleType() const;

	Game::CHARACTER_ID GenerateCharacter();

	void AddCharacter(Game::CHARACTER_ID charID);

	void SetMapType(MapType type);

	void IncrementMapType();

	void SetPrevMapType(MapType type);

	void RemovePlayerFromParty(size_t index);

	MapType GetMapType() const;

	MapType GetPrevMapType() const;

	//game related booleans
	bool game_paused = false;
	bool game_won = false;
	bool playerCanMove = true;

	//tutorial page booleans
	bool firstTimeBase;
	bool firstTimeExplore;
	bool firstTimeCombat;

	void SaveRun() const;
	bool LoadRun();

	//Get the current list of blessings
	const std::vector<std::unique_ptr<Blessing>>& GetBlessings() const;
};