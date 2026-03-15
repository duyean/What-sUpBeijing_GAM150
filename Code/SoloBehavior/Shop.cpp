#include "Shop.hpp"

// Collision logic
void Shop::onHit(BoxCollider2D* other)
{
	for (Entity* ent : display)
		ent->isActive = true;
}
void Shop::onStay(BoxCollider2D* other)
{
}
void Shop::onExit(BoxCollider2D* other)
{
	for (Entity* ent : display)
		ent->isActive = false;
}

void Shop::AddDisplayEntity(Entity* ent)
{
	display.push_back(ent);
}

void Shop::ChooseSelection(int id)
{
	for (std::pair<int, bool> p : selection)
		p.second = false;
	selection.find(id)->second = true;
}

void Shop::awake()
{
	BoxCollider2D* col = entity->getComponent<BoxCollider2D>();
	if (col) {
		col->onCollisionEnter([this](BoxCollider2D* other) { onHit(other); });
		col->onCollisionStay([this](BoxCollider2D* other) { onStay(other); });
		col->onCollisionExit([this](BoxCollider2D* other) { onExit(other); });
	}
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
