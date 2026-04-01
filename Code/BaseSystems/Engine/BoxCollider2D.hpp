/*!
@file BoxCollider2D.hpp
@author Tan Yifeng, Edmund (t.yifengedmund)
@course CSD11451
@section B
@Final Project GAM 150
@date 01/04/26
@brief
This file contains the BoxCollider2D component which provides axis-aligned
bounding box collision detection with callback support for enter, stay,
and exit collision events
*//*______________________________________________________________________*/
#pragma once
#ifndef _BoxCollider2D_
#include <iostream>
#include <cstdint>
#include <vector>
#include <functional>
#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include "OOP.hpp"
#include "Colors.hpp"

using namespace std;

class PhysicSystem;

class BoxCollider2D : public SoloBehavior
{
public:
	using CollisionCallback = std::function<void(BoxCollider2D* other)>;

private:
	std::vector<CollisionCallback> onEnter, onStay, onExit;
	PhysicSystem* phSystem = nullptr;
public:
    AEVec2 halfExtents;
    bool isTrigger = false;

    // Runtime
    bool overlapping = false;

	BoxCollider2D* itself;

	/*!***********************************************************************
	* \brief
	* Registers a callback to be invoked when a collision begins with another collider
	* \param[in] cb
	* The callback function to register, receiving the other BoxCollider2D as a parameter
	*************************************************************************/
	void onCollisionEnter(const CollisionCallback& cb) { onEnter.push_back(cb); }

	/*!***********************************************************************
	* \brief
	* Registers a callback to be invoked each frame while a collision persists
	* \param[in] cb
	* The callback function to register, receiving the other BoxCollider2D as a parameter
	*************************************************************************/
    void onCollisionStay(const CollisionCallback& cb) { onStay.push_back(cb); }

	/*!***********************************************************************
	* \brief
	* Registers a callback to be invoked when a collision ends with another collider
	* \param[in] cb
	* The callback function to register, receiving the other BoxCollider2D as a parameter
	*************************************************************************/
    void onCollisionExit(const CollisionCallback& cb) { onExit.push_back(cb); }

	/*!***********************************************************************
	* \brief
	* Dispatches all registered onCollisionEnter callbacks for a given collider
	* \param[in] other
	* A pointer to the other BoxCollider2D that entered collision
	*************************************************************************/
	void notifyEnter(BoxCollider2D* other) {
		for (auto& cb : onEnter) cb(other);
	}

	/*!***********************************************************************
	* \brief
	* Dispatches all registered onCollisionStay callbacks for a given collider
	* \param[in] other
	* A pointer to the other BoxCollider2D that is staying in collision
	*************************************************************************/
	void notifyStay(BoxCollider2D* other) {
		for (auto& cb : onStay) cb(other);
	}

	/*!***********************************************************************
	* \brief
	* Dispatches all registered onCollisionExit callbacks for a given collider
	* \param[in] other
	* A pointer to the other BoxCollider2D that exited collision
	*************************************************************************/
	void notifyExit(BoxCollider2D* other) {
		for (auto& cb : onExit) cb(other);
	}

	/*!***********************************************************************
	* \brief
	* Called once when the component is first created, before init.
	* Registers this collider with the PhysicSystem
	*************************************************************************/
	void awake() override;

	/*!***********************************************************************
	* \brief
	* Called once before the first update, used for initialisation
	*************************************************************************/
	void init() override;

	/*!***********************************************************************
	* \brief
	* Called every frame
	*************************************************************************/
	void update() override;

	/*!***********************************************************************
	* \brief
	* Called at a fixed timestep, used for physics-based updates
	*************************************************************************/
	void fixedUpdate() override;

	/*!***********************************************************************
	* \brief
	* Called when the component is destroyed. Unregisters this collider
	* from the PhysicSystem
	*************************************************************************/
	void destroy() override;

	/*!***********************************************************************
	* \brief
	* Default constructor, sets half extents to (1, 1)
	*************************************************************************/
	BoxCollider2D() {
		halfExtents.x = 1;
		halfExtents.y = 1;
		itself = this;
	}

	/*!***********************************************************************
	* \brief
	* Constructs a BoxCollider2D with the given half extents
	* \param[in] halfExtentX
	* The half-width of the collider along the X axis
	* \param[in] halfExtentY
	* The half-height of the collider along the Y axis
	*************************************************************************/
	BoxCollider2D(float halfExtentX, float halfExtentY) {
		halfExtents.x = halfExtentX;
		halfExtents.y = halfExtentY;
		itself = this;
	}

	~BoxCollider2D()
	{

	}



};


#endif

