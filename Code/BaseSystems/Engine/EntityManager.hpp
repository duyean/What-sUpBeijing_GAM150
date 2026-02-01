#pragma once
#ifndef _Hierarchy_
#include <iostream>
#include <cstdint>
#include <vector>
#include <crtdbg.h> // To check for memory leaks
#include <mutex>
#include <map>
#include <memory>
#include <algorithm> 
#include "AEEngine.h"
#include "Entity.hpp"

using namespace std;


//Singleton class MeshGen Run once before game loop starts
class EntityManager
{

public:

	Entity* rootEntity = nullptr;
	bool needsCleanup = false;

	std::vector<std::unique_ptr<Entity>> entities;



public:


	EntityManager(const EntityManager&) = delete;
	EntityManager& operator=(const EntityManager&) = delete;

	static EntityManager& getInstance() {

		static EntityManager instance;
		return instance;
	}

	Entity* FindByNameGLOBAL(const std::string& Name)
	{
		//Only searches base parent, use recursive search from root entity for children
		for (const auto& end : entities)
		{
			if (end->name == Name)
			{
				return end.get();
			}
		}
		return nullptr;
	}

	//Search by Component
	template<typename T>
	Entity* findByComponentGLOBAL() {
		
		//Only searches base parent, use recursive search from root entity for children
		for (const auto& end : entities)
		{
			if (end->getComponent<T>() != nullptr)
			{
				return end.get();
			}
		}
		return nullptr;

	}

	void clearAllDestroyed() {

		std::erase_if(entities, [](auto& entity) {
			if (entity->toDestroy) {
				entity->destroy();
				return true;
			}
			return false;
			});
	}

	//use this after drawing layers is complete
	void optimizedDeletion()
	{
			if (!needsCleanup) return;

			for (size_t i = 0; i < entities.size(); ) {
				if (entities[i]->toDestroy) {
					entities[i]->destroy();
					entities[i] = std::move(entities.back());

					entities.pop_back();
				}
				else {
					++i;
				}
			}
			needsCleanup = false;
	}

private:

	EntityManager()
	{

	}

	~EntityManager()
	{

	}

};



#endif