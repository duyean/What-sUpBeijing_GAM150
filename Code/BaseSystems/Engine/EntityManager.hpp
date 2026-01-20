#pragma once
#ifndef _Hierarchy_
#include <iostream>
#include <cstdint>
#include <vector>
#include <crtdbg.h> // To check for memory leaks
#include <mutex>
#include <map>
#include <memory>
#include "AEEngine.h"
#include "OOP.hpp"
#include "Entity.hpp"
#include "Colors.hpp"

using namespace std;


//Singleton class MeshGen Run once before game loop starts
class EntityManager
{
	static EntityManager* instance;

	static mutex mtx;



public:

	Entity* rootEntity = nullptr;

	std::vector<std::unique_ptr<Entity>> entities;

	EntityManager()
	{

	}

	~EntityManager()
	{

	}

public:

	EntityManager(const EntityManager& obj) = delete;

	static EntityManager* getInstance() {
		if (instance == nullptr)
		{
			lock_guard<mutex> lock(mtx);
			if (instance == nullptr) {
				instance = new EntityManager();
			}
		}

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



};



#endif