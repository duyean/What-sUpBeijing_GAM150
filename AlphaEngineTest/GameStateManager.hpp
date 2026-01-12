/*!
@file GameStateManager.h
@author Tai Qian Yi (t.qianyi)
@course CSD11451
@section B
@Final Project
@date 12/1/26
@brief
This file contains the declarations of functions to manage Game States
*//*______________________________________________________________________*/
#pragma once
#include "SingletonPattern.hpp"
#include "GameState.hpp"

class GameStateManager : public SingletonPattern<GameStateManager>
{
	friend SingletonPattern<GameStateManager>;

public: 	
	//enum for the game states
	enum SCENES {
	SPLASHSCREEN,
	MAIN_MENU,
	LEVEL_1,
	NUM_SCENES
};

private:
	GameState* curGameState;
	GameState* nextGameState;
	SCENES currentLevel;

public:
	GameStateManager();
	~GameStateManager();

	/*!
	@brief Initialize GameStateManager variables
	@param void
	@return void
	*//*______________________________________________________________*/
	void Init();

	/*!
	@brief Updates current scene
	@param float
	@return void
	*//*______________________________________________________________*/
	void Update(float _dt);

	/*!
	@brief Render current screen
	@param void
	@return void
	*//*______________________________________________________________*/
	void Render();

	/*!
	@brief Clears GameStateManager variables
	@param void
	@return void
	*//*______________________________________________________________*/
	void Exit();

	/*!
	@brief Loads next Game State
	@param enum SCENES
	@return void
	*//*______________________________________________________________*/
	void NextScene(SCENES _scene);

	bool IsLastLevel(void);
	SCENES GetCurrentLevel(void);
	void LoadNextLevel(void);
};

