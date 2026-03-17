#pragma once
#include "../Engine_WZBJ_Pak.hpp"

enum struct OCCURENCE_ID
{
	TEST_EVENT_1
};

class Occurence
{
	//The name of the occurence
	std::string name;

	//The description of the event
	std::string desc;

	//The effect of picking the first option
	std::function<void()> option1;

	//The effect of picking the second option
	std::function<void()> option2;

	Occurence();
	Occurence(std::string name, std::string desc, std::function<void()> fn1, std::function<void()> fn2);
};

extern std::unordered_map<OCCURENCE_ID, Occurence> eventsDatabase;
extern void InitEventsDatabase();