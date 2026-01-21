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
		writer.Key("name");
		writer.String("Guy");

		writer.Key("element");
		writer.Int(Game::WUXING_ELEMENT::EARTH);
	
		writer.Key("baseHP");
		writer.Double(100.0);
	
		writer.Key("baseATK");
		writer.Double(20.0);
	
		writer.Key("baseDEF");
		writer.Double(15.5);
	
		writer.Key("faction");
		writer.Int(Game::FACTION::PLAYER);

		writer.Key("moves");
		writer.StartObject();
			writer.Key("0");
			writer.String("test");
			writer.Key("1");
			writer.String("test");
			writer.Key("2");
			writer.String("test");
			writer.Key("3");
			writer.String("test");
		writer.EndObject();
	writer.EndObject();
}

void WriteMovesJSON(rapidjson::PrettyWriter<rapidjson::OStreamWrapper>& writer)
{
	writer.StartObject();
		writer.Key("0");
		writer.StartObject();
			writer.Key("name");
			writer.String("Generic Damage Move");
			writer.Key("coefficient");
			writer.Double(0.5);
			writer.Key("brief");
			writer.String("This is a short brief of Move 1.");
			writer.Key("description");
			writer.String("This is a LONG description of Move 1. Blah blah blah weh weh weh grrrrrrrrrrrrrrrrr");
		writer.EndObject();
		writer.Key("1");
		writer.StartObject();
			writer.Key("name");
			writer.String("Burn Move");
			writer.Key("coefficient");
			writer.Double(0.7);
			writer.Key("brief");
			writer.String("This is a short brief of Move 2.");
			writer.Key("description");
			writer.String("This is a LONG description of Move 2. Blah blah blah weh weh weh grrrrrrrrrrrrrrrrr\nAlso I'm on fire now.");
		writer.EndObject();
	writer.EndObject();
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
	jsonSerializer.WriteIntoFile("../../Assets/Characters/Guy.json", WriteIntoJSON);
	jsonSerializer.WriteIntoFile("../../Assets/Moves/moves-list.json", WriteMovesJSON);

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