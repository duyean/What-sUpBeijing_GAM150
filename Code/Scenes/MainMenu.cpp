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
#include "../Combat/CombatUIManager.hpp"
#include "../Maps_WZBJ_Pak.hpp"

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
std::unique_ptr<Entity> character, testEnemy;
BattleManager* battleManager = nullptr;
Map myMap{};

MainMenu::MainMenu()
{
    enSystem = enSystem->getInstance();
    meshSystem = meshSystem->getInstance();
    stateManager = stateManager->GetInstance();

    auto r = std::make_unique<Entity>("ROOT");
    enSystem->rootEntity = r.get();
    AEVec2 pos = { 0.f,0.f };
    AEVec2 scale = { 1.f,1.f };
    enSystem->rootEntity->addComponent<Transform2D>(pos, scale, 0.f);
    enSystem->entities.push_back(std::move(r));

    auto manager = std::make_unique<Entity>("Manager");
    manager->addComponent<Transform2D>(pos, scale, 0.f);
    manager->addComponent<BattleManager>();
    manager->addComponent<CombatUIManager>();
    enSystem->entities.push_back(std::move(manager));

    auto background = std::make_unique<Entity>("BackgroundIMG");
    pos = { 0.f,0.f };
    scale = {1600, 900.f };
    background->addComponent<Transform2D>(pos, scale, 0.f);
    background->addComponent<Mesh>("Box", Color(100, 100, 100, 1), 100, MeshType::BOX_B);
    enSystem->rootEntity->transform->AddChild(background->transform);
    enSystem->entities.push_back(std::move(background));

    character = std::make_unique<Entity>("Guy");
    pos = { -500.f, -300.f };
    scale = { 50.f, 100.f };
    character->addComponent<Transform2D>(pos, scale, 0.f);
    character->addComponent<Character>();
    character->addComponent<Mesh>("Box", Color(0, 255, 0, 1), 100, MeshType::BOX_B);
    character->getComponent<Character>()->LoadCharacter(jsonSerializer, "Assets/Characters/Guy.json");
    enSystem->rootEntity->transform->AddChild(character->transform);
    enSystem->entities.push_back(std::move(character));

    testEnemy = std::make_unique<Entity>("Enemy");
    pos = { 500.f, 300.f };
    scale = { 50.f, 100.f };
    testEnemy->addComponent<Transform2D>(pos, scale, 0.f);
    testEnemy->addComponent<Character>();
    testEnemy->addComponent<Mesh>("Box", Color(255, 0, 0, 1), 100, MeshType::BOX_B);
    Character* ch = testEnemy->getComponent<Character>();
    ch->LoadCharacter(jsonSerializer, "Assets/Characters/Guy.json");
    ch->SetName("Enemy");
    ch->SetFaction(Game::FACTION::ENEMY);
    enSystem->rootEntity->transform->AddChild(testEnemy->transform);
    enSystem->entities.push_back(std::move(testEnemy));
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
void MainMenu::Load()
{
	InitModifierDatabase(jsonSerializer, "Assets/Moves/modifiers-list.json");
	Move::InitMoveDatabase(jsonSerializer, "Assets/Moves/moves-list.json");

    battleManager = BattleManager::instance;
    battleManager->LoadBattleUnit(enSystem->FindByNameGLOBAL("Guy")->getComponent<Character>());
    battleManager->LoadBattleUnit(enSystem->FindByNameGLOBAL("Enemy")->getComponent<Character>());
    battleManager->StartBattle();

    //Map myMap = Map::GenerateMap(CityStreets, 5, 5);
    Map myMap;
    Map::LoadMap(myMap, jsonSerializer, "Assets/Map/testmap.json");
    //Map::SaveMap(myMap, jsonSerializer, "Assets/Map/testmap.json");
}

/*!
@brief Clears splash screen variables

Overwrites virtual GameState::Exit().
This function frees splash screen image used.

@param void
@return void
*//*______________________________________________________________*/
void MainMenu::Unload()
{

}