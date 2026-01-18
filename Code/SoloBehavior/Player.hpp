#pragma once
#ifndef _Player_
#include <iostream>
#include <cstdint>
#include <vector>
#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include "OOP.hpp"
#include "Colors.hpp"
#include "BoxCollider2D.hpp"

using namespace std;

class Player : public SoloBehavior
{
public:

	float health = 100.f;

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	Player() {

	}

	~Player()
	{

	}

private:
	void onHit(BoxCollider2D* other);
	void onStay(BoxCollider2D* other);
	void onExit(BoxCollider2D* other);

};


#endif