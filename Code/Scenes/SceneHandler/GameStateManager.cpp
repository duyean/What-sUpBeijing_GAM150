/*!
@file SplashScreen.cpp
@author Tai Qian Yi (t.qianyi)
@course CSD11451
@section B
@Final Project
@date 12/1/26
@brief
This file contains the definitions for the collection of functions in GameStateManager.h
*//*______________________________________________________________________*/
#include "../../SceneHandler_WZBJ_Pak.hpp"
#include "../Code/Scenes/MainMenu.hpp"
#include "../Code/Scenes/SplashScreen.hpp"
#include "../Code/Scenes/Level1.hpp"
#include "../Code/Scenes/BaseCamp.hpp"

GameStateManager::GameStateManager() :
	curGameState(nullptr),
	nextGameState(nullptr)
{
}

GameStateManager::~GameStateManager()
{
}

/*!
@brief Initialize splash screen variables

@param void
@return void
*//*______________________________________________________________*/
void GameStateManager::Init()
{

}

/*!
@brief Updates current scene

This function updates current scene frame and changes scene if there is one on standby

@param float
@return void
*//*______________________________________________________________*/
void GameStateManager::Update(float _dt)
{
	if (nextGameState != nullptr)
	{
		if (curGameState != nextGameState) {
			if (curGameState != nullptr) {
				curGameState->Unload();
				delete curGameState;

			}
			curGameState = nextGameState;
			curGameState->Load();
		}

	}
	
}

/*!
@brief Clears GameStateManager variables

This function exits current scene and deletes it.

@param void
@return void
*//*______________________________________________________________*/
void GameStateManager::Exit()
{
	nextGameState = nullptr;
	if (curGameState != nullptr) {
		curGameState->Unload();
		delete curGameState;
	}
}

/*!
@brief Sets next game scene

This function sets the next scene on standby and stops all audio

@param enum::SCENES
@return void
*//*______________________________________________________________*/
void GameStateManager::NextScene(SCENES _scene)
{
	if (_scene == SCENES::NUM_SCENES) {
		//DEBUG
		printf("Tried Loading Invalid Scene\n");
		return;
	}

	switch(_scene){
	case SPLASHSCREEN:
		nextGameState = new SplashScreen;
		break;	
	case MAIN_MENU:
		nextGameState = new MainMenu;
		break;
	case BASE_CAMP:
		nextGameState = new BaseCamp;
		break;
	case LEVEL1:
		nextGameState = new Level1;
		break;
	default:
		//DEBUG
		printf("No Scene available for given State\n");
		break;
	}
}

bool GameStateManager::IsLastLevel(void)
{
	return ((currentLevel + 1) >= NUM_SCENES);
}

GameStateManager::SCENES GameStateManager::GetCurrentLevel(void)
{
	return currentLevel;
}

void GameStateManager::LoadNextLevel(void)
{
	//currentLevel = (SCENES)(currentLevel + 1);
	//NextScene(currentLevel);
}
