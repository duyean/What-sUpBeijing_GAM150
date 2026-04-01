/*!
@file Entity.hpp
@author Tan Yifeng, Edmund (t.yifengedmund)
@course CSD11451
@section B
@Final Project GAM 150
@date 01/04/26
@brief
This file contains the Entity class which acts as a game object container,
managing a collection of SoloBehavior components and providing search,
lifecycle, and hierarchy traversal utilities
*//*______________________________________________________________________*/
#pragma once
#ifndef _BaseSys_
#include <iostream>
#include <cstdint>
#include <vector>
#include <crtdbg.h> // To check for memory leaks
#include <mutex>
#include <map>
#include <memory>
#include "AEEngine.h"
#include "ECS.hpp"
#include "Mesh.hpp"
#include "OOP.hpp"
#include "Transform2D.hpp"
#include "Colors.hpp"

#pragma warning( push )
#pragma warning( disable : 4984 )


using namespace std;

class Entity
{
	friend class EntityManager;
private:
	std::vector<std::unique_ptr<SoloBehavior>> components;

protected:

public:
	string name;
	Transform2D* transform = nullptr;
	Mesh* mesh = nullptr;

	bool toDestroy = false;
	bool isActive = true;
	bool allComponentsInit = false;

	/*!***********************************************************************
	* \brief
	* Adds a new component of type T to this entity, enforcing that
	* Transform2D and Mesh are singletons per entity
	* \param[in] args
	* Constructor arguments forwarded to the component
	* \return
	* A raw pointer to the newly created component
	*************************************************************************/
	template<typename T, typename... Args>
	T* addComponent(Args&&... args) {
		static_assert(std::is_base_of_v<SoloBehavior, T>,
			"T must inherit SoloBehavior");

		//Warning C4984 is a false positive prof
		//if you see warning here for if constexpr, i double checked that this is c++17-c++20 compliant and my VS version has a quirk that throws a spurious warning, aka its a false positive by VS :)
		//Enforce singular
		if constexpr (std::is_same_v<T, Transform2D>) {
			if (transform) {
				return transform;
			}
		}
		else if constexpr (std::is_same_v<T, Mesh>) {
			if (mesh) {
				return mesh;
			}
		}

		auto comp = std::make_unique<T>(std::forward<Args>(args)...);
		comp->entity = this;
		T* ptr = comp.get();
		components.push_back(std::unique_ptr<SoloBehavior>(static_cast<SoloBehavior*>(comp.release())));

		if constexpr (std::is_same_v<T, Transform2D>) {
			transform = ptr;
		}
		else if constexpr (std::is_same_v<T, Mesh>) {
			mesh = ptr;
		}

		allComponentsInit = false;
		ptr->isActive = true;
		ptr->isInit = false;
		ptr->awake();
		return ptr;
	}

	/*!***********************************************************************
	* \brief
	* Retrieves the first component of type T attached to this entity
	* \return
	* A raw pointer to the component, or nullptr if not found
	*************************************************************************/
	template<typename T>
	T* getComponent() {
		for (auto& c : components) {
			if (auto ptr = dynamic_cast<T*>(c.get())) {
				return ptr;
			}
		}
		return nullptr;
	}

	//Search by NAME
	/*!***********************************************************************
	* \brief
	* Recursively searches this entity and its children for an entity
	* matching the given name
	* \param[in] searchName
	* The name to search for
	* \return
	* A pointer to the matching entity, or nullptr if not found
	*************************************************************************/
	Entity* FindByName(const std::string& searchName) {
		if (name == searchName) return this;

		if (transform != nullptr)
		{
			for (auto& child : transform->children) {
				if (auto found = child->entity->FindByName(searchName)) {
					return found;
				}
				
			}
		}
		return nullptr;
		
	}

	/*!***********************************************************************
	* \brief
	* Recursively collects all entities with the given name into the
	* provided results vector
	* \param[in] searchName
	* The name to search for
	* \param[out] outResults
	* A vector that will be populated with all matching entities
	*************************************************************************/
	void FindAllByName(const std::string& searchName, std::vector<Entity*>& outResults) {
		if (name == searchName) outResults.push_back(this);
		if (transform != nullptr)
		{
			for (auto& child : transform->children) {
				child->entity->FindAllByName(searchName, outResults);
			}
		}
		
	}


	//Search by Component
	/*!***********************************************************************
	* \brief
	* Recursively searches this entity and its children for the first entity
	* that has a component of type T attached
	* \return
	* A pointer to the matching entity, or nullptr if not found
	*************************************************************************/
	template<typename T>
	Entity* findByComponent() {
		if (getComponent<T>() != nullptr) return this;

		if (transform != nullptr)
		{
			for (auto& child : transform->children) {
				if (auto found = child->entity->findByComponent<T>()) {
					return found;
				}
				
			}

		}
		return nullptr;

	}

	/*!***********************************************************************
	* \brief
	* Recursively collects all entities that have a component of type T
	* into the provided results vector
	* \param[out] outResults
	* A vector that will be populated with all matching entities
	*************************************************************************/
	template<typename T>
	void FindAllWithComponent(std::vector<Entity*>& outResults) {
		if (getComponent<T>() != nullptr)
			outResults.push_back(this);

		if (transform != nullptr)
		{
			for (auto& child : transform->children) {
				child->entity->FindAllWithComponent<T>(outResults);
			
			}
		}
	}

	/*!***********************************************************************
	* \brief
	* Calls init() on all components that have not yet been initialised
	*************************************************************************/
	void init() {
			for (auto& c : components) {
				if (c->isInit == false)
				{
					c->init();
					c->isInit = true;
				}

			}
			allComponentsInit = true;
		
	}

	/*!***********************************************************************
	* \brief
	* Calls update() on all active components each frame
	*************************************************************************/
	void update() {
		for (auto& c : components) {
			if (c->isActive == true)
			{
				c->update();
			}
			
		}
	}

	/*!***********************************************************************
	* \brief
	* Calls fixedUpdate() on all active components at a fixed timestep
	*************************************************************************/
	void fixedUpdate() {
		for (auto& c : components) {
			if (c->isActive == true)
			{
				c->fixedUpdate();
			}
		}
	}

	private:
	//only call the entity manager's delete
	/*!***********************************************************************
	* \brief
	* Destroys all components on this entity and clears the component list.
	* Should only be called through the EntityManager
	*************************************************************************/
	void destroy() {
		for (auto& c : components) {
			c->entity = nullptr;
			c->destroy();
		}
		components.clear();
	}

	public:
	/*!***********************************************************************
	* \brief
	* Constructs an entity with the given name
	* \param[in] Name
	* The name to assign to this entity
	*************************************************************************/
	Entity(string Name) { name = Name; }

	Entity() {

	}
	~Entity() {

	}

};

#pragma warning( pop )

#endif

