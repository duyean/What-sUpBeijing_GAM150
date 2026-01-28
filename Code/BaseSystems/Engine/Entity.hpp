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
#include "MeshNew.hpp"
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

	void update() {
		for (auto& c : components) {
			if (c->isActive == true)
			{
				c->update();
			}
			
		}
	}

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
	void destroy() {
		for (auto& c : components) {
			c->entity == nullptr;
			c->destroy();
		}
		components.clear();
	}

	public:
	Entity(string Name) { name = Name; }

	Entity() {

	}
	~Entity() {

	}

};

#pragma warning( pop )

#endif