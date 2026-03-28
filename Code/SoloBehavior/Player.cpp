#include "Player.hpp"
#include "../BaseSystems/Engine/EntityManager.hpp"
#include "../Code/SoloBehavior/RunManager.hpp"

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
	RunManager::Instance().playerCanMove = true;
}

void Player::update()
{
	float dt = (float)AEFrameRateControllerGetFrameTime();
	AEVec2 pos = entity->transform->getPosition();

	if (RunManager::Instance().playerCanMove && !RunManager::Instance().game_paused)
	{
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
	}
	

	pos.y = AEClamp(pos.y, -AEGfxGetWindowHeight() / 2.f + (entity->transform->getScale().y / 2.f), AEGfxGetWindowHeight() / 2.f - (entity->transform->getScale().y / 2.f));
	pos.x = AEClamp(pos.x, -AEGfxGetWindowWidth() / 2.f + (entity->transform->getScale().x / 2.f), AEGfxGetWindowWidth() / 2.f - (entity->transform->getScale().x / 2.f));
	entity->transform->setPosition(pos);
}

void Player::fixedUpdate()
{

}

void Player::destroy()
{

}
