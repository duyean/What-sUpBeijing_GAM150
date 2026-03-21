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
#include "../Code/SoloBehavior/MainHealthbar.hpp"
#include "../SoloBehavior/PartyUI.hpp"
#include "../SoloBehavior/MovesUI.hpp"
#include "../UI_WZBJ_Pak.hpp"


std::unique_ptr<Entity> character;
//Map myMap{};

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
    //FOR DEBUG, TO REMOVE LATER!!!!
    InitBlessingDatabase();

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
    background->addComponent<Mesh>("Box", Color(20, 20, 20, 1), 100, MeshType::BOX_B);
    enSystem->rootEntity->transform->AddChild(background->transform);
    enSystem->entities.push_back(std::move(background));
 
    auto partyUI = std::make_unique<Entity>("PartyUISystem");
    pos = { 0.f, 0.f };
    scale = { 0.f, 0.f };
    partyUI->addComponent<Transform2D>(pos, scale, 0.f);
    auto pUI = partyUI->addComponent<PartyUI>();
    enSystem->rootEntity->transform->AddChild(partyUI->transform);
    enSystem->entities.push_back(std::move(partyUI));

    int count = 0;
    for (const auto& str : RunManager::Instance().GetParty())
    {
        character = std::make_unique<Entity>(str.c_str());
        pos = { -500.f, -150.f };
        scale = { static_cast<float>(AEGfxGetWindowWidth() / 2.f), static_cast<float>(AEGfxGetWindowHeight()) };
        character->addComponent<Transform2D>(pos, scale, 0.f);
        auto ch = character->addComponent<Character>();
        std::string charDataPath = "Assets/Characters/" + str + ".json";
        character->getComponent<Character>()->LoadCharacter(jsonSerializer, charDataPath.c_str());
        std::string texturePath = "Assets/Images/" + ch->characterModelTexture;
        std::string texturePath2 = "Assets/Images/" + ch->characterModelTexture2;
        std::string iconPath = "Assets/Images/" + ch->characterIconTexture;
        meshSystem->CreateTexture(texturePath.c_str(), ch->characterModelTexture.c_str());
        meshSystem->CreateTexture(texturePath2.c_str(), ch->characterModelTexture2.c_str());
        meshSystem->CreateTexture(iconPath.c_str(), ch->characterIconTexture.c_str());
        character->addComponent<Mesh>("Box", ch->characterModelTexture.c_str(), Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);
        character->getComponent<Mesh>()->isActive = false;
        battleManager->LoadBattleUnit(ch);
        enSystem->rootEntity->transform->AddChild(character->transform);
        enSystem->entities.push_back(std::move(character));

        //Create the Party UI Icons
        auto PartyUnitIcon1 = std::make_unique<Entity>("Icon");
        pos = { 60.f + (count * 250), -AEGfxGetWindowHeight() * 0.7f * 0.5f};
        scale = { 100, 100 };
        PartyUnitIcon1->addComponent<Transform2D>(pos, scale, 0.f);
        PartyUnitIcon1->addComponent<Mesh>("Box", ch->characterIconTexture.c_str(), Color(255, 255, 255, 1.f), 103, MeshType::BOX_T);
        pUI->AddIcon(PartyUnitIcon1.get());
        enSystem->rootEntity->transform->AddChild(PartyUnitIcon1->transform);
        enSystem->entities.push_back(std::move(PartyUnitIcon1));

        //Create Party UI Health
        auto partyUIHealthBar = std::make_unique<Entity>("PartyUIHealth");
        float angle = 0;
        float posX = 0;
        switch (count)
        {
        case 0:
            angle = 9.5;
            posX = -40;
            break;
        case 1:
            angle = -15.0f;
            posX = 260;
            break;
        case 2:
            angle = 11.5f;
            posX = 440;
            break;
        }
        pos = { posX, (-AEGfxGetWindowHeight() * 0.5f) - ((count == 2) ? 5.f : 0.f)};
        scale = { 210, 210 };
        partyUIHealthBar->addComponent<Transform2D>(pos, scale, 90 - angle);
        partyUIHealthBar->addComponent<Mesh>("Box", Color(0, 255, 255, 1.f), 101, MeshType::BOX_BL);
        pUI->AddHealthBarEntity(partyUIHealthBar.get());
        enSystem->rootEntity->transform->AddChild(partyUIHealthBar->transform);
        enSystem->entities.push_back(std::move(partyUIHealthBar));

        //Create 3 modifier icons for each party
            //Create enemy status icons
        for (int i = 0; i < 3; ++i)
        {
            auto characterIcon = std::make_unique<Entity>("StatusIcon");
            scale = { 30, 30 };
            pos = { 0, 0 };
            characterIcon->addComponent<Transform2D>(pos, scale, 0);
            characterIcon->addComponent<Mesh>("Box", Color(255, 255, 255, 1.f), 103, MeshType::BOX_T);
            pUI->AddModifierIcon(count, characterIcon.get());
            enSystem->rootEntity->transform->AddChild(characterIcon->transform);
            enSystem->entities.push_back(std::move(characterIcon));
        }
        count++;
    }

    //Parameter is BOSS if player is in Boss Node
    GenerateEnemies(RunManager::Instance().GetBattleType());

    // UI
    meshSystem->CreateTexture("Assets/UI/MainHP.png", "MainHP");
    auto UI_MainHealthbar = std::make_unique<Entity>("MainHealthbar");
    pos = { 0.f, 0.f };
    scale = { static_cast<float>(AEGfxGetWindowWidth()), static_cast<float>(AEGfxGetWindowHeight())};
    UI_MainHealthbar->addComponent<Transform2D>(pos, scale, 0.f);
    UI_MainHealthbar->addComponent<Mesh>("Box", "MainHP", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);
    enSystem->rootEntity->transform->AddChild(UI_MainHealthbar->transform);
    enSystem->entities.push_back(std::move(UI_MainHealthbar));

    auto mainUnitHealthBar = std::make_unique<Entity>("HealthBar");
    pos = { -0.8f * AEGfxGetWindowWidth() / 2, 0.9f * AEGfxGetWindowHeight() / 2 };
    scale = { 300, 12 };
    mainUnitHealthBar->addComponent<Transform2D>(pos, scale, 0.f);
    mainUnitHealthBar->addComponent<Mesh>("Box", Color(255, 255, 255, 1.f), 102, MeshType::BOX_BL);
    mainUnitHealthBar->addComponent<MainHealthbar>();
    enSystem->rootEntity->transform->AddChild(mainUnitHealthBar->transform);
    enSystem->entities.push_back(std::move(mainUnitHealthBar));

    auto mainUnitHealthBarBG = std::make_unique<Entity>("HealthBarBG");
    pos = { -0.8f * AEGfxGetWindowWidth() / 2, 0.9f * AEGfxGetWindowHeight() / 2 };
    scale = { 300, 12 };
    mainUnitHealthBarBG->addComponent<Transform2D>(pos, scale, 0.f);
    mainUnitHealthBarBG->addComponent<Mesh>("Box", Color(122, 0, 0, 1.f), 101, MeshType::BOX_BL);
    enSystem->rootEntity->transform->AddChild(mainUnitHealthBarBG->transform);
    enSystem->entities.push_back(std::move(mainUnitHealthBarBG));

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
    UI_Bottom2->addComponent<Mesh>("Box", "Bottom2", Color(255, 255, 255, 1.f), 102, MeshType::BOX_T);
    enSystem->rootEntity->transform->AddChild(UI_Bottom2->transform);
    enSystem->entities.push_back(std::move(UI_Bottom2));

    meshSystem->CreateTexture("Assets/UI/Bottom3.png", "Bottom3");
    auto UI_Bottom3 = std::make_unique<Entity>("Bottom3");
    pos = { 0.f, 0.f };
    scale = { static_cast<float>(AEGfxGetWindowWidth()), static_cast<float>(AEGfxGetWindowHeight()) };
    UI_Bottom3->addComponent<Transform2D>(pos, scale, 0.f);
    UI_Bottom3->addComponent<Mesh>("Box", "Bottom3", Color(255, 255, 255, 1.f), 102, MeshType::BOX_T);
    enSystem->rootEntity->transform->AddChild(UI_Bottom3->transform);
    enSystem->entities.push_back(std::move(UI_Bottom3));


    auto moveui = std::make_unique<Entity>("MovesUI");
    pos = { 0.f, 0.f };
    scale = { 0.f, 0.f };
    moveui->addComponent<Transform2D>(pos, scale, 0.f);
    moveui->addComponent<MovesUI>();
    enSystem->rootEntity->transform->AddChild(moveui->transform);
    enSystem->entities.push_back(std::move(moveui));

    //load the button textures
    meshSystem->CreateTexture("../../Assets/UI/button_border_2.png", "moveButton");
    ////////////////////////////////////////////////
    // 
    // MOVE BUTTON 1
    //
    ////////////////////////////////////////////////

    auto mb1 = std::make_unique<Entity>("MOVEBUTTON1");
    pos = { -550.f,-200.f };
    scale = { 400.f, 50.f };
    mb1->addComponent<Transform2D>(pos, scale, 0.f);
    mb1->addComponent<Mesh>("Box", "moveButton", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);
    mb1->addComponent<TextBox>("move", 0.6f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);
    Button* moveButton1 = mb1->addComponent<Button>();
    moveButton1->SetNormalColor(Color{ 200,200,200,1 });
    moveButton1->SetHighlightedColor(Color{ 255,255,255,1 });
    enSystem->rootEntity->transform->AddChild(mb1->transform);
    enSystem->entities.push_back(std::move(mb1));


    ////////////////////////////////////////////////
    // 
    // MOVE BUTTON 2
    //
    ////////////////////////////////////////////////

    auto mb2 = std::make_unique<Entity>("MOVEBUTTON2");
    pos = { -550.f,-260.f };
    scale = { 400.f, 50.f };
    mb2->addComponent<Transform2D>(pos, scale, 0.f);
    mb2->addComponent<Mesh>("Box", "moveButton", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);
    mb2->addComponent<TextBox>("move", 0.6f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);
    Button* moveButton2 = mb2->addComponent<Button>();
    moveButton2->SetNormalColor(Color{ 200,200,200,1 });
    moveButton2->SetHighlightedColor(Color{ 255,255,255,1 });
    enSystem->rootEntity->transform->AddChild(mb2->transform);
    enSystem->entities.push_back(std::move(mb2));


    ////////////////////////////////////////////////
    // 
    // MOVE BUTTON 3
    //
    ////////////////////////////////////////////////

    auto mb3 = std::make_unique<Entity>("MOVEBUTTON3");
    pos = { -550.f,-320.f };
    scale = { 400.f, 50.f };
    mb3->addComponent<Transform2D>(pos, scale, 0.f);
    mb3->addComponent<Mesh>("Box", "moveButton", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);
    mb3->addComponent<TextBox>("move", 0.6f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);
    Button* moveButton3 = mb3->addComponent<Button>();
    moveButton3->SetNormalColor(Color{ 200,200,200,1 });
    moveButton3->SetHighlightedColor(Color{ 255,255,255,1 });
    enSystem->rootEntity->transform->AddChild(mb3->transform);
    enSystem->entities.push_back(std::move(mb3));


    ////////////////////////////////////////////////
    // 
    // MOVE BUTTON 4
    //
    ////////////////////////////////////////////////

    auto mb4 = std::make_unique<Entity>("MOVEBUTTON4");
    pos = { -550.f,-380.f };
    scale = { 400.f, 50.f };
    mb4->addComponent<Transform2D>(pos, scale, 0.f);
    mb4->addComponent<Mesh>("Box", "moveButton", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);
    mb4->addComponent<TextBox>("move", 0.6f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);
    Button* moveButton4 = mb4->addComponent<Button>();
    moveButton4->SetNormalColor(Color{ 200,200,200,1 });
    moveButton4->SetHighlightedColor(Color{ 255,255,255,1 });
    enSystem->rootEntity->transform->AddChild(mb4->transform);
    enSystem->entities.push_back(std::move(mb4));


    ////////////////////////////////////////////////
    // 
    // TOOLTIP UI
    //
    ////////////////////////////////////////////////

    auto tt = std::make_unique<Entity>("ToolTipUI");
    pos = { 0.f, 0.f };
    scale = { 400, 200};
    tt->addComponent<Transform2D>(pos, scale, 0.f);
    tt->addComponent<Mesh>("Box", Color(1, 1, 1, 0.8), 501, MeshType::BOX_B);
    TextBox* tt_tb = tt->addComponent<TextBox>("tooltip", 0.6f, TextBoxVAllign::TOP, TextBoxHAllign::LEFT);
    tt_tb->text_layer = 502;
    tt_tb->line_padding = 2.f;
    enSystem->rootEntity->transform->AddChild(tt->transform);
    enSystem->entities.push_back(std::move(tt));

    auto ts = std::make_unique<Entity>("TransitionScreen");
    pos = { 0.f, 0.f };
    scale = { (float)AEGfxGetWindowWidth(), (float)AEGfxGetWindowHeight() };
    ts->addComponent<Transform2D>(pos, scale, 0.f);
    ts->addComponent<Mesh>("Box", Color(20, 20, 20, 1), 999, MeshType::BOX_B);
    ts->addComponent<TransitionScreen>(T_State::T_OUT);
    enSystem->rootEntity->transform->AddChild(ts->transform);
    enSystem->entities.push_back(std::move(ts));

    //Can call this every battle since the function clears the databases 
	InitModifierDatabase(jsonSerializer, "Assets/Moves/modifiers-list.json");
	Move::InitMoveDatabase(jsonSerializer, "Assets/Moves/moves-list.json");

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
    JSONSerializer jsonSerializer{};
    Character* ch = nullptr;
    int enemies = 1;
    AEVec2 pos = {}, scale = { 200, 200 };
    AEVec2 hpBarScale = {};
    if (type == BATTLE_TYPE::NORMAL)
    {
        std::uniform_int_distribution<int> dist(1, 3);
        int enemies = dist(Game::gen);
        for (int i = 0; i < enemies; ++i)
        {
            character = std::make_unique<Entity>("Enemy");
            ch = character->addComponent<Character>();
            hpBarScale = { 200, 10 };
            scale = { 200, 200 };
            pos = enemyPositions[i];
            ch->LoadCharacter(jsonSerializer, "Assets/Characters/Enemy.json");

            //Create the enemy entity
            std::string texturePath = "Assets/Images/" + ch->characterModelTexture;
            std::string texturePath2 = "Assets/Images/" + ch->characterModelTexture2;
            meshSystem->CreateTexture(texturePath.c_str(), ch->characterModelTexture.c_str());
            meshSystem->CreateTexture(texturePath2.c_str(), ch->characterModelTexture2.c_str());
            character->addComponent<Transform2D>(pos, scale, 0.f);
            character->addComponent<Mesh>("Box", ch->characterModelTexture.c_str(), Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);
            auto hpBar = character->addComponent<Healthbar1>();
            battleManager->LoadBattleUnit(ch);
            enSystem->rootEntity->transform->AddChild(character->transform);
            enSystem->entities.push_back(std::move(character));

            //Create enemy HPBar
            auto enemyHP = std::make_unique<Entity>("EnemyHP");
            pos = { 0, 0 }; //HealthBar1 will handle it
            enemyHP->addComponent<Transform2D>(pos, hpBarScale, 0.f);
            enemyHP->addComponent<Mesh>("Box", Color(0, 255, 0, 1.f), 103, MeshType::BOX_BL);
            hpBar->en = enemyHP.get();
            enSystem->rootEntity->transform->AddChild(enemyHP->transform);
            enSystem->entities.push_back(std::move(enemyHP));

            //Create enemy HPBarBG
            auto enemyHPBG = std::make_unique<Entity>("EnemyHPBG");
            pos = { 0, 0 }; //HealthBar1 will handle it
            enemyHPBG->addComponent<Transform2D>(pos, hpBarScale, 0.f);
            enemyHPBG->addComponent<Mesh>("Box", Color(50, 50, 50, 1.f), 102, MeshType::BOX_BL);
            hpBar->hpBarBG = enemyHPBG.get();
            enSystem->rootEntity->transform->AddChild(enemyHPBG->transform);
            enSystem->entities.push_back(std::move(enemyHPBG));

            //Create enemy status icons
            for (int i = 0; i < 3; ++i)
            {
                auto enemyIcon = std::make_unique<Entity>("StatusIcon");
                scale = { 30, 30 };
                pos = { 0, 0 };
                enemyIcon->addComponent<Transform2D>(pos, scale, 0);
                enemyIcon->addComponent<Mesh>("Box", Color(255, 255, 255, 1.f), 102, MeshType::BOX_T);
                hpBar->statusIcons.push_back(enemyIcon.get());
                enSystem->rootEntity->transform->AddChild(enemyIcon->transform);
                enSystem->entities.push_back(std::move(enemyIcon));
            }
        }
    }
    else
    {
        character = std::make_unique<Entity>("Enemy");
        ch = character->addComponent<Character>();
        switch (type)
        {
            case (BATTLE_TYPE::MINI_BOSS):
            {
                hpBarScale = { 250, 10 };
                pos = enemyPositions[0];
                ch->LoadCharacter(jsonSerializer, "Assets/Characters/MiniBoss1.json");
                break;
            }
            case (BATTLE_TYPE::BOSS):
            {
                hpBarScale = { 350, 10 };
                pos = enemyPositions[0];
                ch->LoadCharacter(jsonSerializer, "Assets/Characters/Boss1.json");
                break;
            }
        }
        //Create the enemy entity
        std::string texturePath = "Assets/Images/" + ch->characterModelTexture;
        std::string texturePath2 = "Assets/Images/" + ch->characterModelTexture2;
        meshSystem->CreateTexture(texturePath.c_str(), ch->characterModelTexture.c_str());
        meshSystem->CreateTexture(texturePath2.c_str(), ch->characterModelTexture2.c_str());
        character->addComponent<Transform2D>(pos, scale, 0.f);
        character->addComponent<Mesh>("Box", ch->characterModelTexture.c_str(), Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);
        auto hpBar = character->addComponent<Healthbar1>();
        battleManager->LoadBattleUnit(ch);
        enSystem->rootEntity->transform->AddChild(character->transform);
        enSystem->entities.push_back(std::move(character));

        //Create enemy HPBar
        auto enemyHP = std::make_unique<Entity>("EnemyHP");
        pos = { 0, 0 }; //HealthBar1 will handle it
        enemyHP->addComponent<Transform2D>(pos, hpBarScale, 0.f);
        enemyHP->addComponent<Mesh>("Box", Color(0, 255, 0, 1.f), 103, MeshType::BOX_BL);
        hpBar->en = enemyHP.get();
        enSystem->rootEntity->transform->AddChild(enemyHP->transform);
        enSystem->entities.push_back(std::move(enemyHP));

        //Create enemy HPBarBG
        auto enemyHPBG = std::make_unique<Entity>("EnemyHPBG");
        pos = { 0, 0 }; //HealthBar1 will handle it
        enemyHPBG->addComponent<Transform2D>(pos, hpBarScale, 0.f);
        enemyHPBG->addComponent<Mesh>("Box", Color(50, 50, 50, 1.f), 102, MeshType::BOX_BL);
        hpBar->hpBarBG = enemyHPBG.get();
        enSystem->rootEntity->transform->AddChild(enemyHPBG->transform);
        enSystem->entities.push_back(std::move(enemyHPBG));

        //Create enemy status icons
        for (int i = 0; i < 3; ++i)
        {
            auto enemyIcon = std::make_unique<Entity>("StatusIcon");
            scale = { 30, 30 };
            pos = { 0, 0 };
            enemyIcon->addComponent<Transform2D>(pos, scale, 0);
            enemyIcon->addComponent<Mesh>("Box", Color(255, 255, 255, 1.f), 102, MeshType::BOX_T);
            hpBar->statusIcons.push_back(enemyIcon.get());
            enSystem->rootEntity->transform->AddChild(enemyIcon->transform);
            enSystem->entities.push_back(std::move(enemyIcon));
        }
    }
}