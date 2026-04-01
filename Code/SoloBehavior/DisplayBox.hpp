/*!
@file DisplayBox.hpp
@author Wayne Lion (lion.w)
@course CSD11451
@section B
@Final Project
@date 25/2/26
@brief
This file contains the interface for a Display Box entity 
for our game.
*//*______________________________________________________________________*/
#pragma once
#include "../Engine_WZBJ_Pak.hpp"

class DisplayBox : public SoloBehavior
{
	//Timer for the delay to allow players to click to close
	double onClickDestroyTimer;

	//The header text at the very top.
	const char* header;

	//The title text
	const char* title;

	//The description text
	const char* desc;

	//The footer text at the very bottom.
	const char* footer;

	//A vector to store sub-entities such that all can be destroyed
	std::vector<Entity*> children;
public:

	//Default constructor
	DisplayBox();

	//Customised constructor
	DisplayBox(const char* head, const char* t, const char* d, const char* foot);

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;
};