#include "SceneEdge.hpp"



//Do collision logic
void SceneEdge::onHit(BoxCollider2D* other)
{
	std::cout << other->entity->name << "collided with Scene edge " << entity->name
		<< ", making Scene edge " << entity->name <<"'s value become: " << triggerBuffer << "!!!!!" << std::endl;
	if (other->entity->name == "Player")
	{
		triggerBuffer = true;
	}		
}
void SceneEdge::onStay(BoxCollider2D* other)
{

}
void SceneEdge::onExit(BoxCollider2D* other)
{
	if (other->entity->name == "Player")
		triggerBuffer = false;
}

void SceneEdge::awake()
{

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
