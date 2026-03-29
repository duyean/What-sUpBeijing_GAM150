#include "OOP.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"

template<typename T>
T* SoloBehavior::GetComponent()
{
	return entity ? entity->getComponent<T>() : nullptr;
}

void SoloBehavior::Destroy(Entity& _entity)
{
	//set destroy flag
	EntityManager::getInstance().needsCleanup = true;
	_entity.toDestroy = true;
}

void SoloBehavior::Destroy(Entity* _entity)
{
	//set destroy flag
	EntityManager::getInstance().needsCleanup = true;
	_entity->toDestroy = true;
	if (_entity->transform->children.size() != 0)
	{
		for (int i = 0; i < _entity->transform->children.size(); ++i)
		{
			Destroy(_entity->transform->children[i]->entity);
		}
	}
}