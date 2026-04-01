/*!
@file PhysicSystem.hpp
@author Tan Yifeng, Edmund (t.yifengedmund)
@course CSD11451
@section B
@Final Project GAM 150
@date 01/04/26
@brief
This file contains the PhysicSystem singleton class which manages AABB
collision detection between BoxCollider2D components, including broad phase
and narrow phase processing
*//*______________________________________________________________________*/
#pragma once
#ifndef _Physics_
#include <iostream>
#include <cstdint>
#include <vector>
#include <crtdbg.h> // To check for memory leaks
#include <mutex>
#include <map>
#include <memory>
#include <algorithm>
#include "AEEngine.h"
#include "OOP.hpp"
#include "Entity.hpp"
#include "Colors.hpp"
#include "BoxCollider2D.hpp"

using namespace std;

struct ColliderPair {
	BoxCollider2D* a;
	BoxCollider2D* b;

	bool operator==(const ColliderPair& other) const {
		return (a == other.a && b == other.b);
	}
};

//Singleton class PhysicSystem Run once before game loop starts
class PhysicSystem
{

	std::vector<BoxCollider2D*> colliders;

	std::vector<ColliderPair> potentialPairs;

	// Persistent collision state
	std::vector<ColliderPair> overlappingPairs;

public:

	/*!***********************************************************************
	* \brief
	* Registers a BoxCollider2D with the physics system so it participates
	* in collision detection
	* \param[in] c
	* A pointer to the BoxCollider2D to register
	*************************************************************************/
	void registerCollider(BoxCollider2D* c) {
		colliders.push_back(c);
	}

	/*!***********************************************************************
	* \brief
	* Removes a BoxCollider2D from the physics system so it no longer
	* participates in collision detection
	* \param[in] c
	* A pointer to the BoxCollider2D to unregister
	*************************************************************************/
	void unregisterCollider(BoxCollider2D* c) {
		colliders.erase(
			std::remove(colliders.begin(), colliders.end(), c),
			colliders.end()
		);
	}

	/*!***********************************************************************
	* \brief
	* Checks whether two colliders were overlapping in the previous frame
	* \param[in] a
	* Pointer to the first BoxCollider2D
	* \param[in] b
	* Pointer to the second BoxCollider2D
	* \return
	* True if the pair was overlapping in the previous frame
	*************************************************************************/
	bool wasOverlapping(BoxCollider2D* a, BoxCollider2D* b);

	/*!***********************************************************************
	* \brief
	* Sets the persistent overlap state between two colliders
	* \param[in] a
	* Pointer to the first BoxCollider2D
	* \param[in] b
	* Pointer to the second BoxCollider2D
	* \param[in] overlapping
	* True to mark the pair as overlapping, false to remove the overlap record
	*************************************************************************/
	void setOverlapState(BoxCollider2D* a, BoxCollider2D* b, bool overlapping);

	/*!***********************************************************************
	* \brief
	* Tests whether two axis-aligned bounding boxes are overlapping
	* \param[in] a
	* Pointer to the first BoxCollider2D
	* \param[in] b
	* Pointer to the second BoxCollider2D
	* \return
	* True if the two AABBs overlap
	*************************************************************************/
	bool aabbOverlap(BoxCollider2D* a, BoxCollider2D* b);

	/*!***********************************************************************
	* \brief
	* Tests a single collider pair and dispatches the appropriate enter,
	* stay, or exit collision callbacks
	* \param[in] a
	* Pointer to the first BoxCollider2D
	* \param[in] b
	* Pointer to the second BoxCollider2D
	*************************************************************************/
	void testPair(BoxCollider2D* a, BoxCollider2D* b);

	/*!***********************************************************************
	* \brief
	* Generates the list of potential collider pairs to be tested in the
	* narrow phase
	*************************************************************************/
	void broadPhase();

	/*!***********************************************************************
	* \brief
	* Tests all potential pairs from the broad phase for actual AABB overlap
	* and dispatches collision callbacks accordingly
	*************************************************************************/
	void narrowPhase();

	/*!***********************************************************************
	* \brief
	* Runs the full physics update for a single fixed timestep, executing
	* both the broad and narrow phase collision passes
	* \param[in] dt
	* The fixed delta time in seconds
	*************************************************************************/
	void fixedUpdate(double dt);

private:
	PhysicSystem()
	{

	}

	~PhysicSystem()
	{

	}

public:

	PhysicSystem(const PhysicSystem&) = delete;
	PhysicSystem& operator=(const PhysicSystem&) = delete;

	/*!***********************************************************************
	* \brief
	* Returns the singleton instance of PhysicSystem
	* \return
	* A reference to the single PhysicSystem instance
	*************************************************************************/
	static PhysicSystem& getInstance() {

		static PhysicSystem instance;
		return instance;
	}




};



#endif

