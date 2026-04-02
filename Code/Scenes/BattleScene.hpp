/*!
@file BattleScene.hpp
@author Tai Qian Yi (t.qianyi)
@course CSD11451
@section B
@Final Project
@date 13/1/26
@brief
This file contains the declarations of functions for the main menu
*//*______________________________________________________________________*/
#pragma once
#include "../BaseSystems_WZBJ_Pak.hpp"
#include "../SceneHandler_WZBJ_Pak.hpp"
#include "../Engine_WZBJ_Pak.hpp"
#include "../Code/SoloBehavior/RunManager.hpp"

class BattleManager;

enum struct NORMAL_ENEMY_TYPE
{
	INFANTRY,
	SLIME,
	DRAGON,
	TOTAL
};

//default enemy positions
static const std::vector<AEVec2> enemyPositions = { { 400.f, 250.f }, {150.f, 300.f}, {650.f, 300.f} };
//default party member positions
static const std::vector<AEVec2> allyPositions = { { -450.f, -150.f }, {-300.f, 300.f}, {-600.f, 300.f} };

class BattleScene : public GameState
{
private:
	//pointer to the state manager
	GameStateManager* stateManager;
	//pointer to the mesh Gen system
	MeshGen* meshSystem;
	//pointer to the entity system
	EntityManager* enSystem;
	//pointer to the battle manager
	BattleManager* battleManager;
	//boolean to check if can render each units stats
	bool renderUnitStat;
public:
	//cstr
	BattleScene();
	//dstr
	~BattleScene();

/*!***********************************************************************
\brief Function to generate eneimes based on the battle type
\param BATTLE_TYPE
*************************************************************************/
	void GenerateEnemies(BATTLE_TYPE type);
	/*!
	@brief Initialize Splash Screen variables
	@param void
	@return void
	*//*______________________________________________________________*/
	void Load() override;

	/*!
	@brief Clears splash screen variables
	@param void
	@return void
	*//*______________________________________________________________*/
	void Unload() override;

};