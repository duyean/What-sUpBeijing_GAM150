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
#include "AEEngine.h"
#include "GameStateManager.hpp"


class EventSystem;
class GameStateManager;
class MeshGen;
class EntityManager;
class PhysicSystem;
class RenderSystem;

class GameManager : public SingletonPattern<GameManager>
{
	friend SingletonPattern<GameManager>;
private:
	EventSystem* eventSystem;
	GameStateManager* stateManager;
	MeshGen* meshSystem;
	EntityManager* enSystem;
	PhysicSystem* phSystem;
	RenderSystem* rSystem;
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
	@brief Updates game at fixed intervals
	@param float
	@return void
	*//*______________________________________________________________*/
	void FixedUpdate(double _fixedDt, double accumulator);

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

