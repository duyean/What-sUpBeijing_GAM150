#include "Shop.hpp"
#include "../Code/SoloBehavior/RunManager.hpp"
#include "../Code/SoloBehavior/Player.hpp"
#include "../Audio_WZBJ_Pak.hpp"

// Collision logic
void Shop::onHit(BoxCollider2D* other)
{
	canShow = true;
	player->getComponent<Player>()->canMove = false;
}
void Shop::onStay(BoxCollider2D* other)
{
}
void Shop::onExit(BoxCollider2D* other)
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
		buyButton->isActive = true;
	else
		buyButton->isActive = false;
	AudioManager::GetInstance()->PlaySFX(AudioManager::SFX_SELECT_SHOP);
}

void Shop::SetBuyButton(Entity* ent)
{
	buyButton = ent;
}

void Shop::PurchaseSelection()
{
	// Purchase logic
	selection.find(currSelection)->second = true;

	// Selection is Blessing
	if (currSelection <= 3)
	{
		auto b = shopBlessings[currSelection]->GetBlessing().get()->Clone();
		RunManager::Instance().AddBlessing(std::move(b));
	}

	// UI elements
	for (std::pair<int, bool> p : selection)
		p.second = false;
	buyButton->isActive = false;
	AudioManager::GetInstance()->PlaySFX(AudioManager::SFX_PURCHASE_SHOP);
}

void Shop::AddShopBlessings(ShopBlessing* b, int id)
{
	shopBlessings[id] = b;
}

void Shop::CloseShopUI()
{
	canShow = false;
}

void Shop::SetPlayer(Entity* p)
{
	player = p;
}

void Shop::awake()
{
	BoxCollider2D* col = entity->getComponent<BoxCollider2D>();
	if (col) {
		col->onCollisionEnter([this](BoxCollider2D* other) { onHit(other); });
		col->onCollisionStay([this](BoxCollider2D* other) { onStay(other); });
		col->onCollisionExit([this](BoxCollider2D* other) { onExit(other); });
	}

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
}

void Shop::update()
{
	if (canShow && !RunManager::Instance().game_paused)
	{
		for (Entity* ent : display)
			ent->isActive = true;
		if (currSelection != -1 && selection.find(currSelection)->second != true)
			buyButton->isActive = true;
	}
	else
	{
		for (Entity* ent : display)
			ent->isActive = false;
		buyButton->isActive = false;
	}
}

void Shop::fixedUpdate()
{
}

void Shop::destroy()
{
}

Shop::Shop()
{
}

Shop::~Shop()
{
}
