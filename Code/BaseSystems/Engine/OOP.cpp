#include "OOP.hpp"
#include "Entity.hpp"


template<typename T>
T* SoloBehavior::GetComponent()
{
	return entity ? entity->getComponent<T>() : nullptr;
}
