#pragma once
#include "../Engine_WZBJ_Pak.hpp"

class RunManager;

enum struct OCCURENCE_ID
{
	TEST_EVENT_1,
	REWARD_EVENT_1,
	GAMBLING_EVENT_1
};

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

	Occurence();
	Occurence(const char* name, const char* desc, const char* op1Text, const char* op2Text, std::function<void(RunManager*)> fn1, std::function<void(RunManager*)> fn2);
};

extern std::unordered_map<OCCURENCE_ID, Occurence> eventsDatabase;
extern void InitEventsDatabase();