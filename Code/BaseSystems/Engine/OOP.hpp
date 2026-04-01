/*!
@file OOP.hpp
@author Tan Yifeng, Edmund (t.yifengedmund)
@course CSD11451
@section B
@Final Project GAM 150
@date 01/04/26
@brief
This file contains the SoloBehavior base class which all components must
inherit from, providing the standard component lifecycle interface
*//*______________________________________________________________________*/
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

	/*!***********************************************************************
	* \brief
	* Retrieves a component of type T from the owning entity
	* \return
	* A pointer to the component of type T, or nullptr if not found
	*************************************************************************/
	template<typename T>
	T* GetComponent();

	/*!***********************************************************************
	* \brief
	* Marks the given entity for destruction by reference
	* \param[in] _entity
	* A reference to the entity to destroy
	*************************************************************************/
	void Destroy(Entity& _entity);

	/*!***********************************************************************
	* \brief
	* Marks the given entity for destruction by pointer
	* \param[in] _entity
	* A pointer to the entity to destroy
	*************************************************************************/
	void Destroy(Entity* _entity);

	SoloBehavior() = default;

	/*!***********************************************************************
	* \brief
	* Called once when the component is first created, before init
	*************************************************************************/
	virtual void awake() = 0;

	/*!***********************************************************************
	* \brief
	* Called once before the first update, used for initialisation
	*************************************************************************/
	virtual void init() = 0;

	/*!***********************************************************************
	* \brief
	* Called every frame for game logic updates
	*************************************************************************/
	virtual void update() = 0;

	/*!***********************************************************************
	* \brief
	* Called at a fixed timestep, used for physics-based updates
	*************************************************************************/
	virtual void fixedUpdate() = 0;

	/*!***********************************************************************
	* \brief
	* Called when the component is destroyed, used for cleanup
	*************************************************************************/
	virtual void destroy() = 0;

	virtual ~SoloBehavior() {}

};


#endif

