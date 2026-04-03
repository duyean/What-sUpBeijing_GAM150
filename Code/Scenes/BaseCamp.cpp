/*!
@file SplashScreen.cpp
@author Tai Qian Yi (t.qianyi)
@course CSD11451
@section B
@Final Project
@date 13/1/26
@brief
This file contains the definitions for the collection of functions in SplashScreen.h
*//*______________________________________________________________________*/
#include "BaseCamp.hpp"
#include "../Code/SoloBehavior/EdgeManagerBase.hpp"
#include "../Code/SoloBehavior/Shop.hpp"
#include "../Code/SoloBehavior/PartyManagerObject.hpp"
#include "../Code/SoloBehavior/ShopBlessing.hpp"
#include "../Code/UI_WZBJ_Pak.hpp"
#include "../Code/SoloBehavior/RunManager.hpp"
#include "../Code/SoloBehavior/PauseMenu.hpp"
#include "../Code/SoloBehavior/CurrencyDisplay.hpp"
#include "../Audio_WZBJ_Pak.hpp"
#include "../Code/SoloBehavior/TutorialScreen.hpp"
#include "../BaseSystems/Engine/Bounce.hpp"

BaseCamp::BaseCamp()
{	
}

BaseCamp::~BaseCamp()
{
}


/*!
@brief Initialize splash screen variables

Overwrites virtual GameState::Init().
This function loads splash screen image

@param void
@return void
*//*______________________________________________________________*/
void BaseCamp::Load()
{
	meshSystem = &MeshGen::getInstance();

	// Load Meshes for BLESSINGS
	meshSystem->CreateTexture("Assets/UI/Blessings/ATK_Minor.png", "ATK_Minor_Texture");
	meshSystem->CreateTexture("Assets/UI/Blessings/ATK_Major.png", "ATK_Major_Texture");
	meshSystem->CreateTexture("Assets/UI/Blessings/DEF_Minor.png", "DEF_Minor_Texture");
	meshSystem->CreateTexture("Assets/UI/Blessings/DEF_Major.png", "DEF_Major_Texture");
	meshSystem->CreateTexture("Assets/UI/Blessings/HP_Minor.png", "HP_Minor_Texture");
	meshSystem->CreateTexture("Assets/UI/Blessings/HP_Major.png", "HP_Major_Texture");
	meshSystem->CreateTexture("Assets/UI/Blessings/CRITRATE_Minor.png", "CRITRATE_Minor_Texture");
	meshSystem->CreateTexture("Assets/UI/Blessings/CRITRATE_Major.png", "CRITRATE_Major_Texture");
	meshSystem->CreateTexture("Assets/UI/Blessings/CRITDMG_Minor.png", "CRITDMG_Minor_Texture");
	meshSystem->CreateTexture("Assets/UI/Blessings/CRITDMG_Major.png", "CRITDMG_Major_Texture");
	meshSystem->CreateTexture("Assets/UI/Helm.png", "Temp_Texture");
	meshSystem->CreateTexture("Assets/UI/button_border.png", "Button");

	float collidersize = 100.f;

	enSystem = &EntityManager::getInstance();
	auto r = std::make_unique<Entity>("ROOT");
	enSystem->rootEntity = r.get();
	AEVec2 pos = { 0.f,0.f };
	AEVec2 scale = { 1.f, 1.f };
	enSystem->rootEntity->addComponent<Transform2D>(pos, scale, 0.f);
	enSystem->entities.push_back(std::move(r));

	meshSystem->CreateTexture("Assets/Images/SPRITE.png", "player_sprite");
	auto e = std::make_unique<Entity>("Player");
	pos = { 0.f, -200.f };
	scale = { 100.f, 100.f };
	e->addComponent<Transform2D>(pos, scale, 0.f);
	e->addComponent<Player>();
	e->addComponent<Mesh>("Box", "player_sprite", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);
	e->addComponent<BoxCollider2D>(scale.x / 2, scale.y / 2);
	e->addComponent<Bounce>(0.f, 2.f, 0.1f, 0.07f);
	enSystem->rootEntity->transform->AddChild(e->transform);

	/*auto curr_disp = std::make_unique<Entity>("CurrDisp");
	pos = { 0.f, 0.f };
	scale = { 100.f, 100.f };
	curr_disp->addComponent<Transform2D>(pos, scale, 0.f);
	curr_disp->addComponent<CurrencyDisplay>();
	enSystem->rootEntity->transform->AddChild(curr_disp->transform);
	enSystem->entities.push_back(std::move(curr_disp));*/

	meshSystem->CreateTexture("Assets/Images/base_camp.png", "BC_BG");
	auto bg = std::make_unique<Entity>("Background");
	pos = { 0.f, 0.f };
	scale = { (float)AEGfxGetWindowWidth(), (float)AEGfxGetWindowHeight() };
	bg->addComponent<Transform2D>(pos, scale, 0.f);
	bg->addComponent<Mesh>("Box", "BC_BG", Color(255, 255, 255, 1.f), 1, MeshType::BOX_T);
	enSystem->rootEntity->transform->AddChild(bg->transform);
	enSystem->entities.push_back(std::move(bg));

	meshSystem->CreateTexture("Assets/Images/shop.png", "shop");
	auto shop = std::make_unique<Entity>("Shop");
	pos = { -300.f, 100.f };
	scale = { 200.f, 200.f };
	shop->addComponent<Transform2D>(pos, scale, 0.f);
	shop->addComponent<Mesh>("Box", "shop", Color(255, 255, 255, 1), 100, MeshType::BOX_T);
	shop->addComponent<BoxCollider2D>(scale.x / 2, scale.y / 2);
	Shop* s = shop->addComponent<Shop>();
	s->SetPlayer(e.get());
	enSystem->rootEntity->transform->AddChild(shop->transform);
	enSystem->entities.push_back(std::move(shop));
	enSystem->entities.push_back(std::move(e));

	auto ps = std::make_unique<Entity>("PauseScreen");
	pos = { 0.f, 0.f };
	scale = { (float)AEGfxGetWindowWidth(), (float)AEGfxGetWindowHeight() };
	ps->addComponent<Transform2D>(pos, scale, 0.f);
	ps->addComponent<PauseMenu>();
	enSystem->rootEntity->transform->AddChild(ps->transform);
	enSystem->entities.push_back(std::move(ps));

	if (RunManager::Instance().firstTimeBase)
	{
		auto tut_s = std::make_unique<Entity>("TutorialScreen");
		pos = { 0.f, 0.f };
		scale = { 1.f, 1.f };
		tut_s->addComponent<Transform2D>(pos, scale, 0.f);
		tut_s->addComponent<TutorialScreen>(TutorialScreen::TUTORIAL_TYPE::TUTORIAL_BASE_CAMP);
		enSystem->rootEntity->transform->AddChild(tut_s->transform);
		enSystem->entities.push_back(std::move(tut_s));
		
		RunManager::Instance().firstTimeBase = false;
	}

	auto ts = std::make_unique<Entity>("TransitionScreen");
	pos = { 0.f, 0.f };
	scale = { (float)AEGfxGetWindowWidth(), (float)AEGfxGetWindowHeight() };
	ts->addComponent<Transform2D>(pos, scale, 0.f);
	ts->addComponent<Mesh>("Box", Color(20, 20, 20, 1), 999, MeshType::BOX_B);
	ts->addComponent<TransitionScreen>(T_State::T_OUT);
	enSystem->rootEntity->transform->AddChild(ts->transform);
	enSystem->entities.push_back(std::move(ts));

	meshSystem->CreateTexture("Assets/UI/PathArrow.png", "path_arrow_sprite");
	auto baseExit = std::make_unique<Entity>("baseExit");
	scale = { (float)AEGfxGetWindowWidth(), collidersize };
	pos = { 0.f, scale.y / 2 - (float)AEGfxGetWindowHeight() / 2 };
	baseExit->addComponent<Transform2D>(pos, scale, 0.f);
	//baseExit->addComponent<Mesh>("Box", Color(255, 255, 255, 0.3), 100, MeshType::BOX_B);
	baseExit->addComponent<BoxCollider2D>(scale.x / 2, scale.y / 2);
	baseExit->addComponent<SceneEdge>();
	enSystem->rootEntity->transform->AddChild(baseExit->transform);

	auto baseExit_sprite = std::make_unique<Entity>("S_Path_sprite");
	scale = { 0.05f, 0.5f }; pos = { 0.f, 0.f };
	baseExit_sprite->addComponent<Transform2D>(pos, scale, 180.f);
	baseExit_sprite->addComponent<Mesh>("Box", "path_arrow_sprite", Color(50, 50, 50, 1.f), 102, MeshType::BOX_T);
	baseExit->transform->AddChild(baseExit_sprite->transform);

	enSystem->entities.push_back(std::move(baseExit));
	enSystem->entities.push_back(std::move(baseExit_sprite));

	
	auto SE_Manager = std::make_unique<Entity>("SceneEdgeManager");
	SE_Manager->addComponent<EdgeManagerBase>();
	pos = { 0.f, 0.f }; scale = { 1.f, 1.f };
	SE_Manager->addComponent<Transform2D>(pos, scale, 0.f);
	enSystem->entities.push_back(std::move(SE_Manager));

	RunManager::Instance().game_paused = false;

	AudioManager::GetInstance()->StopAllTracks(true, AudioManager::AUDIO_BASECAMP_BGM);
	AudioManager::GetInstance()->PlayTrack(AudioManager::AUDIO_BASECAMP_BGM, true);
}


/*!
@brief Clears splash screen variables

Overwrites virtual GameState::Exit().
This function frees splash screen image used.

@param void
@return void
*//*______________________________________________________________*/
void BaseCamp::Unload()
{
	EntityManager::getInstance().needsCleanup = true;
	for (auto& e : enSystem->entities) {
		e->toDestroy = true;
	}
}
