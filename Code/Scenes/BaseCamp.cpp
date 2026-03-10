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

	float collidersize = 100.f;

	enSystem = &EntityManager::getInstance();
	auto r = std::make_unique<Entity>("ROOT");
	enSystem->rootEntity = r.get();
	AEVec2 pos = { 0.f,0.f };
	AEVec2 scale = { 1.f, 1.f };
	enSystem->rootEntity->addComponent<Transform2D>(pos, scale, 0.f);
	enSystem->entities.push_back(std::move(r));

	meshSystem->CreateTexture("../../Assets/Images/base_camp.png", "BC_BG");
	auto bg = std::make_unique<Entity>("Background");
	pos = { 0.f, 0.f };
	scale = { (float)AEGfxGetWindowWidth(), (float)AEGfxGetWindowHeight() };
	bg->addComponent<Transform2D>(pos, scale, 0.f);
	bg->addComponent<Mesh>("Box", "BC_BG", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);
	enSystem->rootEntity->transform->AddChild(bg->transform);
	enSystem->entities.push_back(std::move(bg));


	pos = { 0.f, 0.f };
	scale = { 1.f, 1.f };
	auto decisionBoxManager = std::make_unique<Entity>("DecisionBoxManager");
	decisionBoxManager->addComponent<Transform2D>(pos, scale, 0.f);
	decisionBoxManager->addComponent<DecisionBoxManager>();
	enSystem->rootEntity->transform->AddChild(decisionBoxManager->transform);
	pos = { 0.f, 0.f };
	scale = { AEGfxGetWindowWidth() * 0.8f, AEGfxGetWindowHeight() * 0.8f };
	auto decisionBox = std::make_unique<Entity>("DecisionBox");
	decisionBox->addComponent<Transform2D>(pos, scale, 0.f);
	decisionBox->addComponent<Mesh>("Box", Color(155, 155, 155, 0.5f), 200, MeshType::BOX_B);
	decisionBox->addComponent<TextMesh>(pos, 1.5, "wehwehwehweh", Color(255, 255, 255, 1.f));
	decisionBox->isActive = false;
	decisionBoxManager->transform->AddChild(decisionBox->transform);
	pos = { -AEGfxGetWindowWidth() * 0.2f, -AEGfxGetWindowHeight() * 0.3f};
	scale = { AEGfxGetWindowWidth() * 0.3f, AEGfxGetWindowHeight() * 0.1f };
	auto decisionButtonLeft = std::make_unique<Entity>("DecisionButtonLeft");
	decisionButtonLeft->addComponent<Transform2D>(pos, scale, 0.f);
	decisionButtonLeft->addComponent<Mesh>("Box", Color(255, 255, 55, 1.f), 201, MeshType::BOX_B);
	Button* leftButton = decisionButtonLeft->addComponent<Button>();
	leftButton->SetNormalColor(Color{ 55, 255, 55, 1.f });
	leftButton->SetHighlightedColor(Color{ 155, 255, 155, 1.f });
	//decisionButtonLeft->addComponent<TextMesh>(pos, 1.5, "Test", Color(255, 255, 255, 1.f));
	decisionButtonLeft->isActive = false;
	decisionBoxManager->transform->AddChild(decisionButtonLeft->transform);
	pos = { AEGfxGetWindowWidth() * 0.2f, -AEGfxGetWindowHeight() * 0.3f };
	scale = { AEGfxGetWindowWidth() * 0.3f, AEGfxGetWindowHeight() * 0.1f };
	auto decisionButtonRight = std::make_unique<Entity>("DecisionButtonRight");
	decisionButtonRight->addComponent<Transform2D>(pos, scale, 0.f);
	decisionButtonRight->addComponent<Mesh>("Box", Color(255, 255, 255, 1.f), 201, MeshType::BOX_B);
	Button* rightButton = decisionButtonRight->addComponent<Button>();
	rightButton->SetNormalColor(Color{ 255, 55, 55, 1.f });
	rightButton->SetHighlightedColor(Color{ 255, 155, 155, 1.f });
	decisionButtonRight->isActive = false;
	decisionBoxManager->transform->AddChild(decisionButtonRight->transform);

	meshSystem->CreateTexture("../../Assets/Images/barracks.png", "barracks");
	auto PartyManager = std::make_unique<Entity>("PartyManager");
	pos = { 300.f, 100.f };
	scale = { 200.f, 200.f };
	PartyManager->addComponent<Transform2D>(pos, scale, 0.f);
	PartyManager->addComponent<Mesh>("Box", "barracks", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);
	PartyManager->addComponent<BoxCollider2D>(scale.x / 2, scale.y / 2);
	PartyManager->addComponent<PartyManagerObject>(decisionBoxManager.get()->getComponent<DecisionBoxManager>());
	enSystem->rootEntity->transform->AddChild(PartyManager->transform);
	enSystem->entities.push_back(std::move(PartyManager));
	enSystem->entities.push_back(std::move(decisionBox));
	enSystem->entities.push_back(std::move(decisionBoxManager));
	enSystem->entities.push_back(std::move(decisionButtonLeft));
	enSystem->entities.push_back(std::move(decisionButtonRight));

	meshSystem->CreateTexture("Assets/UI/shop-back.png", "ShopBGTexture");
	auto shopBackground = std::make_unique<Entity>("ShopBG");
	pos = { 0.f, 0.f };
	scale = { static_cast<float>(AEGfxGetWindowWidth()), static_cast<float>(AEGfxGetWindowHeight()) };
	shopBackground->addComponent<Transform2D>(pos, scale, 0.f);
	shopBackground->addComponent<Mesh>("Box", "ShopBGTexture", Color(255, 255, 255, 1.f), 200, MeshType::BOX_T);
	shopBackground->isActive = false;

	meshSystem->CreateTexture("../../Assets/Images/shop.png", "shop");
	auto shop = std::make_unique<Entity>("Shop");
	pos = { -300.f, 100.f };
	scale = { 200.f, 200.f };
	shop->addComponent<Transform2D>(pos, scale, 0.f);
	shop->addComponent<Mesh>("Box", "shop", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);
	shop->addComponent<BoxCollider2D>(scale.x / 2, scale.y / 2);
	shop->addComponent<Shop>(shopBackground.get());
	enSystem->rootEntity->transform->AddChild(shop->transform);
	enSystem->entities.push_back(std::move(shopBackground));
	enSystem->entities.push_back(std::move(shop));

	meshSystem->CreateTexture("../../Assets/Images/GuanShiYinBack.png", "player_sprite");
	auto e = std::make_unique<Entity>("Player");
	pos = { 0.f, -200.f };
	scale = { 100.f, 100.f };
	e->addComponent<Transform2D>(pos, scale, 0.f);
	e->addComponent<Player>();
	e->addComponent<Mesh>("Box", "player_sprite", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);
	e->addComponent<BoxCollider2D>(scale.x/2, scale.y/2);
	enSystem->rootEntity->transform->AddChild(e->transform);
	enSystem->entities.push_back(std::move(e));

	auto ts = std::make_unique<Entity>("TransitionScreen");
	pos = { 0.f, 0.f };
	scale = { (float)AEGfxGetWindowWidth(), (float)AEGfxGetWindowHeight() };
	ts->addComponent<Transform2D>(pos, scale, 0.f);
	ts->addComponent<Mesh>("Box", Color(20, 20, 20, 1), 101, MeshType::BOX_B);
	ts->addComponent<TransitionScreen>(T_State::T_OUT);
	enSystem->rootEntity->transform->AddChild(ts->transform);
	enSystem->entities.push_back(std::move(ts));

	auto baseExit = std::make_unique<Entity>("baseExit");
	scale = { (float)AEGfxGetWindowWidth(), collidersize };
	pos = { 0.f, scale.y / 2 - (float)AEGfxGetWindowHeight() / 2 };
	baseExit->addComponent<Transform2D>(pos, scale, 0.f);
	baseExit->addComponent<Mesh>("Box", Color(255, 255, 255, 0.3), 100, MeshType::BOX_B);
	baseExit->addComponent<BoxCollider2D>(scale.x / 2, scale.y / 2);
	baseExit->addComponent<SceneEdge>();
	enSystem->rootEntity->transform->AddChild(baseExit->transform);
	enSystem->entities.push_back(std::move(baseExit));

	auto SE_Manager = std::make_unique<Entity>("SceneEdgeManager");
	SE_Manager->addComponent<EdgeManagerBase>();
	enSystem->entities.push_back(std::move(SE_Manager));
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
