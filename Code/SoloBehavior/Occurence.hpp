/*!
@file Occurence.hpp
@author Wayne Lion (lion.w)
@course CSD11451
@section B
@Final Project
@date 25/3/26
@brief
This file contains the interface for an Occurence random event
for our game
*//*______________________________________________________________________*/

#pragma once
#include "../Engine_WZBJ_Pak.hpp"

//Forward declaration
class RunManager;

enum struct OCCURENCE_ID
{
	TEST_EVENT_1,
	REWARD_EVENT_1,
	GAMBLING_EVENT_1
};
/*!***********************************************************************
* \class Occurence
* \brief
* The Data to store the various random events for the game during
* exploration phase
*************************************************************************/
class Occurence
{
	public:
	//The name of the occurence
	const char* name;

	//The description of the event
	const char* desc;

	//Text shown for option 1
	const char* option1Text;

	const char* option2Text;

	//The effect of picking the first option
	std::function<void(RunManager*)> option1;

	//The effect of picking the second option
	std::function<void(RunManager*)> option2;

	//Default constructor
	Occurence();

	//Customised constructor
	Occurence(const char* name, const char* desc, const char* op1Text, const char* op2Text, std::function<void(RunManager*)> fn1, std::function<void(RunManager*)> fn2);
};

//Map to store all the occurences in the game
extern std::unordered_map<OCCURENCE_ID, Occurence> eventsDatabase;

/*!***********************************************************************
* \brief
* Initialise all the occurences in the game
*************************************************************************/
extern void InitEventsDatabase();