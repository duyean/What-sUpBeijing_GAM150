#include "Player.hpp"
#include "../BaseSystems/Engine/EntityManager.hpp"

BoxCollider2D* col;

//Do collision logic
void Player::onHit(BoxCollider2D* other)
{
	
}
void Player::onStay(BoxCollider2D* other)
{

}
void Player::onExit(BoxCollider2D* other)
{

}

void Player::awake()
{
	col = entity->getComponent<BoxCollider2D>();
	if (col) {
		col->onCollisionEnter([this](BoxCollider2D* other) { onHit(other); });
		col->onCollisionStay([this](BoxCollider2D* other) { onStay(other); });
		col->onCollisionExit([this](BoxCollider2D* other) { onExit(other); });
	}
}


void Player::init()
{

}

void Player::update()
{
	float dt = AEFrameRateControllerGetFrameTime();
	AEVec2 pos = entity->transform->getPosition();

	if (AEInputCheckCurr(AEVK_W))
	{
		pos.y += moveSpeed * dt;
		entity->transform->setPosition(pos);
	}
	if (AEInputCheckCurr(AEVK_S))
	{
		pos.y -= moveSpeed * dt;
		entity->transform->setPosition(pos);
	}
	if (AEInputCheckCurr(AEVK_A))
	{
		pos.x -= moveSpeed * dt;
		entity->transform->setPosition(pos);
	}
	if (AEInputCheckCurr(AEVK_D))
	{
		pos.x += moveSpeed * dt;
		entity->transform->setPosition(pos);
	}

	pos.y = AEClamp(pos.y, -400, 400);
	pos.x = AEClamp(pos.x, -775, 775);
	entity->transform->setPosition(pos);
}

void Player::fixedUpdate()
{

}

void Player::destroy()
{

}
