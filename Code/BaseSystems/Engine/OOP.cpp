#include "OOP.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"

template<typename T>
T* SoloBehavior::GetComponent()
{
	return entity ? entity->getComponent<T>() : nullptr;
}

void SoloBehavior::Destroy(Entity& entity)
{
	//set destroy flag
	EntityManager::getInstance()->needsCleanup = true;
	entity.toDestroy = true;
}
