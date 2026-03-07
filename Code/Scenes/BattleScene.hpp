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


class BattleScene : public GameState
{
private:
	const std::vector<AEVec2> enemyPositions = { { 400.f, 250.f }, {150.f, 300.f}, {650.f, 300.f} };
	const std::vector<AEVec2> allyPositions = { { -450.f, -150.f }, {-300.f, 300.f}, {-600.f, 300.f} };

	GameStateManager* stateManager;
	MeshGen* meshSystem;
	EntityManager* enSystem;
	BattleManager* battleManager;

public:
	BattleScene();
	~BattleScene();


	void GenerateEnemies(BATTLE_TYPE type = BATTLE_TYPE::NORMAL);
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