/*!
@file GameManager.hpp
@author Tai Qian Yi (t.qianyi)
@course CSD11451
@section B
@Final Project
@date 12/1/26
@brief
This file contains the declarations of functions to manage the game
*//*______________________________________________________________________*/
#pragma once
#include "GameStateManager.hpp"

class GameManager : public SingletonPattern<GameManager>
{
	friend SingletonPattern<GameManager>;
private:
	GameStateManager* stateManager;
	bool ShowDebug;

public:
	GameManager();
	~GameManager();

	/*!
	@brief Initialize game variables and settings
	@param void
	@return void
	*//*______________________________________________________________*/
	void Init();

	/*!
	@brief Updates game frame
	@param float
	@return void
	*//*______________________________________________________________*/
	void Update(float _dt);

	/*!
	@brief Render game frame
	@param void
	@return void
	*//*______________________________________________________________*/
	void Render();

	/*!
	@brief Clears game manager variables
	@param void
	@return void
	*//*______________________________________________________________*/
	void Exit();
};

