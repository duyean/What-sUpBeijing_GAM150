#include "Occurence.hpp"
#include "../SoloBehavior/RunManager.hpp"

Occurence::Occurence() : name("Test"), desc("Test"), option1(nullptr), option2(nullptr), option1Text(""), option2Text("") {}

Occurence::Occurence(const char* name, const char* desc, const char* op1Text, const char* op2Text, std::function<void(RunManager*)> fn1, std::function<void(RunManager*)> fn2) : name(name),
desc(desc), option1Text(op1Text), option2Text(op2Text), option1(fn1), option2(fn2) {}

std::unordered_map<OCCURENCE_ID, Occurence> eventsDatabase = {};
void InitEventsDatabase()
{
	eventsDatabase.clear();
	eventsDatabase.emplace(OCCURENCE_ID::TEST_EVENT_1, Occurence("Up For A Bet?", "A strange merchant offers you a choice, what do you do?", "Consume 20 currency for a 50% chance of obtaining a random blessing.", "Decline as you do not gamble.",
		[](RunManager* rm) 
		{
			rm->ModifyCurrency(-20);
			std::uniform_real_distribution<float> chanceRoll(0.0, 1.0);
			float rng = chanceRoll(Game::gen);
			std::cout << "RNG: " << rng << std::endl;
			if (rng <= 0.5)
			{
				std::uniform_int_distribution<size_t> dist(0, !blessingDatabase.size() ? 0 : blessingDatabase.size() - 1);
				auto it = blessingDatabase.begin();
				std::advance(it, dist(Game::gen));
				auto randomBlessing = it->second->Clone();
				RunManager::Instance().AddBlessing(std::move(randomBlessing));
			}
		}, [](RunManager* rm) {UNREFERENCED_PARAMETER(rm); }));
}
