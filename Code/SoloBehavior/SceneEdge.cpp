#include "SceneEdge.hpp"


//Do collision logic
void SceneEdge::onHit(BoxCollider2D* other)
{
	
	triggerBuffer = true;
}
void SceneEdge::onStay(BoxCollider2D* other)
{

}
void SceneEdge::onExit(BoxCollider2D* other)
{
	triggerBuffer = false;
}

void SceneEdge::awake()
{
	enSystem = &EntityManager::getInstance();
	t_screen = enSystem->FindByNameGLOBAL("TransitionScreen")->getComponent<TransitionScreen>();

	col = entity->getComponent<BoxCollider2D>();
	if (col) {
		col->onCollisionEnter([this](BoxCollider2D* other) { onHit(other); });
		col->onCollisionStay([this](BoxCollider2D* other) { onStay(other); });
		col->onCollisionExit([this](BoxCollider2D* other) { onExit(other); });
	}
}

void SceneEdge::init()
{
	
}

void SceneEdge::update()
{
	switch (type)
	{
	case BASE:
		if (t_screen->GetState() == DONE && changeBuffer)
		{
			GameStateManager::GetInstance()->NextScene(GameStateManager::LEVEL1);
			changeBuffer = false;
		}
		break;
	default:
		break;
	}
}

void SceneEdge::fixedUpdate()
{

}

void SceneEdge::destroy()
{

}
