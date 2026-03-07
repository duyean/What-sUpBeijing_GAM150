/*!
@file BattleScene.cpp
@author Tai Qian Yi (t.qianyi)
@course CSD11451
@section B
@Final Project
@date 13/1/26
@brief
This file contains the definitions for the collection of functions in BattleScene.hpp
*//*______________________________________________________________________*/
#include "BattleScene.hpp"

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
#include "../Code/SoloBehavior/RunManager.hpp"


JSONSerializer jsonSerializer{};
std::unique_ptr<Entity> character;
Map myMap{};

BattleScene::BattleScene()
{
    
}

BattleScene::~BattleScene()
{
}

/*!
@brief Initialize splash screen variables

Overwrites virtual GameState::Init().
This function loads splash screen image

@param void
@return void
*//*______________________________________________________________*/
void BattleScene::Load()
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
    manager->addComponent<CombatUIManager>();
    battleManager = manager->addComponent<BattleManager>();
    manager->addComponent<AudioManager>();
    enSystem->rootEntity->transform->AddChild(manager->transform);
    enSystem->entities.push_back(std::move(manager));

    auto background = std::make_unique<Entity>("BattleBackgroundIMG");
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

    /* To do, shift the above code block into a for loop
    *     
    for (Character* ch : RunManager::Instance().GetParty())
    {
        battleManager->LoadBattleUnit(enSystem->FindByNameGLOBAL("Guy")->getComponent<Character>());
    }
    */


    //Parameter is BOSS if player is in Boss Node
    GenerateEnemies();

    //ONLY CALL ONCE, TO-DO
	InitModifierDatabase(jsonSerializer, "Assets/Moves/modifiers-list.json");
	Move::InitMoveDatabase(jsonSerializer, "Assets/Moves/moves-list.json");

    battleManager->LoadBattleUnit(enSystem->FindByNameGLOBAL("Guy")->getComponent<Character>());
    battleManager->StartBattle();

    //Map myMap = Map::GenerateMap(CityStreets, 5, 5);
    myMap.LoadMap(jsonSerializer, "Assets/Map/testmap.json");
    //Map::SaveMap(myMap, jsonSerializer, "Assets/Map/testmap.json");
}

/*!
@brief Clears splash screen variables

Overwrites virtual GameState::Exit().
This function frees splash screen image used.

@param void
@return void
*//*______________________________________________________________*/
void BattleScene::Unload()
{
    EntityManager::getInstance().needsCleanup = true;
    for (auto& e : enSystem->entities) {
        e->toDestroy = true;
    }
}

void BattleScene::GenerateEnemies(BATTLE_TYPE type)
{
    switch (type)
    {
        case (BATTLE_TYPE::NORMAL):
        {
            //Generate between 1 to 3 enemies
            std::uniform_int_distribution<int> dist(1, 3);
            int enemies = dist(Game::gen);

            for (int i = 0; i < enemies; ++i)
            {
                character = std::make_unique<Entity>("Enemy");
                AEVec2 pos = enemyPositions[i];
                AEVec2 scale = { 50.f, 100.f };
                character->addComponent<Transform2D>(pos, scale, 0.f);
                character->addComponent<Character>();
                character->addComponent<Mesh>("Box", Color(255, 0, 0, 1), 100, MeshType::BOX_B);
                character->addComponent<Healthbar1>();
                Character* ch = character->getComponent<Character>();
                //Use a switch case and edit the line below for different enemy types
                /*
                ENEMY_TYPE type = dist(0, MAX_ENEMY_TYPE - 1);
                switch (type)
                {
                    ...
                    case (ENEMY_TYPE::MELEE)
                    {
                        ch->LoadCharacter(jsonSerializer, "Assets/Characters/EnemyMelee.json);
                        break;
                    }
                    ...
                }
                */
                ch->LoadCharacter(jsonSerializer, "Assets/Characters/Enemy.json");
                battleManager->LoadBattleUnit(ch);
                enSystem->rootEntity->transform->AddChild(character->transform);
                enSystem->entities.push_back(std::move(character));
            }
            break;
        }
        case (BATTLE_TYPE::BOSS):
        {
            //To-do, Get Boss Type and load boss data
            break;
        }
    }
}