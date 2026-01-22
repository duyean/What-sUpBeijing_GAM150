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

// This is all temporary btw
void WriteIntoJSON(rapidjson::PrettyWriter<rapidjson::OStreamWrapper>& writer)
{
	writer.StartObject();
	writer.Key("test");
	writer.String("yay!");
	writer.EndObject();
}

void ReadFromJSON(rapidjson::Document& doc)
{
	std::cout << doc["test"].GetString();
}

JSONSerializer jsonSerializer{};
Character* character = nullptr;
BattleManager* battleManager = nullptr;

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
	jsonSerializer.WriteIntoFile("Assets/test.json", WriteIntoJSON);
	//jsonSerializer.WriteIntoFile("../../Assets/Characters/Guy.json", WriteIntoJSON);
	//jsonSerializer->WriteIntoFile("../../Assets/Moves/moves-list.json", WriteMovesJSON);

	character = new Character();
	character->LoadCharacter(jsonSerializer, "../../Assets/Characters/Guy.json");

	battleManager = new BattleManager();
	battleManager->LoadBattleUnit(character);

	InitModifierDatabase();
	Move::InitMoveDatabase();
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
	// JSON Serializer test
	if (AEInputCheckTriggered(AEVK_SPACE))
		jsonSerializer.ReadFromFile("Assets/test.json", ReadFromJSON);
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