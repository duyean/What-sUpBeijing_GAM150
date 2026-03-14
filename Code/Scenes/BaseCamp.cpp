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

void BaseCamp::PurchaseBlessing(BLESSING_ID id)
{
}

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

	float collidersize = 100.f;

	enSystem = &EntityManager::getInstance();
	auto r = std::make_unique<Entity>("ROOT");
	enSystem->rootEntity = r.get();
	AEVec2 pos = { 0.f,0.f };
	AEVec2 scale = { 1.f, 1.f };
	enSystem->rootEntity->addComponent<Transform2D>(pos, scale, 0.f);
	enSystem->entities.push_back(std::move(r));

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
	Button* leftDecButton = decisionButtonLeft->addComponent<Button>();
	leftDecButton->SetNormalColor(Color{ 55, 255, 55, 1.f });
	leftDecButton->SetHighlightedColor(Color{ 155, 255, 155, 1.f });
	//decisionButtonLeft->addComponent<TextMesh>(pos, 1.5, "Test", Color(255, 255, 255, 1.f));
	decisionButtonLeft->isActive = false;
	decisionBoxManager->transform->AddChild(decisionButtonLeft->transform);
	pos = { AEGfxGetWindowWidth() * 0.2f, -AEGfxGetWindowHeight() * 0.3f };
	scale = { AEGfxGetWindowWidth() * 0.3f, AEGfxGetWindowHeight() * 0.1f };
	auto decisionButtonRight = std::make_unique<Entity>("DecisionButtonRight");
	decisionButtonRight->addComponent<Transform2D>(pos, scale, 0.f);
	decisionButtonRight->addComponent<Mesh>("Box", Color(255, 255, 255, 1.f), 201, MeshType::BOX_B);
	Button* rightDecButton = decisionButtonRight->addComponent<Button>();
	rightDecButton->SetNormalColor(Color{ 255, 55, 55, 1.f });
	rightDecButton->SetHighlightedColor(Color{ 255, 155, 155, 1.f });
	decisionButtonRight->isActive = false;
	decisionBoxManager->transform->AddChild(decisionButtonRight->transform);

	meshSystem->CreateTexture("../../Assets/Images/base_camp.png", "BC_BG");
	auto bg = std::make_unique<Entity>("Background");
	pos = { 0.f, 0.f };
	scale = { (float)AEGfxGetWindowWidth(), (float)AEGfxGetWindowHeight() };
	bg->addComponent<Transform2D>(pos, scale, 0.f);
	bg->addComponent<Mesh>("Box", "BC_BG", Color(255, 255, 255, 1.f), 1, MeshType::BOX_T);
	enSystem->rootEntity->transform->AddChild(bg->transform);
	enSystem->entities.push_back(std::move(bg));

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
	enSystem->rootEntity->transform->AddChild(shopBackground->transform);

	auto blessing1 = std::make_unique<Entity>("Blessing1");
	pos = { -AEGfxGetWindowWidth() * 0.275f, AEGfxGetWindowHeight() * 0.05f };
	scale = { AEGfxGetWindowHeight() * 0.1f, AEGfxGetWindowHeight() * 0.1f};
	blessing1->addComponent<Transform2D>(pos, scale, 0.f);
	ShopBlessing* shopB1 = blessing1->addComponent<ShopBlessing>();
	blessing1->addComponent<Mesh>("Box", shopB1->GetTextureName().c_str(), Color(255, 255, 255, 1.f), 200, MeshType::BOX_T);
	Button* blessing1Button = blessing1->addComponent<Button>();
	blessing1Button->SetNormalColor(Color{ 255, 255, 255, 1.f });
	blessing1Button->SetHighlightedColor(Color{ 155, 155, 155, 1.f });
	blessing1Button->SetOnClick([this, shopB1]() {PurchaseBlessing(shopB1->GetBlessingId()); });
	blessing1->isActive = false;
	enSystem->rootEntity->transform->AddChild(blessing1->transform);

	auto blessing2 = std::make_unique<Entity>("Blessing2");
	pos = { -AEGfxGetWindowWidth() * 0.175f, AEGfxGetWindowHeight() * 0.05f };
	scale = { AEGfxGetWindowHeight() * 0.1f, AEGfxGetWindowHeight() * 0.1f };
	blessing2->addComponent<Transform2D>(pos, scale, 0.f);
	ShopBlessing* shopB2 = blessing2->addComponent<ShopBlessing>();
	blessing2->addComponent<Mesh>("Box", shopB2->GetTextureName().c_str(), Color(255, 255, 255, 1.f), 200, MeshType::BOX_T);
	Button* blessing2Button = blessing2->addComponent<Button>();
	blessing2Button->SetNormalColor(Color{ 255, 255, 255, 1.f });
	blessing2Button->SetHighlightedColor(Color{ 155, 155, 155, 1.f });
	blessing2Button->SetOnClick([this, shopB2]() {PurchaseBlessing(shopB2->GetBlessingId()); });
	blessing2->isActive = false;
	enSystem->rootEntity->transform->AddChild(blessing2->transform);

	auto blessing3 = std::make_unique<Entity>("Blessing3");
	pos = { -AEGfxGetWindowWidth() * 0.075f, AEGfxGetWindowHeight() * 0.05f };
	scale = { AEGfxGetWindowHeight() * 0.1f, AEGfxGetWindowHeight() * 0.1f };
	blessing3->addComponent<Transform2D>(pos, scale, 0.f);
	ShopBlessing* shopB3 = blessing3->addComponent<ShopBlessing>();
	blessing3->addComponent<Mesh>("Box", shopB3->GetTextureName().c_str(), Color(255, 255, 255, 1.f), 200, MeshType::BOX_T);
	Button* blessing3Button = blessing3->addComponent<Button>();
	blessing3Button->SetNormalColor(Color{ 255, 255, 255, 1.f });
	blessing3Button->SetHighlightedColor(Color{ 155, 155, 155, 1.f });
	blessing3Button->SetOnClick([this, shopB3]() {PurchaseBlessing(shopB3->GetBlessingId()); });
	blessing3->isActive = false;
	enSystem->rootEntity->transform->AddChild(blessing3->transform);

	auto blessing4 = std::make_unique<Entity>("Blessing4");
	pos = { AEGfxGetWindowWidth() * 0.025f, AEGfxGetWindowHeight() * 0.05f };
	scale = { AEGfxGetWindowHeight() * 0.1f, AEGfxGetWindowHeight() * 0.1f };
	blessing4->addComponent<Transform2D>(pos, scale, 0.f);
	ShopBlessing* shopB4 = blessing4->addComponent<ShopBlessing>();
	blessing4->addComponent<Mesh>("Box", shopB4->GetTextureName().c_str(), Color(255, 255, 255, 1.f), 200, MeshType::BOX_T);
	Button* blessing4Button = blessing4->addComponent<Button>();
	blessing4Button->SetNormalColor(Color{ 255, 255, 255, 1.f });
	blessing4Button->SetHighlightedColor(Color{ 155, 155, 155, 1.f });
	blessing4Button->SetOnClick([this, shopB4]() {PurchaseBlessing(shopB4->GetBlessingId()); });
	blessing4->isActive = false;
	enSystem->rootEntity->transform->AddChild(blessing4->transform);

	auto blessingsText = std::make_unique<Entity>("BlessingsText");
	pos = { -AEGfxGetWindowWidth() * 0.9f, AEGfxGetWindowHeight() * 0.7f};
	scale = { 1.f, 1.f };
	blessingsText->addComponent<Transform2D>(pos, scale, 0.f);
	blessingsText->addComponent<Mesh>("Box", Color(255, 255, 255, 1.f), 201, MeshType::BOX_B);
	blessingsText->addComponent<TextMesh>(pos, 1, "Blessings:", Color(255, 255, 255, 1.f));
	blessingsText->isActive = false;
	enSystem->rootEntity->transform->AddChild(blessingsText->transform);

	auto artifactsText = std::make_unique<Entity>("ArtifactsText");
	pos = { -AEGfxGetWindowWidth() * 0.9f, -AEGfxGetWindowHeight() * 0.4f };
	scale = { 1.f, 1.f };
	artifactsText->addComponent<Transform2D>(pos, scale, 0.f);
	artifactsText->addComponent<Mesh>("Box", Color(255, 255, 255, 1.f), 201, MeshType::BOX_B);
	artifactsText->addComponent<TextMesh>(pos, 1, "Artifacts:", Color(255, 255, 255, 1.f));
	artifactsText->isActive = false;
	enSystem->rootEntity->transform->AddChild(artifactsText->transform);
	auto nameText = std::make_unique<Entity>("NameText");
	pos = { AEGfxGetWindowWidth() * 0.6f, AEGfxGetWindowHeight() * 0.5f };
	scale = { 1.f, 1.f };
	nameText->addComponent<Transform2D>(pos, scale, 0.f);
	nameText->addComponent<Mesh>("Box", Color(255, 255, 255, 1.f), 201, MeshType::BOX_B);
	nameText->addComponent<TextMesh>(pos, 0.5f, "Name:", Color(255, 255, 255, 1.f));
	nameText->isActive = false;
	enSystem->rootEntity->transform->AddChild(nameText->transform);
	auto typeDesc = std::make_unique<Entity>("TypeDesc");
	pos = { AEGfxGetWindowWidth() * 0.6f, AEGfxGetWindowHeight() * 0.4f };
	scale = { 1.f, 1.f };
	typeDesc->addComponent<Transform2D>(pos, scale, 0.f);
	typeDesc->addComponent<Mesh>("Box", Color(255, 255, 255, 1.f), 201, MeshType::BOX_B);
	typeDesc->addComponent<TextMesh>(pos, 0.5f, "(Blessings are buffs\nthat only last for\n1 level)", Color(255, 255, 255, 1.f));
	typeDesc->isActive = false;
	enSystem->rootEntity->transform->AddChild(typeDesc->transform);

	meshSystem->CreateTexture("../../Assets/Images/shop.png", "shop");
	auto shop = std::make_unique<Entity>("Shop");
	pos = { -300.f, 100.f };
	scale = { 200.f, 200.f };
	shop->addComponent<Transform2D>(pos, scale, 0.f);
	shop->addComponent<Mesh>("Box", "shop", Color(100, 100, 100, 1), 100, MeshType::BOX_T);
	shop->addComponent<BoxCollider2D>(scale.x / 2, scale.y / 2);
	Shop* s = shop->addComponent<Shop>();
	s->AddDisplayEntity(shopBackground.get());
	s->AddDisplayEntity(blessing1.get());
	s->AddDisplayEntity(blessing2.get());
	s->AddDisplayEntity(blessing3.get());
	s->AddDisplayEntity(blessing4.get());
	s->AddDisplayEntity(blessingsText.get());
	s->AddDisplayEntity(artifactsText.get());
	s->AddDisplayEntity(nameText.get());
	s->AddDisplayEntity(typeDesc.get());
	enSystem->rootEntity->transform->AddChild(shop->transform);
	enSystem->entities.push_back(std::move(shopBackground));
	enSystem->entities.push_back(std::move(blessing1));
	enSystem->entities.push_back(std::move(blessing2));
	enSystem->entities.push_back(std::move(blessing3));
	enSystem->entities.push_back(std::move(blessing4));
	enSystem->entities.push_back(std::move(blessingsText));
	enSystem->entities.push_back(std::move(artifactsText));
	enSystem->entities.push_back(std::move(nameText));
	enSystem->entities.push_back(std::move(typeDesc));
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
	ts->addComponent<Mesh>("Box", Color(20, 20, 20, 1), 999, MeshType::BOX_B);
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
