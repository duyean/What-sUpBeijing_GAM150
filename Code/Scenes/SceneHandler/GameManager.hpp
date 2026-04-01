/******************************************************************************/
/*!
\file   GameManager.hpp
\author Tai Qian Yi
\par    Email: t.qianyi\@digipen.edu
\par    DigiPen login: t.qianyi
\par    Course: CSD1451
\par    Section B
\brief  This file contains the declarations of functions to manage the game
*/
/******************************************************************************/
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
	

public:
	GameManager();
	~GameManager();

	//public bool for quitting game
	bool quitGame =  false;


/*!***********************************************************************
\brief Initialize game variables and settings
*************************************************************************/
	void Init();

/*!***********************************************************************
\brief Updates game frame
\param _dt
game delta time
*************************************************************************/
	void Update(float _dt);

/*!***********************************************************************
\brief Updates game at fixed intervals
\param _dt
\param accumulator
*************************************************************************/
	void FixedUpdate(double _fixedDt, double accumulator);

/*!***********************************************************************
\brief Renders game frame
*************************************************************************/
	void Render();

/*!***********************************************************************
\brief Clears Game Manager variables
*************************************************************************/
	void Exit();
};

