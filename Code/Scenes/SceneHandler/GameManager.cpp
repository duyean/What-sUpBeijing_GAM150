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
#include "../Code/SoloBehavior/RunManager.hpp"
#include "../Code/Engine_WZBJ_Pak.hpp"
#include "../Code/Audio_WZBJ_Pak.hpp"

GameManager::GameManager()
{
	stateManager = GameStateManager::GetInstance();
	meshSystem = &MeshGen::getInstance();
	enSystem = &EntityManager::getInstance();
	phSystem = &PhysicSystem::getInstance();
	rSystem = &RenderSystem::getInstance();
	eventSystem = &EventSystem::getInstance();
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
	//Initialize our singleton classes here...

	meshSystem->initialize();

	//Set the starting game scene
	stateManager->NextScene(GameStateManager::SPLASHSCREEN); //GAME_SCREEN SPLASHSCREEN
	//initialize all entities
	for (int i = 0; i < enSystem->entities.size(); i++)
	{
		enSystem->entities[i]->init();
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
	eventSystem->Update(_dt);

	if (AEInputCheckTriggered(AEVK_ESCAPE))
		RunManager::Instance().game_paused = !RunManager::Instance().game_paused;

	for (int i = 0; i < enSystem->entities.size(); i++)
	{
		if (enSystem->entities[i] != nullptr)
		{
			if (enSystem->entities[i]->toDestroy == true)
			{
				continue;
			}
			if (enSystem->entities[i]->allComponentsInit == false)
			{

				enSystem->entities[i]->init();

			}

			if (enSystem->entities[i]->isActive == true)
			{
				enSystem->entities[i]->update();
			}
			else
			{
				//Add in parental Active control sometime in the future and make sure no bugs
				// 
				//if (enSystem->entities[i]->transform != nullptr && enSystem->entities[i]->transform->activeDirty == true)
				//{
				//	for (int j = 0; j < enSystem->entities[i]->transform->children.size(); j++)
				//	{
				//		enSystem->entities[i]->transform->children[j]->isActive == false;
				//	}
			    //}
			}
		}
	}

	AudioManager::GetInstance()->Update();
}

void GameManager::FixedUpdate(double _fixedDt, double accumulator)
{
	if (accumulator >= _fixedDt)
	{
		for (int i = 0; i < enSystem->entities.size(); i++)
		{
			if (enSystem->entities[i]->toDestroy == true)
			{
				continue;
			}
			if (enSystem->entities[i] != nullptr)
			{
				if (enSystem->entities[i]->isActive == true)
				{
					enSystem->entities[i]->fixedUpdate();
				}
			}
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
	
	AEGfxSetBackgroundColor(0.3f, 0.3f, 0.3f);
	rSystem->RenderObjects(enSystem->entities);
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
	meshSystem->ClearAllFont();
	meshSystem->ClearAllMesh();
	GameStateManager::DestroyInstance();
}