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
	PhysicSystem* phSystem;
public:
    AEVec2 halfExtents;
    bool isTrigger = false;

    // Runtime
    bool overlapping = false;

	BoxCollider2D* itself;

	void onCollisionEnter(const CollisionCallback& cb) { onEnter.push_back(cb); }
    void onCollisionStay(const CollisionCallback& cb) { onStay.push_back(cb); }
    void onCollisionExit(const CollisionCallback& cb) { onExit.push_back(cb); }

	void notifyEnter(BoxCollider2D* other) {
		for (auto& cb : onEnter) cb(other);
	}
	void notifyStay(BoxCollider2D* other) {
		for (auto& cb : onStay) cb(other);
	}
	void notifyExit(BoxCollider2D* other) {
		for (auto& cb : onExit) cb(other);
	}

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	BoxCollider2D() {
		halfExtents.x = 1;
		halfExtents.y = 1;
		itself = this;
	}

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