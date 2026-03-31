#include "Shop.hpp"
#include "../Code/SoloBehavior/RunManager.hpp"
#include "../Code/SoloBehavior/Player.hpp"
#include "../Audio_WZBJ_Pak.hpp"
#include "../BaseSystems/Engine/TextBox.hpp"

// Collision logic
void Shop::onHit(BoxCollider2D*)
{
	canShow = true;
	//player->getComponent<Player>()->canMove = false;
	RunManager::Instance().playerCanMove = false;
}
void Shop::onStay(BoxCollider2D*)
{
}
void Shop::onExit(BoxCollider2D*)
{
}

void Shop::AddDisplayEntity(Entity* ent)
{
	display.push_back(ent);
}

void Shop::ChooseSelection(int id)
{
	currSelection = id;
	if (selection.find(currSelection)->second != true)
	{
		buyButtonEnt->isActive = true;
		auto b = shopBlessings[currSelection]->GetBlessing().get();
		switch (b->blessingRarity)
		{
		case BLESSING_RARITY::COMMON:
			costStr = "Cost: 25";
			break;
		case BLESSING_RARITY::RARE:
			costStr = "Cost: 50";
			break;
		case BLESSING_RARITY::LEGENDARY:
			costStr = "Cost: 100";
			break;
		case BLESSING_RARITY::MYTHICAL:
			costStr = "Cost: 250";
			break;
		}
	}
	else
	{
		buyButtonEnt->isActive = false;
		costStr = "Purchased!";
	}
	AudioManager::GetInstance()->PlaySFX(AudioManager::SFX_SELECT_SHOP);
}

void Shop::SetBuyButton(Entity* ent)
{
	buyButtonEnt = ent;
}

void Shop::PurchaseSelection()
{
	//if (RunManager::Instance().GetCurrency() <= itemPrice)
	//{
	//	Show the player cannot buy this item (Flash button, show text, play audio etc)
	//	return;
	//}
	// Purchase logic
	selection.find(currSelection)->second = true;

	bool couldPurchase = false;
	// Selection is Blessing
	if (currSelection <= 3)
	{
		auto b = shopBlessings[currSelection]->GetBlessing().get()->Clone();
		int itemcost{ 0 };
		switch (b.get()->blessingRarity)
		{
		case BLESSING_RARITY::COMMON:
			itemcost = 25;
			break;
		case BLESSING_RARITY::RARE:
			itemcost = 50;
			break;
		case BLESSING_RARITY::LEGENDARY:
			itemcost = 100;
			break;
		case BLESSING_RARITY::MYTHICAL:
			itemcost = 250;
			break;
		}

		if (RunManager::Instance().RemoveCurrency(itemcost))
		{
			RunManager::Instance().AddBlessing(std::move(b));
			couldPurchase = true;
		}
		else
		{
			currencyFlashTimer = currencyFlashTimerMax;
			currency->getComponent<TextBox>()->text_color = Color{ 255, 55, 55, 1.f };
		}
	}

	// UI elements
	if (couldPurchase)
	{
		for (std::pair<int, bool> p : selection)
			p.second = false;
		buyButtonEnt->isActive = false;
		costStr = "Purchased!";

		curStr = "Currency: " + to_string(RunManager::Instance().GetCurrency());
		currency->getComponent<TextBox>()->text = curStr.c_str();
		AudioManager::GetInstance()->PlaySFX(AudioManager::SFX_PURCHASE_SHOP);
	}
}

void Shop::AddShopBlessings(ShopBlessing* b, int id)
{
	shopBlessings[id] = b;
}

void Shop::CloseShopUI()
{
	canShow = false;
	RunManager::Instance().playerCanMove = true;
}

void Shop::SetPlayer(Entity* p)
{
	player = p;
}

void Shop::SetCurrency(Entity* c)
{
	currency = c;
}

void Shop::SetCost(Entity* c)
{
	cost = c;
}

void Shop::DisplayBlessing(std::string const& nameStr, std::string const& typeDesc, std::string const& longDescStr, int shopId)
{
	// Get the three text boxes
	Entity* name = enSystem->rootEntity->FindByName("NameText");
	Entity* type = enSystem->rootEntity->FindByName("TypeDesc");
	Entity* longDesc = enSystem->rootEntity->FindByName("LongDesc");

	name->getComponent<TextBox>()->text = nameStr.c_str();
	type->getComponent<TextBox>()->text = typeDesc.c_str();
	longDesc->getComponent<TextBox>()->text = longDescStr.c_str();

	// Shop selection
	ChooseSelection(shopId);
}

void Shop::awake()
{
	BoxCollider2D* col = entity->getComponent<BoxCollider2D>();
	if (col) {
		col->onCollisionEnter([this](BoxCollider2D* other) { onHit(other); });
		col->onCollisionStay([this](BoxCollider2D* other) { onStay(other); });
		col->onCollisionExit([this](BoxCollider2D* other) { onExit(other); });
	}

	std::string blessingDesc("(Blessings are buffs that only last for 1 level)");
	std::string artifactDesc("(Artifacts are powerful buffs that last forever)");

	meshSystem->CreateTexture("Assets/UI/shop-back.png", "ShopBGTexture");
	auto shopBackground = std::make_unique<Entity>("ShopBG");
	AEVec2 pos = { 0.f, 0.f };
	AEVec2 scale = { static_cast<float>(AEGfxGetWindowWidth()), static_cast<float>(AEGfxGetWindowHeight()) };
	shopBackground->addComponent<Transform2D>(pos, scale, 0.f);
	shopBackground->addComponent<Mesh>("Box", "ShopBGTexture", Color(255, 255, 255, 1.f), 202, MeshType::BOX_T);
	shopBackground->isActive = false;
	enSystem->rootEntity->transform->AddChild(shopBackground->transform);
	auto nameText = std::make_unique<Entity>("NameText");
	pos = { AEGfxGetWindowWidth() * 0.26f, AEGfxGetWindowHeight() * 0.115f };
	scale = { AEGfxGetWindowWidth() * 0.2f, AEGfxGetWindowHeight() * 0.05f };
	nameText->addComponent<Transform2D>(pos, scale, 0.f);
	nameText->addComponent<Mesh>("Box", Color(0, 0, 0, 0.f), 202, MeshType::BOX_B);
	nameText->addComponent<TextBox>("Click to view items", 0.5f, TextBoxVAllign::CENTER, TextBoxHAllign::LEFT);
	nameText->isActive = false;
	enSystem->rootEntity->transform->AddChild(nameText->transform);
	auto typeDesc = std::make_unique<Entity>("TypeDesc");
	pos = { AEGfxGetWindowWidth() * 0.26f, AEGfxGetWindowHeight() * 0.065f };
	scale = { AEGfxGetWindowWidth() * 0.2f, AEGfxGetWindowHeight() * 0.05f };
	typeDesc->addComponent<Transform2D>(pos, scale, 0.f);
	typeDesc->addComponent<Mesh>("Box", Color(0, 0, 0, 0.f), 202, MeshType::BOX_B);
	typeDesc->addComponent<TextBox>("", 0.35f, TextBoxVAllign::TOP, TextBoxHAllign::LEFT);
	typeDesc->isActive = false;
	enSystem->rootEntity->transform->AddChild(typeDesc->transform);
	auto longDesc = std::make_unique<Entity>("LongDesc");
	pos = { AEGfxGetWindowWidth() * 0.26f, -AEGfxGetWindowHeight() * 0.085f };
	scale = { AEGfxGetWindowWidth() * 0.2f, AEGfxGetWindowHeight() * 0.25f };
	longDesc->addComponent<Transform2D>(pos, scale, 0.f);
	longDesc->addComponent<Mesh>("Box", Color(0, 0, 0, 0.f), 202, MeshType::BOX_B);
	longDesc->addComponent<TextBox>("", 0.5f, TextBoxVAllign::TOP, TextBoxHAllign::LEFT);
	longDesc->isActive = false;
	enSystem->rootEntity->transform->AddChild(longDesc->transform);
	auto buyButton = std::make_unique<Entity>("BuyButton");
	pos = { AEGfxGetWindowWidth() * 0.250f, -AEGfxGetWindowHeight() * 0.2f };
	scale = { AEGfxGetWindowWidth() * 0.13f, AEGfxGetWindowHeight() * 0.07f };
	buyButton->addComponent<Transform2D>(pos, scale, 0.f);
	buyButton->addComponent<Mesh>("Box", "Button", Color(255, 255, 255, 1.f), 202, MeshType::BOX_T);
	buyButton->addComponent<TextBox>("BUY", 0.5f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);
	Button* actualBuyButton = buyButton->addComponent<Button>();
	actualBuyButton->SetNormalColor(Color{ 255, 255, 255, 1.f });
	actualBuyButton->SetHighlightedColor(Color{ 155, 155, 155, 1.f });
	actualBuyButton->SetOnClick([this]() {PurchaseSelection(); });
	buyButton->isActive = false;
	enSystem->rootEntity->transform->AddChild(buyButton->transform);

	auto blessing1 = std::make_unique<Entity>("Blessing1");
	pos = { -AEGfxGetWindowWidth() * 0.275f, AEGfxGetWindowHeight() * 0.05f };
	scale = { AEGfxGetWindowHeight() * 0.1f, AEGfxGetWindowHeight() * 0.1f };
	blessing1->addComponent<Transform2D>(pos, scale, 0.f);
	ShopBlessing* shopB1 = blessing1->addComponent<ShopBlessing>();
	blessing1->addComponent<Mesh>("Box", shopB1->GetTextureName().c_str(), Color(255, 255, 255, 1.f), 202, MeshType::BOX_T);
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
	blessing2->addComponent<Mesh>("Box", shopB2->GetTextureName().c_str(), Color(255, 255, 255, 1.f), 202, MeshType::BOX_T);
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
	blessing3->addComponent<Mesh>("Box", shopB3->GetTextureName().c_str(), Color(255, 255, 255, 1.f), 202, MeshType::BOX_T);
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
	blessing4->addComponent<Mesh>("Box", shopB4->GetTextureName().c_str(), Color(255, 255, 255, 1.f), 202, MeshType::BOX_T);
	Button* blessing4Button = blessing4->addComponent<Button>();
	blessing4Button->SetNormalColor(Color{ 255, 255, 255, 1.f });
	blessing4Button->SetHighlightedColor(Color{ 155, 155, 155, 1.f });
	blessing4Button->SetOnClick([this, shopB4, blessingDesc]() {DisplayBlessing(shopB4->GetBlessing().get()->blessingName,
		blessingDesc, shopB4->GetBlessing().get()->blessingDesc, 3); });
	blessing4->isActive = false;
	enSystem->rootEntity->transform->AddChild(blessing4->transform);

	auto blessingsText = std::make_unique<Entity>("BlessingsText");
	pos = { -AEGfxGetWindowWidth() * 0.225f, AEGfxGetWindowHeight() * 0.175f };
	scale = { AEGfxGetWindowWidth() * 0.2f, AEGfxGetWindowHeight() * 0.05f };
	blessingsText->addComponent<Transform2D>(pos, scale, 0.f);
	blessingsText->addComponent<Mesh>("Box", Color(0, 0, 0, 0.f), 202, MeshType::BOX_B);
	blessingsText->addComponent<TextBox>("Blessings:", 1.f, TextBoxVAllign::CENTER, TextBoxHAllign::LEFT);
	blessingsText->isActive = false;
	enSystem->rootEntity->transform->AddChild(blessingsText->transform);
	auto artifactsText = std::make_unique<Entity>("ArtifactsText");
	pos = { -AEGfxGetWindowWidth() * 0.225f, -AEGfxGetWindowHeight() * 0.075f };
	scale = { AEGfxGetWindowWidth() * 0.2f, AEGfxGetWindowHeight() * 0.05f };
	artifactsText->addComponent<Transform2D>(pos, scale, 0.f);
	artifactsText->addComponent<Mesh>("Box", Color(0, 0, 0, 0.f), 202, MeshType::BOX_B);
	artifactsText->addComponent<TextBox>("Artifacts:", 1.f, TextBoxVAllign::CENTER, TextBoxHAllign::LEFT);
	artifactsText->isActive = false;
	enSystem->rootEntity->transform->AddChild(artifactsText->transform);

	auto shopCloseButton = std::make_unique<Entity>("ShopCloseButton");
	pos = { AEGfxGetWindowWidth() * 0.325f, AEGfxGetWindowHeight() * 0.25f };
	scale = { AEGfxGetWindowWidth() * 0.05f, AEGfxGetWindowHeight() * 0.05f };
	shopCloseButton->addComponent<Transform2D>(pos, scale, 0.f);
	shopCloseButton->addComponent<Mesh>("Box", Color(255, 0, 0, 1.f), 202, MeshType::BOX_B);
	shopCloseButton->addComponent<TextBox>("X", 1.f, TextBoxVAllign::CENTER, TextBoxHAllign::CENTER);
	Button* closeButton = shopCloseButton->addComponent<Button>();
	closeButton->SetNormalColor(Color{ 255, 0, 0, 1.f });
	closeButton->SetHighlightedColor(Color{ 155, 0, 0, 1.f });
	closeButton->SetOnClick([this]() {CloseShopUI(); });
	shopCloseButton->isActive = false;
	enSystem->rootEntity->transform->AddChild(shopCloseButton->transform);

	auto currencyText = std::make_unique<Entity>("CurrencyText");
	pos = { -AEGfxGetWindowWidth() * 0.275f, AEGfxGetWindowHeight() * 0.25f };
	scale = { AEGfxGetWindowWidth() * 0.1f, AEGfxGetWindowHeight() * 0.05f };
	currencyText->addComponent<Transform2D>(pos, scale, 0.f);
	currencyText->addComponent<Mesh>("Box", Color(255, 255, 255, 0.f), 202, MeshType::BOX_B);
	currencyText->addComponent<TextBox>("Currency: ", 0.5f, TextBoxVAllign::CENTER, TextBoxHAllign::LEFT);
	currencyText->isActive = false;
	enSystem->rootEntity->transform->AddChild(currencyText->transform);

	auto costText = std::make_unique<Entity>("CostText");
	pos = { AEGfxGetWindowWidth() * 0.26f, -AEGfxGetWindowHeight() * 0.15f };
	scale = { AEGfxGetWindowWidth() * 0.15f, AEGfxGetWindowHeight() * 0.05f };
	costText->addComponent<Transform2D>(pos, scale, 0.f);
	costText->addComponent<Mesh>("Box", Color(255, 255, 255, 0.f), 202, MeshType::BOX_B);
	costText->addComponent<TextBox>("Cost: ", 0.5f, TextBoxVAllign::CENTER, TextBoxHAllign::LEFT);
	costText->isActive = false;
	enSystem->rootEntity->transform->AddChild(costText->transform);

	display.push_back(shopBackground.get());
	display.push_back(blessing1.get());
	display.push_back(blessing2.get());
	display.push_back(blessing3.get());
	display.push_back(blessing4.get());
	display.push_back(blessingsText.get());
	display.push_back(artifactsText.get());
	display.push_back(nameText.get());
	display.push_back(typeDesc.get());
	display.push_back(longDesc.get());
	display.push_back(shopCloseButton.get());
	display.push_back(currencyText.get());
	display.push_back(costText.get());
	display.push_back(buyButton.get());
	SetBuyButton(buyButton.get());
	AddShopBlessings(shopB1, 0);
	AddShopBlessings(shopB2, 1);
	AddShopBlessings(shopB3, 2);
	AddShopBlessings(shopB4, 3);
	SetCurrency(currencyText.get());
	SetCost(costText.get());

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
	enSystem->entities.push_back(std::move(currencyText));
	enSystem->entities.push_back(std::move(costText));

	CloseShopUI();
}

void Shop::init()
{
	selection.insert(std::make_pair<int, bool>(0, false));
	selection.insert(std::make_pair<int, bool>(1, false));
	selection.insert(std::make_pair<int, bool>(2, false));
	selection.insert(std::make_pair<int, bool>(3, false));
	selection.insert(std::make_pair<int, bool>(4, false));
	selection.insert(std::make_pair<int, bool>(5, false));
	selection.insert(std::make_pair<int, bool>(6, false));
	selection.insert(std::make_pair<int, bool>(7, false));

	curStr = "Currency: " + to_string(RunManager::Instance().GetCurrency());
	currency->getComponent<TextBox>()->text = curStr.c_str();
	cost->getComponent<TextBox>()->text = "";

	currencyFlashTimerMax = 0.5f;
}

void Shop::update()
{
	if (canShow && !RunManager::Instance().game_paused)
	{
		for (Entity* ent : display)
			ent->isActive = true;
		if (currSelection != -1 && selection.find(currSelection)->second != true)
			buyButtonEnt->isActive = true;
	}
	else
	{
		for (Entity* ent : display)
			ent->isActive = false;
		buyButtonEnt->isActive = false;
	}
	if (currencyFlashTimer > 0.f)
		currencyFlashTimer -= float(AEFrameRateControllerGetFrameTime());
	else
		currency->getComponent<TextBox>()->text_color = Color{ 255, 255, 255, 1.f };
	cost->getComponent<TextBox>()->text = costStr.c_str();
}

void Shop::fixedUpdate()
{
}

void Shop::destroy()
{
}

Shop::Shop()
{
	enSystem = &EntityManager::getInstance();
	meshSystem = &MeshGen::getInstance();
}

Shop::~Shop()
{
}
