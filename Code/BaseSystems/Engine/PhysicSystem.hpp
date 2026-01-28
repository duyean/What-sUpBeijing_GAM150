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
	

	void registerCollider(BoxCollider2D* c) {
		colliders.push_back(c);
	}

	void unregisterCollider(BoxCollider2D* c) {
		colliders.erase(
			std::remove(colliders.begin(), colliders.end(), c),
			colliders.end()
		);
	}

	bool wasOverlapping(BoxCollider2D* a, BoxCollider2D* b);

	void setOverlapState(BoxCollider2D* a, BoxCollider2D* b, bool overlapping);

	bool aabbOverlap(BoxCollider2D* a, BoxCollider2D* b);

	void testPair(BoxCollider2D* a, BoxCollider2D* b);


	void broadPhase();

	void narrowPhase();

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

	static PhysicSystem& getInstance() {

		static PhysicSystem instance;
		return instance;
	}




};



#endif