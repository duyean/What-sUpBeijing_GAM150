#include "Shop.hpp"

// Collision logic
void Shop::onHit(BoxCollider2D* other)
{
	decisionBox->ToggleDecisionBox(true);
}
void Shop::onStay(BoxCollider2D* other)
{
}
void Shop::onExit(BoxCollider2D* other)
{
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

Shop::Shop(DecisionBoxManager* box)
{
	decisionBox = box;
}

Shop::~Shop()
{
}
