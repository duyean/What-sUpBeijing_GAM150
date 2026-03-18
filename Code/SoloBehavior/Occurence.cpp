#include "Occurence.hpp"
#include "../SoloBehavior/RunManager.hpp"

Occurence::Occurence() : name("Test"), desc("Test"), option1(nullptr), option2(nullptr) {}

Occurence::Occurence(std::string name, std::string desc, std::string op1Text, std::string op2Text, std::function<void(RunManager*)> fn1, std::function<void(RunManager*)> fn2) : name(name),
desc(desc), option1Text(op1Text), option2Text(op2Text), option1(fn1), option2(fn2) {}

std::unordered_map<OCCURENCE_ID, Occurence> eventsDatabase = {};
void InitEventsDatabase()
{
	eventsDatabase.emplace(OCCURENCE_ID::TEST_EVENT_1, Occurence("Up For A Bet?", "A strange merchant offers you a choice, what do you do?", "Consume 20 currency for a 50% chance of obtaining a random blessing.", "Decline as you do not gamble.",
		[](RunManager* rm) 
		{
			rm->ModifyCurrency(-20);
			std::uniform_real_distribution<double> dist(0.0, 1.0);
			float rng = dist(Game::gen);
			if (rng <= 0.5)
			{
				std::uniform_int_distribution<int> dist(0, !blessingDatabase.size() ? 0 : blessingDatabase.size() - 1);
				auto it = blessingDatabase.begin();
				std::advance(it, dist(Game::gen));
				auto randomBlessing = it->second->Clone();
				RunManager::Instance().AddBlessing(std::move(randomBlessing));

				//Display new blessing
			}
		}, [](RunManager* rm) {}));
}
