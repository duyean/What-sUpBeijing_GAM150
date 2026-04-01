/*!
@file EntityManager.hpp
@author Tan Yifeng, Edmund (t.yifengedmund)
@course CSD11451
@section B
@Final Project GAM 150
@date 01/04/26
@brief
This file contains the EntityManager singleton class which manages the
lifetime and lookup of all entities in the scene
*//*______________________________________________________________________*/
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

	/*!***********************************************************************
	* \brief
	* Returns the singleton instance of the EntityManager
	* \return
	* A reference to the single EntityManager instance
	*************************************************************************/
	static EntityManager& getInstance() {

		static EntityManager instance;
		return instance;
	}

	/*!***********************************************************************
	* \brief
	* Searches the top-level entity list by name, excluding entities marked
	* for destruction. Does not search into children
	* \param[in] Name
	* The name of the entity to find
	* \return
	* A pointer to the matching entity, or nullptr if not found
	*************************************************************************/
	Entity* FindByNameGLOBAL(const std::string& Name)
	{
		//Only searches base parent, use recursive search from root entity for children
		for (const auto& end : entities)
		{
			if (end->name == Name && end->toDestroy == false)
			{
				return end.get();
			}
		}
		return nullptr;
	}

	//Search by Component
	/*!***********************************************************************
	* \brief
	* Searches the top-level entity list for the first entity that has a
	* component of type T, excluding entities marked for destruction.
	* Does not search into children
	* \return
	* A pointer to the matching entity, or nullptr if not found
	*************************************************************************/
	template<typename T>
	Entity* findByComponentGLOBAL() {
		
		//Only searches base parent, use recursive search from root entity for children
		for (const auto& end : entities)
		{
			if (end->getComponent<T>() != nullptr && end->toDestroy == false)
			{
				return end.get();
			}
		}
		return nullptr;

	}

	/*!***********************************************************************
	* \brief
	* Removes all entities flagged with toDestroy from the entity list,
	* calling destroy() on each before removal
	*************************************************************************/
	void clearAllDestroyed() {

		std::erase_if(entities, [](auto& entity) {
			if (entity->toDestroy) {
				entity->destroy();
				return true;
			}
			return false;
			});
	}

	/*!***********************************************************************
	* \brief
	* Marks all entities for destruction and immediately clears them all
	*************************************************************************/
	void forceClearAllDestroyed() {

		for (size_t i = 0; i < entities.size(); i++)
		{
			entities[i]->toDestroy = true;
		}
		clearAllDestroyed();
	}

	/*!***********************************************************************
	* \brief
	* Efficiently removes entities flagged for destruction using swap-and-pop.
	* Should be called after all draw layers are complete. Skips the operation
	* if no cleanup is needed
	*************************************************************************/
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

