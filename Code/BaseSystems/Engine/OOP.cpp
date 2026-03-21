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
	EntityManager::getInstance().needsCleanup = true;
	entity.toDestroy = true;
}

void SoloBehavior::Destroy(Entity* entity)
{
	//set destroy flag
	EntityManager::getInstance().needsCleanup = true;
	entity->toDestroy = true;
	if (entity->transform->children.size() != 0)
	{
		for (int i = 0; i < entity->transform->children.size(); ++i)
		{
			Destroy(entity->transform->children[i]->entity);
		}
	}
}