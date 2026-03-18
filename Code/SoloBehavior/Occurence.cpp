#include "Occurence.hpp"

Occurence::Occurence() : name("Test"), desc("Test"), option1(nullptr), option2(nullptr) {}

Occurence::Occurence(std::string name, std::string desc, std::function<void()> fn1, std::function<void()> fn2) : name(name),
desc(desc), option1(fn1), option2(fn2) {}

std::unordered_map<OCCURENCE_ID, Occurence> eventsDatabase = {};
void InitEventsDatabase()
{
	//eventsDatabase.emplace(OCCURENCE_ID::TEST_EVENT_1, Occurence("Up For A Bet?", "A strange merchant offers you a choice, what do you do?",
	//	[]() {}, []() {}));
}
