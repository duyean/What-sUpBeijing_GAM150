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
	case T_NONE:
		pos = { -(float)AEGfxGetWindowWidth() , 0.f };
		entity->transform->setPosition(pos);
		break;
	}

	currFadeTime = maxFadeTime;
}

void TransitionScreen::update()
{
	f64 dt = AEFrameRateControllerGetFrameTime();

	AEVec2 pos = entity->transform->getPosition();
	

	switch (state)
	{
	case T_IN:
		pos.x -= (f32)(transitionSpeed * dt);
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
		pos.x -= (f32)(transitionSpeed * dt);
		entity->transform->setPosition(pos);
		if (pos.x <= -(float)AEGfxGetWindowWidth()) state = DONE;
		break;
	case T_FADE_OUT:
		pos = { 0.f , 0.f };
		entity->transform->setPosition(pos);

		currFadeTime -= (float)dt;
		if (currFadeTime > maxFadeTime / 2)
			ts_opacity = Lerp(0.f, 1.f, (maxFadeTime - currFadeTime) / (maxFadeTime / 2));
		else
		{
			if (ts_color > 1)
				--ts_color;
		}	

		entity->getComponent<Mesh>()->color = { (int)ts_color, (int)ts_color, (int)ts_color, ts_opacity };
		if (currFadeTime <= 0.f)
			state = DONE;
		break;
	case DONE:
		if (scene_t_buffer == true && nextScene != GameStateManager::NUM_SCENES)
		{
			GameStateManager::GetInstance()->NextScene(nextScene);
			nextScene = GameStateManager::NUM_SCENES;
			currFadeTime = maxFadeTime;
			scene_t_buffer = false;
		}
		break;
	}

}

void TransitionScreen::TransitionToScene(GameStateManager::SCENES gs)
{
	scene_t_buffer = true;
	nextScene = gs;
	SetState(T_IN);
}

void TransitionScreen::FadeOutToScene(GameStateManager::SCENES gs)
{
	scene_t_buffer = true;
	nextScene = gs;
	SetState(T_FADE_OUT);
}

void TransitionScreen::fixedUpdate()
{

}

void TransitionScreen::destroy()
{

}


