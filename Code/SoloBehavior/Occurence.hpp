#pragma once
#include "../Engine_WZBJ_Pak.hpp"

class RunManager;

enum struct OCCURENCE_ID
{
	TEST_EVENT_1
};

class Occurence
{
	public:
	//The name of the occurence
	std::string name;

	//The description of the event
	std::string desc;

	//Text shown for option 1
	std::string option1Text;

	std::string option2Text;

	//The effect of picking the first option
	std::function<void(RunManager*)> option1;

	//The effect of picking the second option
	std::function<void(RunManager*)> option2;

	Occurence();
	Occurence(std::string name, std::string desc, std::string op1Text, std::string op2Text, std::function<void(RunManager*)> fn1, std::function<void(RunManager*)> fn2);
};

extern std::unordered_map<OCCURENCE_ID, Occurence> eventsDatabase;
extern void InitEventsDatabase();