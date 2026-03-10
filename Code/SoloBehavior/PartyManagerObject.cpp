#include "PartyManagerObject.hpp"

// Collision logic
void PartyManagerObject::onHit(BoxCollider2D* other)
{
	decisionBox->ToggleDecisionBox(true);
}
void PartyManagerObject::onStay(BoxCollider2D* other)
{
}
void PartyManagerObject::onExit(BoxCollider2D* other)
{
}

void PartyManagerObject::awake()
{
	BoxCollider2D* col = entity->getComponent<BoxCollider2D>();
	if (col) {
		col->onCollisionEnter([this](BoxCollider2D* other) { onHit(other); });
		col->onCollisionStay([this](BoxCollider2D* other) { onStay(other); });
		col->onCollisionExit([this](BoxCollider2D* other) { onExit(other); });
	}
}

void PartyManagerObject::init()
{
}

void PartyManagerObject::update()
{
}

void PartyManagerObject::fixedUpdate()
{
}

void PartyManagerObject::destroy()
{
}

PartyManagerObject::PartyManagerObject()
{
}

PartyManagerObject::PartyManagerObject(DecisionBoxManager* box)
{
	decisionBox = box;
}

PartyManagerObject::~PartyManagerObject()
{
}
