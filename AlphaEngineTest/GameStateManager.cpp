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
#include "GameStateManager.hpp"

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
	if (curGameState != nextGameState) {
		if (curGameState != nullptr) {
			curGameState->Exit();
			delete curGameState;
		}

		curGameState = nextGameState;
		curGameState->Init();
	}

	curGameState->Update(_dt);
}

/*!
@brief Renders current scene

This function renders current scene

@param float
@return void
*//*______________________________________________________________*/
void GameStateManager::Render()
{
	curGameState->Render();
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
		curGameState->Exit();
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
		//printf("Tried Loading Invalid Scene");
		return;
	}

	switch(_scene){
	case SPLASHSCREEN:
		nextGameState = new SplashScreen;
		break;
	case INTRO_CUTSCENE:
		nextGameState = new IntroScreen;
		break;
	case MAIN_MENU:
		nextGameState = new MainMenu;
		break;
	case CREDITS_SCREEN:
		nextGameState = new CreditsScreen;
		break;
	case TUTORIAL:
		nextGameState = new GameScreen("Tutorial");
		currentLevel = TUTORIAL;
		break;
	case LEVEL_1:
		nextGameState = new GameScreen("Level1");
		currentLevel = LEVEL_1;
		break;
	/*case LEVEL_2:
		nextGameState = new GameScreen("Level2");
		currentLevel = LEVEL_2;
		break;*/
		
	default:
		//DEBUG
		//printf("No Scene available for given State");
		break;
	}

	//AudioManager::GetInstance()->StopAll();
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
	currentLevel = (SCENES)(currentLevel + 1);
	NextScene(currentLevel);
}
