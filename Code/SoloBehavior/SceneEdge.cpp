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
	
}

void SceneEdge::awake()
{
	enSystem = &EntityManager::getInstance();

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
	
}

void SceneEdge::fixedUpdate()
{

}

void SceneEdge::destroy()
{

}
