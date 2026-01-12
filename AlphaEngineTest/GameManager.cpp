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
	//CP_System_SetWindowSize(1600, 900);
	/*CP_System_SetWindowSize(
		CP_System_GetDisplayWidth() - 100, 
		CP_System_GetDisplayHeight() - 100);*/
	/*CP_System_SetWindowSize(
		1600,
		900);*/

	//Set the starting game scene
	stateManager->NextScene(GameStateManager::SPLASHSCREEN); //GAME_SCREEN SPLASHSCREEN

	//Initialize our singleton classes
	/*audioManager->Init();
	meshManager->Init();
	settingsManager->Init();
	dialogManager->Init();
	objectiveManager->Init();
	emitterManager->Init();*/
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