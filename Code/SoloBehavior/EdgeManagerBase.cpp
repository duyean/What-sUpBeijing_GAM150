
#include "EdgeManagerBase.hpp"

void EdgeManagerBase::awake()
{
	enSystem = &EntityManager::getInstance();
	base_exit = enSystem->FindByNameGLOBAL("baseExit")->getComponent<SceneEdge>();
	ts = enSystem->findByComponentGLOBAL<TransitionScreen>()->getComponent<TransitionScreen>();
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

