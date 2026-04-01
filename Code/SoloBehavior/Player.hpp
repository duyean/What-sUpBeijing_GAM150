/******************************************************************************/
/*!
\file   Player.hpp
\author Tai Qian Yi
\par    Email: t.qianyi\@digipen.edu
\par    DigiPen login: t.qianyi
\par    Course: CSD1451
\par    Section B
\brief  This file contains the declarations of functions for Player class
*/
/******************************************************************************/

#pragma once
#ifndef _Player_
#include <iostream>
#include <cstdint>
#include <vector>
#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include "../BaseSystems/Engine/OOP.hpp"
#include "../BaseSystems/Engine/Colors.hpp"
#include "../BaseSystems/Engine/BoxCollider2D.hpp"

using namespace std;

class Player : public SoloBehavior
{
public:
	//player health
	float health = 100.f;

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	//default cstr
	Player() {}
	//dstr
	~Player(){}

private:
	//player move speed
	float moveSpeed = 500.f;
	//On Hit functions for Box Collider 2D
	void onHit(BoxCollider2D* other);
	void onStay(BoxCollider2D* other);
	void onExit(BoxCollider2D* other);

};


#endif