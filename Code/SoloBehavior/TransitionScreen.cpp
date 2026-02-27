#include "TransitionScreen.hpp"

void TransitionScreen::awake()
{
	enSystem = &EntityManager::getInstance();
}

void TransitionScreen::init()
{
	AEVec2 pos = entity->transform->getPosition();
	switch (state)
	{
	case T_IN:
		pos = { (float)AEGfxGetWindowWidth(), 0.f};
		entity->transform->setPosition(pos);
		break;
	case T_OUT:
		pos = { 0.f , 0.f };
		entity->transform->setPosition(pos);
		break;
	}
}

void TransitionScreen::update()
{
	float dt = AEFrameRateControllerGetFrameTime();

	AEVec2 pos = entity->transform->getPosition();
	

	switch (state)
	{
	case T_IN:
		pos.x -= transitionSpeed * dt;
		entity->transform->setPosition(pos);
		if (t_buffer)
		{
			pos = { (float)AEGfxGetWindowWidth() , 0.f };
			entity->transform->setPosition(pos);
			t_buffer = false;
		}
		if (pos.x < -10.f)
		{
			state = DONE;
		}
		break;
	case T_OUT:
		pos.x -= transitionSpeed * dt;
		entity->transform->setPosition(pos);
		if (pos.x <= -(float)AEGfxGetWindowWidth()) state = DONE;
		break;
	case DONE:
		break;
	}

}

void TransitionScreen::fixedUpdate()
{

}

void TransitionScreen::destroy()
{

}
