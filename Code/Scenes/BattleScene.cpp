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
#include "../Code/SoloBehavior/TransitionScreen.hpp"



std::unique_ptr<Entity> character;

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
    JSONSerializer jsonSerializer{};
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

    meshSystem->CreateTexture("Assets/Images/GuanShiYinBack.png", "CharacterBack");
    character = std::make_unique<Entity>("CharacterBack");
    pos = { -500.f, -150.f };
    scale = { static_cast<float>(AEGfxGetWindowWidth() / 2.f), static_cast<float>(AEGfxGetWindowHeight()) };
    character->addComponent<Transform2D>(pos, scale, 0.f);
    character->addComponent<Character>();
    character->addComponent<Mesh>("Box", "CharacterBack", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);
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


    // UI
    meshSystem->CreateTexture("Assets/UI/MainHP.png", "MainHP");
    auto UI_MainHealthbar = std::make_unique<Entity>("MainHealthbar");
    pos = { 0.f, 0.f };
    scale = { static_cast<float>(AEGfxGetWindowWidth()), static_cast<float>(AEGfxGetWindowHeight())};
    UI_MainHealthbar->addComponent<Transform2D>(pos, scale, 0.f);
    UI_MainHealthbar->addComponent<Mesh>("Box", "MainHP", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);
    enSystem->rootEntity->transform->AddChild(UI_MainHealthbar->transform);
    enSystem->entities.push_back(std::move(UI_MainHealthbar));

    meshSystem->CreateTexture("Assets/UI/Bottom1.png", "Bottom1");
    auto UI_Bottom1 = std::make_unique<Entity>("Bottom1");
    pos = { 0.f, 0.f };
    scale = { static_cast<float>(AEGfxGetWindowWidth()), static_cast<float>(AEGfxGetWindowHeight()) };
    UI_Bottom1->addComponent<Transform2D>(pos, scale, 0.f);
    UI_Bottom1->addComponent<Mesh>("Box", "Bottom1", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);
    enSystem->rootEntity->transform->AddChild(UI_Bottom1->transform);
    enSystem->entities.push_back(std::move(UI_Bottom1));

    meshSystem->CreateTexture("Assets/UI/Bottom2.png", "Bottom2");
    auto UI_Bottom2 = std::make_unique<Entity>("Bottom2");
    pos = { 0.f, 0.f };
    scale = { static_cast<float>(AEGfxGetWindowWidth()), static_cast<float>(AEGfxGetWindowHeight()) };
    UI_Bottom2->addComponent<Transform2D>(pos, scale, 0.f);
    UI_Bottom2->addComponent<Mesh>("Box", "Bottom2", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);
    enSystem->rootEntity->transform->AddChild(UI_Bottom2->transform);
    enSystem->entities.push_back(std::move(UI_Bottom2));

    meshSystem->CreateTexture("Assets/UI/Bottom3.png", "Bottom3");
    auto UI_Bottom3 = std::make_unique<Entity>("Bottom3");
    pos = { 0.f, 0.f };
    scale = { static_cast<float>(AEGfxGetWindowWidth()), static_cast<float>(AEGfxGetWindowHeight()) };
    UI_Bottom3->addComponent<Transform2D>(pos, scale, 0.f);
    UI_Bottom3->addComponent<Mesh>("Box", "Bottom3", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);
    enSystem->rootEntity->transform->AddChild(UI_Bottom3->transform);
    enSystem->entities.push_back(std::move(UI_Bottom3));

    auto test = std::make_unique<AttributeBlessing>(BLESSING_ID::MINOR_ATK_BUFF, "Test", "Test", BLESSING_RARITY::COMMON,
        nullptr, Game::ATK, 90.15f);
    RunManager::Instance().AddBlessing(std::move(test));
    //Parameter is BOSS if player is in Boss Node
    GenerateEnemies(RunManager::Instance().GetBattleType());

    //ONLY CALL ONCE, TO-DO
	InitModifierDatabase(jsonSerializer, "Assets/Moves/modifiers-list.json");
	Move::InitMoveDatabase(jsonSerializer, "Assets/Moves/moves-list.json");

    battleManager->LoadBattleUnit(enSystem->FindByNameGLOBAL("CharacterBack")->getComponent<Character>());
    battleManager->StartBattle();
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
            character = std::make_unique<Entity>("Melee_Boss");
            AEVec2 pos = enemyPositions[0];
            AEVec2 scale = { 50.f, 100.f };
            character->addComponent<Transform2D>(pos, scale, 0.f);
            character->addComponent<Character>();
            character->addComponent<Mesh>("Box", Color(255, 0, 0, 1), 100, MeshType::BOX_B);
            character->addComponent<Healthbar1>();
            Character* ch = character->getComponent<Character>();

            ch->LoadCharacter(jsonSerializer, "Assets/Characters/Melee_Boss.json");
            battleManager->LoadBattleUnit(ch);
            enSystem->rootEntity->transform->AddChild(character->transform);
            enSystem->entities.push_back(std::move(character));
            break;
        }
    }
}