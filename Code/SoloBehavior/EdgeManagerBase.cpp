
#include "EdgeManagerBase.hpp"
#include "../Code/SoloBehavior/Player.hpp"

void EdgeManagerBase::awake()
{
	enSystem = &EntityManager::getInstance();
	base_exit = enSystem->FindByNameGLOBAL("baseExit")->getComponent<SceneEdge>();
	ts = enSystem->findByComponentGLOBAL<TransitionScreen>()->getComponent<TransitionScreen>();
	player = enSystem->FindByNameGLOBAL("Player");
}

void EdgeManagerBase::UpdateEdges()
{

}

void EdgeManagerBase::init()
{
	
}

void EdgeManagerBase::update()
{
	if (base_exit && base_exit->triggerBuffer)
	{
		player->getComponent<Player>()->canMove = false;
		ts->TransitionToScene(GameStateManager::LEVEL_SCENE);
		base_exit->triggerBuffer = false;
	}
}

void EdgeManagerBase::fixedUpdate()
{

}

void EdgeManagerBase::destroy()
{

}

