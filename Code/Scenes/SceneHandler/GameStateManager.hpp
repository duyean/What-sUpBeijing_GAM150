/******************************************************************************/
/*!
\file   GameStateManager.hpp
\author Tai Qian Yi
\par    Email: t.qianyi\@digipen.edu
\par    DigiPen login: t.qianyi
\par    Course: CSD1451
\par    Section B
\brief  This file contains the declarations of functions to manage Game States
*/
/******************************************************************************/

#pragma once
#include "../../BaseSystems_WZBJ_Pak.hpp"
#include "GameState.hpp"

class GameStateManager : public SingletonPattern<GameStateManager>
{
	friend SingletonPattern<GameStateManager>;

public: 	
	//enum for the game states
	enum SCENES {
	SPLASHSCREEN,
	MAIN_MENU,
	BASE_CAMP,
	LEVEL_SCENE,
	BATTLE_SCENE,
	NUM_SCENES,
};

private:
	GameState* curGameState;
	GameState* nextGameState;
	SCENES currentLevel;

public:
	GameStateManager();
	~GameStateManager();

/*!***********************************************************************
\brief Initialize GameState variables
*************************************************************************/
	void Init();

/*!***********************************************************************
\brief Updates current scene
\param _dt
delta time
*************************************************************************/
	void Update(float _dt);

/*!***********************************************************************
\brief Clears GameState variables
*************************************************************************/
	void Exit();

/*!***********************************************************************
\brief Loads next GameState
*************************************************************************/
	void NextScene(SCENES _scene);

/*!***********************************************************************
\brief Gets the current Scene enum
\return SCENES
enum of the current scene
*************************************************************************/
	SCENES GetCurrentLevel(void) const;
};

