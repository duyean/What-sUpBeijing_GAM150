/*!
@file SplashScreen.cpp
@author Tai Qian Yi (t.qianyi)
@course CSD11451
@section B
@Final Project
@date 13/1/26
@brief
This file contains the definitions for the collection of functions in MainMenu.hpp
*//*______________________________________________________________________*/
#include "MainMenu.hpp"

#include <iostream>

#include "../Code/BaseSystems/JSONSerializer/JSONSerializer.hpp"
#include "../JSONSerializer_WZBJ_Pak.hpp"
#include "../Combat/BattleManager/BattleManager.hpp"
#include "../Code/Combat/Move.hpp"
#include "../Code/Combat/Modifier/Modifier.hpp"
#include "../Maps_WZBJ_Pak.hpp"

JSONSerializer jsonSerializer{};
Character* character = nullptr;
Character* testEnemy = nullptr;
BattleManager* battleManager = nullptr;
Map myMap{};

MainMenu::MainMenu()
{
	
}

MainMenu::~MainMenu()
{
}

/*!
@brief Initialize splash screen variables

Overwrites virtual GameState::Init().
This function loads splash screen image

@param void
@return void
*//*______________________________________________________________*/
void MainMenu::Init()
{
	InitModifierDatabase(jsonSerializer, "Assets/Moves/modifiers-list.json");
	Move::InitMoveDatabase(jsonSerializer, "Assets/Moves/moves-list.json");

    character = new Character();
    character->LoadCharacter(jsonSerializer, "Assets/Characters/Guy.json");

    testEnemy = new Character();
    testEnemy->LoadCharacter(jsonSerializer, "Assets/Characters/Guy.json");
    testEnemy->SetName("TestEnemy");
    testEnemy->SetFaction(Game::FACTION::ENEMY);

    battleManager = new BattleManager();
    battleManager->LoadBattleUnit(character);
    battleManager->LoadBattleUnit(testEnemy);
    battleManager->StartBattle();

    //Map myMap = Map::GenerateMap(CityStreets, 5, 5);
    Map myMap;
    Map::LoadMap(myMap, jsonSerializer, "Assets/Map/testmap.json");
    //Map::SaveMap(myMap, jsonSerializer, "Assets/Map/testmap.json");
}

/*!
@brief Updates splash screen frame

Overwrites virtual GameState::Update().
This function updates variables in splash screen per frame to
makes image fade in and out before loading main menu.

@param float
@return void
*//*______________________________________________________________*/
void MainMenu::Update(float _dt)
{
    battleManager->Update(_dt);
}

/*!
@brief Render splash screen

Overwrites virtual GameState::Render().
This function renders splash screen image

@param void
@return void
*//*______________________________________________________________*/
void MainMenu::Render()
{

}

/*!
@brief Clears splash screen variables

Overwrites virtual GameState::Exit().
This function frees splash screen image used.

@param void
@return void
*//*______________________________________________________________*/
void MainMenu::Exit()
{
	delete character;
	delete battleManager;
}