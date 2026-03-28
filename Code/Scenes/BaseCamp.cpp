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

void BaseCamp::DisplayBlessing(std::string const& nameStr, std::string const& typeDesc, std::string const& longDescStr, int shopId)
{
	// Get the three text boxes
	Entity* name = enSystem->rootEntity->FindByName("NameText");
	Entity* type = enSystem->rootEntity->FindByName("TypeDesc");
	Entity* longDesc = enSystem->rootEntity->FindByName("LongDesc");

	name->getComponent<TextBox>()->text = nameStr.c_str();
	type->getComponent<TextBox>()->text = typeDesc.c_str();
	longDesc->getComponent<TextBox>()->text = longDescStr.c_str();

	// Shop selection
	Entity* shop = enSystem->rootEntity->FindByName("Shop");
	shop->getComponent<Shop>()->ChooseSelection(shopId);
}

void BaseCamp::Purchase()
{
	Entity* shop = enSystem->rootEntity->FindByName("Shop");
	shop->getComponent<Shop>()->PurchaseSelection();
}

void BaseCamp::CloseShop()
{
	Entity* shop = enSystem->rootEntity->FindByName("Shop");
	Entity* player = enSystem->rootEntity->FindByName("Player");
	
	shop->getComponent<Shop>()->CloseShopUI();
	//player->getComponent<Player>()->canMove = true;
	RunManager::Instance().playerCanMove = true;
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
	std::string blessingDesc("(Blessings are buffs that only last for 1 level)");
	std::string artifactDesc("(Artifacts are powerful buffs that last forever)");

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

	meshSystem->CreateTexture("../../Assets/Images/SPRITE.png", "player_sprite");
	auto e = std::make_unique<Entity>("Player");
	pos = { 0.f, -200.f };
	scale = { 100.f, 100.f };
	e->addComponent<Transform2D>(pos, scale, 0.f);
	e->addComponent<Player>();
	e->addComponent<Mesh>("Box", "player_sprite", Color(255, 255, 255, 1.f), 100, MeshType::BOX_T);
	e->addComponent<BoxCollider2D>(scale.x / 2, scale.y / 2);
	enSystem->rootEntity->transform->AddChild(e->transform);

	/*auto curr_disp = std::make_unique<Entity>("CurrDisp");
	pos = { 0.f, 0.f };
	scale = { 100.f, 100.f };
	curr_disp->addComponent<Transform2D>(pos, scale, 0.f);
	curr_disp->addComponent<CurrencyDisplay>();
	enSystem->rootEntity->transform->AddChild(curr_disp->transform);
	enSystem->entities.push_back(std::move(curr_disp));*/

	meshSystem->CreateTexture("../../Assets/Images/base_camp.png", "BC_BG");
	auto bg = std::make_unique<Entity>("Background");
	pos = { 0.f, 0.f };
	scale = { (float)AEGfxGetWindowWidth(), (float)AEGfxGetWindowHeight() };
	bg->addComponent<Transform2D>(pos, scale, 0.f);
	bg->addComponent<Mesh>("Box", "BC_BG", Color(255, 255, 255, 1.f), 1, MeshType::BOX_T);
	enSystem->rootEntity->transform->AddChild(bg->transform);
	enSystem->entities.push_back(std::move(bg));

	meshSystem->CreateTexture("Assets/UI/shop-back.png", "ShopBGTexture");
	auto shopBackground = std::make_unique<Entity>("ShopBG");
	pos = { 0.f, 0.f };
	scale = { static_cast<float>(AEGfxGetWindowWidth()), static_cast<float>(AEGfxGetWindowHeight()) };
	shopBackground->addComponent<Transform2D>(pos, scale, 0.f);
	shopBackground->addComponent<Mesh>("Box", "ShopBGTexture", Color(255, 255, 255, 1.f), 200, MeshType::BOX_T);
	shopBackground->isActive = false;
	enSystem->rootEntity->transform->AddChild(shopBackground->transform);

	auto nameText = std::make_unique<Entity>("NameText");
	pos = { AEGfxGetWindowWidth() * 0.26f, AEGfxGetWindowHeight() * 0.115f };
	scale = { AEGfxGetWindowWidth() * 0.2f, AEGfxGetWindowHeight() * 0.05f };
	nameText->addComponent<Transform2D>(pos, scale, 0.f);
	nameText->addComponent<Mesh>("Box", Color(0, 0, 0, 0.f), 201, MeshType::BOX_B);
	nameText->addComponent<TextBox>("Click to view items", 0.5f, TextBoxVAllign::CENTER, TextBoxHAllign::LEFT);
	nameText->isActive = false;
	enSystem->rootEntity->transform->AddChild(nameText->transform);
	auto typeDesc = std::make_unique<Entity>("TypeDesc");
	pos = { AEGfxGetWindowWidth() * 0.26f, AEGfxGetWindowHeight() * 0.065f };
	scale = { AEGfxGetWindowWidth() * 0.2f, AEGfxGetWindowHeight() * 0.05f };
	typeDesc->addComponent<Transform2D>(pos, scale, 0.f);
	typeDesc->addComponent<Mesh>("Box", Color(0, 0, 0, 0.f), 201, MeshType::BOX_B);
	typeDesc->addComponent<TextBox>("", 0.35f, TextBoxVAllign::TOP, TextBoxHAllign::LEFT);
	typeDesc->isActive = false;
	enSystem->rootEntity->transform->AddChild(typeDesc->transform);
	auto longDesc = std::make_unique<Entity>("LongDesc");
	pos = { AEGfxGetWindowWidth() * 0.26f, -AEGfxGetWindowHeight() * 0.085f };
	scale = { AEGfxGetWindowWidth() * 0.2f, AEGfxGetWindowHeight() * 0.25f };
	longDesc->addComponent<Transform2D>(pos, scale, 0.f);
	longDesc->addComponent<Mesh>("Box", Color(0, 0, 0, 0.f), 201, MeshType::BOX_B);
	longDesc->addComponent<TextBox>("", 0.5f, TextBoxVAllign::TOP, TextBoxHAllign::LEFT);
	longDesc->isActive = false;
	enSystem->rootEntity->transform->AddChild(longDesc->transform);
	auto buyButton = std::make_unique<Entity>("BuyButton");
	pos = { AEGfxGetWindowWidth() * 0.250f, -AEGfxGetWindowHeight() * 0.2f };
	scale = { AEGfxGetWindowWidth() * 0.13f, AEGfxGetWindowHeight() * 0.07f };
	buyButton->addComponent<Transform2D>(pos, scale, 0.f);
	buyButton->addComponent<Mesh>("Box", "Button", Color(255, 255, 255, 1.f), 201, MeshType::BOX_T);
	buyButton->addComponent<TextBox>("BUY", 0.5f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);
	Button* actualBuyButton = buyButton->addComponent<Button>();
	actualBuyButton->SetNormalColor(Color{ 255, 255, 255, 1.f });
	actualBuyButton->SetHighlightedColor(Color{ 155, 155, 155, 1.f });
	actualBuyButton->SetOnClick([this]() {Purchase(); });
	buyButton->isActive = false;
	enSystem->rootEntity->transform->AddChild(buyButton->transform);

	auto blessing1 = std::make_unique<Entity>("Blessing1");
	pos = { -AEGfxGetWindowWidth() * 0.275f, AEGfxGetWindowHeight() * 0.05f };
	scale = { AEGfxGetWindowHeight() * 0.1f, AEGfxGetWindowHeight() * 0.1f};
	blessing1->addComponent<Transform2D>(pos, scale, 0.f);
	ShopBlessing* shopB1 = blessing1->addComponent<ShopBlessing>();
	blessing1->addComponent<Mesh>("Box", shopB1->GetTextureName().c_str(), Color(255, 255, 255, 1.f), 200, MeshType::BOX_T);
	Button* blessing1Button = blessing1->addComponent<Button>();
	blessing1Button->SetNormalColor(Color{ 255, 255, 255, 1.f });
	blessing1Button->SetHighlightedColor(Color{ 155, 155, 155, 1.f });
	blessing1Button->SetOnClick([this, shopB1, blessingDesc]() {DisplayBlessing(shopB1->GetBlessing().get()->blessingName,
		blessingDesc, shopB1->GetBlessing().get()->blessingDesc, 0); });
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
	blessing2Button->SetOnClick([this, shopB2, blessingDesc]() {DisplayBlessing(shopB2->GetBlessing().get()->blessingName,
		blessingDesc, shopB2->GetBlessing().get()->blessingDesc, 1); });
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
	blessing3Button->SetOnClick([this, shopB3, blessingDesc]() {DisplayBlessing(shopB3->GetBlessing().get()->blessingName,
		blessingDesc, shopB3->GetBlessing().get()->blessingDesc, 2); });
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
	blessing4Button->SetOnClick([this, shopB4, blessingDesc]() {DisplayBlessing(shopB4->GetBlessing().get()->blessingName,
		blessingDesc, shopB4->GetBlessing().get()->blessingDesc, 3); });
	blessing4->isActive = false;
	enSystem->rootEntity->transform->AddChild(blessing4->transform);

	auto blessingsText = std::make_unique<Entity>("BlessingsText");
	pos = { -AEGfxGetWindowWidth() * 0.225f, AEGfxGetWindowHeight() * 0.175f};
	scale = { AEGfxGetWindowWidth() * 0.2f, AEGfxGetWindowHeight() * 0.05f };
	blessingsText->addComponent<Transform2D>(pos, scale, 0.f);
	blessingsText->addComponent<Mesh>("Box", Color(0, 0, 0, 0.f), 201, MeshType::BOX_B);
	blessingsText->addComponent<TextBox>("Blessings:", 1.f, TextBoxVAllign::CENTER, TextBoxHAllign::LEFT);
	blessingsText->isActive = false;
	enSystem->rootEntity->transform->AddChild(blessingsText->transform);
	auto artifactsText = std::make_unique<Entity>("ArtifactsText");
	pos = { -AEGfxGetWindowWidth() * 0.225f, -AEGfxGetWindowHeight() * 0.075f };
	scale = { AEGfxGetWindowWidth() * 0.2f, AEGfxGetWindowHeight() * 0.05f };
	artifactsText->addComponent<Transform2D>(pos, scale, 0.f);
	artifactsText->addComponent<Mesh>("Box", Color(0, 0, 0, 0.f), 201, MeshType::BOX_B);
	artifactsText->addComponent<TextBox>("Artifacts:", 1.f, TextBoxVAllign::CENTER, TextBoxHAllign::LEFT);
	artifactsText->isActive = false;
	enSystem->rootEntity->transform->AddChild(artifactsText->transform);

	auto shopCloseButton = std::make_unique<Entity>("ShopCloseButton");
	pos = { AEGfxGetWindowWidth() * 0.325f, AEGfxGetWindowHeight() * 0.25f };
	scale = { AEGfxGetWindowWidth() * 0.05f, AEGfxGetWindowHeight() * 0.05f };
	shopCloseButton->addComponent<Transform2D>(pos, scale, 0.f);
	shopCloseButton->addComponent<Mesh>("Box", Color(255, 0, 0, 1.f), 201, MeshType::BOX_B);
	shopCloseButton->addComponent<TextBox>("X", 1.f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);
	Button* closeButton = shopCloseButton->addComponent<Button>();
	closeButton->SetNormalColor(Color{ 255, 0, 0, 1.f });
	closeButton->SetHighlightedColor(Color{ 155, 0, 0, 1.f });
	closeButton->SetOnClick([this]() {CloseShop(); });
	shopCloseButton->isActive = false;
	enSystem->rootEntity->transform->AddChild(shopCloseButton->transform);

	meshSystem->CreateTexture("Assets/Images/shop.png", "shop");
	auto shop = std::make_unique<Entity>("Shop");
	pos = { -300.f, 100.f };
	scale = { 200.f, 200.f };
	shop->addComponent<Transform2D>(pos, scale, 0.f);
	shop->addComponent<Mesh>("Box", "shop", Color(255, 255, 255, 1), 100, MeshType::BOX_T);
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
	s->AddDisplayEntity(longDesc.get());
	s->AddDisplayEntity(shopCloseButton.get());
	s->SetBuyButton(buyButton.get());
	s->AddShopBlessings(shopB1, 0);
	s->AddShopBlessings(shopB2, 1);
	s->AddShopBlessings(shopB3, 2);
	s->AddShopBlessings(shopB4, 3);
	s->SetPlayer(e.get());
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
	enSystem->entities.push_back(std::move(longDesc));
	enSystem->entities.push_back(std::move(buyButton));
	enSystem->entities.push_back(std::move(shopCloseButton));
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
