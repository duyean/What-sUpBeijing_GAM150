#include "Player.hpp"
#include "../BaseSystems/Engine/EntityManager.hpp"

BoxCollider2D* col;

//Do collision logic
void Player::onHit(BoxCollider2D* other)
{
	
}
void Player::onStay(BoxCollider2D* other)
{
	//Temp code for solo project
	if (other->entity->name == "BUTTONGREEN")
	{
		if (health < 100.f)
		{
			health += 1.f;
		}

	}
	else if (other->entity->name == "BUTTONRED")
	{
		if (health > 0.f)
		{
			health -= 1.f;
		}
	}

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
	if (AEInputCheckCurr(AEVK_W))
	{
		AEVec2 pos = entity->transform->getPosition();
		pos.y += 10.f;
		entity->transform->setPosition(pos);
	}
	if (AEInputCheckCurr(AEVK_S))
	{
		AEVec2 pos = entity->transform->getPosition();
		pos.y -= 10.f;
		entity->transform->setPosition(pos);
	}
	if (AEInputCheckCurr(AEVK_A))
	{
		AEVec2 pos = entity->transform->getPosition();
		pos.x -= 10.f;
		entity->transform->setPosition(pos);
	}
	if (AEInputCheckCurr(AEVK_D))
	{
		AEVec2 pos = entity->transform->getPosition();
		pos.x += 10.f;
		entity->transform->setPosition(pos);
	}

}

void Player::fixedUpdate()
{

}

void Player::destroy()
{

}
