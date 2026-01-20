/*!
@file GameManager.cpp
@author Tai Qian Yi (t.qianyi)
@course CSD11451
@section B
@Final Project
@date 12/1/26
This file contains the definition of functions for GameManager.h
*//*______________________________________________________________________*/
#include "GameManager.hpp"

GameManager::GameManager()
{
	stateManager = GameStateManager::GetInstance();
	meshSystem = MeshGen::getInstance();
	enSystem = EntityManager::getInstance();
	phSystem = PhysicSystem::getInstance();
}

GameManager::~GameManager()
{
}

/*!
@brief Initialize game variables and settings

This function sets game window size and intializes all other managers.

@param void
@return void
*//*______________________________________________________________*/
void GameManager::Init()
{
	//Set the starting game scene
	stateManager->NextScene(GameStateManager::SPLASHSCREEN); //GAME_SCREEN SPLASHSCREEN

	//Initialize our singleton classes here...
	meshSystem->initialize();

	//initialize all entities
	for (const auto& end : enSystem->entities)
	{
		end->init();
	}
}

/*!
@brief Updates game frame

This function updates managers per frame

@param float
@return void
*//*______________________________________________________________*/
void GameManager::Update(float _dt)
{
	stateManager->Update(_dt);

	// Your own update logic goes here
		//Update everything
	for (const auto& end : enSystem->entities)
	{
		end->update();
	}
}

void GameManager::FixedUpdate(double _fixedDt, double accumulator)
{
	if (accumulator >= _fixedDt)
	{
		for (const auto& end : enSystem->entities)
		{
			end->fixedUpdate();
		}
		phSystem->fixedUpdate(_fixedDt);
		accumulator -= _fixedDt;
	}
}


/*!
@brief Render game frame

This functions clears background for new frame and renders frame

@param void
@return void
*//*______________________________________________________________*/
void GameManager::Render() 
{
	//CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	stateManager->Render();
}

/*!
@brief Clears game manager variables

This functions clears variables for all managers and destroys instances.

@param void
@return void
*//*______________________________________________________________*/
void GameManager::Exit()
{
	stateManager->Exit();
	GameStateManager::DestroyInstance();
}