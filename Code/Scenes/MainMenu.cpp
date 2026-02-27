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
#include "../SoloBehavior/HEALTHBAR1.hpp"
#include "../Audio_WZBJ_Pak.hpp"

JSONSerializer jsonSerializer{};
std::unique_ptr<Entity> character, testEnemy, testEnemy2;
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
void MainMenu::Load()
{
    enSystem = &EntityManager::getInstance();
    meshSystem = &MeshGen::getInstance();
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
    manager->addComponent<AudioManager>();
    enSystem->rootEntity->transform->AddChild(manager->transform);
    enSystem->entities.push_back(std::move(manager));

    auto background = std::make_unique<Entity>("BackgroundIMG");
    pos = { 0.f,0.f };
    scale = { 1600, 900.f };
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
    character->addComponent<Healthbar1>();
    enSystem->rootEntity->transform->AddChild(character->transform);
    enSystem->entities.push_back(std::move(character));

    testEnemy = std::make_unique<Entity>("Enemy");
    pos = { 500.f, 300.f };
    scale = { 50.f, 100.f };
    testEnemy->addComponent<Transform2D>(pos, scale, 0.f);
    testEnemy->addComponent<Character>();
    testEnemy->addComponent<Mesh>("Box", Color(255, 0, 0, 1), 100, MeshType::BOX_B);
    testEnemy->addComponent<Healthbar1>();
    Character* ch = testEnemy->getComponent<Character>();
    ch->LoadCharacter(jsonSerializer, "Assets/Characters/Enemy.json");
    enSystem->rootEntity->transform->AddChild(testEnemy->transform);
    enSystem->entities.push_back(std::move(testEnemy));

    testEnemy2 = std::make_unique<Entity>("Enemy2");
    pos = { 550.f, 100.f };
    scale = { 50.f, 100.f };
    testEnemy2->addComponent<Transform2D>(pos, scale, 0.f);
    testEnemy2->addComponent<Character>();
    testEnemy2->addComponent<Mesh>("Box", Color(255, 0, 0, 1), 100, MeshType::BOX_B);
    testEnemy2->addComponent<Healthbar1>();
    ch = testEnemy2->getComponent<Character>();
    ch->LoadCharacter(jsonSerializer, "Assets/Characters/Enemy.json");
    enSystem->rootEntity->transform->AddChild(testEnemy2->transform);
    enSystem->entities.push_back(std::move(testEnemy2));

	InitModifierDatabase(jsonSerializer, "Assets/Moves/modifiers-list.json");
	Move::InitMoveDatabase(jsonSerializer, "Assets/Moves/moves-list.json");

    BattleManager::Instance().LoadBattleUnit(enSystem->FindByNameGLOBAL("Guy")->getComponent<Character>());
    BattleManager::Instance().LoadBattleUnit(enSystem->FindByNameGLOBAL("Enemy")->getComponent<Character>());
    BattleManager::Instance().LoadBattleUnit(enSystem->FindByNameGLOBAL("Enemy2")->getComponent<Character>());
    BattleManager::Instance().StartBattle();

    //Map myMap = Map::GenerateMap(CityStreets, 5, 5);
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