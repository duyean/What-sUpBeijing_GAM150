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
        writer.Int(static_cast<int>(Game::WUXING_ELEMENT::EARTH));
    
        writer.Key("baseHP");
        writer.Double(100.0);
    
        writer.Key("baseATK");
        writer.Double(20.0);
    
        writer.Key("baseDEF");
        writer.Double(15.5);
    
        writer.Key("faction");
        writer.Int(static_cast<int>(Game::FACTION::PLAYER));

        writer.Key("moves");
        writer.StartObject();
            writer.Key("0");
            writer.Int(1);
            writer.Key("1");
            writer.Int(2);
            writer.Key("2");
            writer.Int(3);
            writer.Key("3");
            writer.Int(4);
        writer.EndObject();
    writer.EndObject();
}

void WriteMovesJSON(rapidjson::PrettyWriter<rapidjson::OStreamWrapper>& writer)
{
    writer.StartObject();
    writer.Key("moves");
    writer.StartArray();
        writer.StartObject();
            writer.Key("id");
            writer.Int(0);
            writer.Key("name");
            writer.String("Basic Attack");
            writer.Key("coefficient");
            writer.Double(0.2);
            writer.Key("dot");
            writer.Double(0.0);
            writer.Key("brief");
            writer.String("Attacks a single enemy");
            writer.Key("description");
            writer.String("This is a LONG description of Move 1. Blah blah blah weh weh weh grrrrrrrrrrrrrrrrr");
            writer.Key("target");
            writer.Int(2);
            writer.Key("modifiers");
            writer.StartArray();
            writer.EndArray();
        writer.EndObject();
        writer.StartObject();
            writer.Key("id");
            writer.Int(1);
            writer.Key("name");
            writer.String("Scorch");
            writer.Key("coefficient");
            writer.Double(0.1);
            writer.Key("dot");
            writer.Double(0.15);
            writer.Key("brief");
            writer.String("Attacks an enemy and applies BURN");
            writer.Key("description");
            writer.String("This is a LONG description of Move 2. Blah blah blah weh weh weh grrrrrrrrrrrrrrrrr\nAlso I'm on fire now.");
            writer.Key("target");
            writer.Int(2);
        writer.EndObject();
    writer.EndArray();
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
	//jsonSerializer.WriteIntoFile("Assets/Characters/Guy.json", WriteIntoJSON);
	//jsonSerializer.WriteIntoFile("Assets/Moves/moves-list.json", WriteMovesJSON);

	InitModifierDatabase(jsonSerializer, "Assets/Moves/modifiers-list.json");
	Move::InitMoveDatabase(jsonSerializer, "Assets/Moves/moves-list.json");

    character = new Character();
    character->LoadCharacter(jsonSerializer, "Assets/Characters/Guy.json");

    battleManager = new BattleManager();
    battleManager->LoadBattleUnit(character);
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