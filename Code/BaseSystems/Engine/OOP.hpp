#pragma once
#ifndef _OOP_
#include <iostream>
#include <cstdint>
#include <vector>
#include <crtdbg.h> // To check for memory leaks
#include <mutex>
#include <map>
#include <memory>
#include "AEEngine.h"
#include "Colors.hpp"


using namespace std;

class Entity;

class SoloBehavior
{
	//Component class for ECS, inherit this for every component please
	int ActionDepth = 100;
public:

	Entity* entity = nullptr;

	bool isInit = false;
	bool isActive = false;
	bool toDestroy = false;

	template<typename T>
	T* GetComponent();

	void Destroy(Entity& entity);
	void Destroy(Entity* entity);

	SoloBehavior() = default;

	virtual void awake() = 0;
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void fixedUpdate() = 0;
	virtual void destroy() = 0;

	virtual ~SoloBehavior() {}

};


#endif