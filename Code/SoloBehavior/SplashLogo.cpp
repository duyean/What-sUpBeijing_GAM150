#include "SplashLogo.hpp"



void SplashLogo::awake()
{
	
}

void SplashLogo::init()
{
	curSplashTimer = maxSplashTimer;
}

void SplashLogo::update()
{
	float dt = AEFrameRateControllerGetFrameTime();
	curSplashTimer -= dt;

	if (curSplashTimer < 0 || AEInputCheckTriggered(AEVK_SPACE)) {
		GameStateManager::GetInstance()->NextScene(GameStateManager::MAIN_MENU);
		return;
	}


	if (curSplashTimer > maxSplashTimer / 2) {
		splashOpacity = Lerp(0.f, 1.f, (maxSplashTimer - curSplashTimer) / (maxSplashTimer / 2));
	}
	else {
		splashOpacity = Lerp(1.f, 0.f, (maxSplashTimer / 2 - curSplashTimer) / (maxSplashTimer / 2));
	}

	entity->getComponent<Mesh>()->color = { 255, 255, 255, splashOpacity};
}

void SplashLogo::fixedUpdate()
{
}

void SplashLogo::destroy()
{

}
