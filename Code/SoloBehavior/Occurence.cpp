#include "Occurence.hpp"
#include "../SoloBehavior/RunManager.hpp"
#include "../UI_WZBJ_Pak.hpp"

Occurence::Occurence() : name("Test"), desc("Test"), option1(nullptr), option2(nullptr), option1Text(""), option2Text("") {}

Occurence::Occurence(const char* name, const char* desc, const char* op1Text, const char* op2Text, std::function<void(RunManager*)> fn1, std::function<void(RunManager*)> fn2) : name(name),
desc(desc), option1Text(op1Text), option2Text(op2Text), option1(fn1), option2(fn2) {}

std::unordered_map<OCCURENCE_ID, Occurence> eventsDatabase = {};
void InitEventsDatabase()
{
	eventsDatabase.clear();
	eventsDatabase.emplace(OCCURENCE_ID::TEST_EVENT_1, Occurence("Up For A Bet?", "A strange merchant offers you a choice, what do you do?", "50% chance of obtaining a random blessing.", "Decline as you do not gamble. Get 10 currency",
		[](RunManager*) 
		{
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
			else
			{
				AEVec2 pos = { 0, 0 };
				AEVec2 scale = { AEGfxGetWindowWidth() * 0.8f, AEGfxGetWindowHeight() * 0.8f };

				auto displayBox = std::make_unique<Entity>("DisplayBox");
				displayBox->addComponent<Transform2D>(pos, scale, 0.f);
				displayBox->addComponent<Mesh>("Box", Color(50, 50, 50, 0.9f), 1002, MeshType::BOX_B);
				displayBox->addComponent<DisplayBox>("Event Outcome", "Nothing Happened", "Better Luck Next Time", "-- Click To Continue --");
				EntityManager::getInstance().rootEntity->transform->AddChild(displayBox->transform);
				EntityManager::getInstance().entities.push_back(std::move(displayBox));
			}
		}, [](RunManager* rm) {rm->ModifyCurrency(10); }));

	eventsDatabase.emplace(OCCURENCE_ID::GAMBLING_EVENT_1, Occurence("Lottery Ticket?", "You stumbled upon a scratch ticket. What do you do?", "Try your hand to win BIG!", "Throw the ticket away, you never win these things anyway.",
		[](RunManager*)
		{
			std::uniform_real_distribution<float> outcome(0.f, 1.f);
			float rng = outcome(Game::gen);
			if (rng <= 0.02)
			{
				AEVec2 pos = { 0, 0 };
				AEVec2 scale = { AEGfxGetWindowWidth() * 0.8f, AEGfxGetWindowHeight() * 0.8f };

				auto displayBox = std::make_unique<Entity>("DisplayBox");
				displayBox->addComponent<Transform2D>(pos, scale, 0.f);
				displayBox->addComponent<Mesh>("Box", Color(50, 50, 50, 0.9f), 1002, MeshType::BOX_B);
				displayBox->addComponent<DisplayBox>("Event Outcome", "Amazing Luck! You won it big indeed!", "+10,000 Credits, +1 Mystery Gift", "-- Click To Continue --");
				EntityManager::getInstance().rootEntity->transform->AddChild(displayBox->transform);
				EntityManager::getInstance().entities.push_back(std::move(displayBox));
			}
			else
			{
				AEVec2 pos = { 0, 0 };
				AEVec2 scale = { AEGfxGetWindowWidth() * 0.8f, AEGfxGetWindowHeight() * 0.8f };

				auto displayBox = std::make_unique<Entity>("DisplayBox");
				displayBox->addComponent<Transform2D>(pos, scale, 0.f);
				displayBox->addComponent<Mesh>("Box", Color(50, 50, 50, 0.9f), 1002, MeshType::BOX_B);
				displayBox->addComponent<DisplayBox>("Event Outcome", "Nothing Happened", "Better Luck Next Time", "-- Click To Continue --");
				EntityManager::getInstance().rootEntity->transform->AddChild(displayBox->transform);
				EntityManager::getInstance().entities.push_back(std::move(displayBox));
			}
		}, [](RunManager* rm) {rm->ModifyCurrency(0); /*Dummy Line*/ }));

	eventsDatabase.emplace(OCCURENCE_ID::REWARD_EVENT_1, Occurence("A Mysterious Box", "You stumbled upon a treasure chest. What do you do?", "Open the chest, unpredictable outcome.", "Sell the chest. Get 25 currency.",
		[](RunManager* rm)
		{
			std::uniform_int_distribution<int> outcome(0, 3);
			int eventSelected = outcome(Game::gen);
			switch (eventSelected)
			{
				//Get random blessing
			case (0):
			{
				std::uniform_int_distribution<size_t> dist(0, !blessingDatabase.size() ? 0 : blessingDatabase.size() - 1);
				auto it = blessingDatabase.begin();
				std::advance(it, dist(Game::gen));
				auto randomBlessing = it->second->Clone();
				RunManager::Instance().AddBlessing(std::move(randomBlessing));
				break;
			}
			//Get currency
			case (1):
			{
				rm->ModifyCurrency(50);
				AEVec2 pos = { 0, 0 };
				AEVec2 scale = { AEGfxGetWindowWidth() * 0.8f, AEGfxGetWindowHeight() * 0.8f };

				auto displayBox = std::make_unique<Entity>("DisplayBox");
				displayBox->addComponent<Transform2D>(pos, scale, 0.f);
				displayBox->addComponent<Mesh>("Box", Color(50, 50, 50, 0.9f), 1002, MeshType::BOX_B);
				displayBox->addComponent<DisplayBox>("Event Outcome", "You have found a stash of coins!", "+50 Currency", "-- Click To Continue --");
				EntityManager::getInstance().rootEntity->transform->AddChild(displayBox->transform);
				EntityManager::getInstance().entities.push_back(std::move(displayBox));
				break;
			}
			//Weaken Enemies
			case (2):
			{
				AEVec2 pos = { 0, 0 };
				AEVec2 scale = { AEGfxGetWindowWidth() * 0.8f, AEGfxGetWindowHeight() * 0.8f };

				auto displayBox = std::make_unique<Entity>("DisplayBox");
				displayBox->addComponent<Transform2D>(pos, scale, 0.f);
				displayBox->addComponent<Mesh>("Box", Color(50, 50, 50, 0.9f), 1002, MeshType::BOX_B);
				displayBox->addComponent<DisplayBox>("Event Outcome", "You found some valuable enemy intel.", "Enemy has been weakened.", "-- Click To Continue --");
				EntityManager::getInstance().rootEntity->transform->AddChild(displayBox->transform);
				EntityManager::getInstance().entities.push_back(std::move(displayBox));
				rm->ModifyEnemyDifficulty(-2);
				break;
			}
			//Chest explosion
			case (3):
			{
				AEVec2 pos = { 0, 0 };
				AEVec2 scale = { AEGfxGetWindowWidth() * 0.8f, AEGfxGetWindowHeight() * 0.8f };

				auto displayBox = std::make_unique<Entity>("DisplayBox");
				displayBox->addComponent<Transform2D>(pos, scale, 0.f);
				displayBox->addComponent<Mesh>("Box", Color(50, 50, 50, 0.9f), 1002, MeshType::BOX_B);
				displayBox->addComponent<DisplayBox>("Event Outcome", "The chest exploded! It was a trap!", "100 Currency Lost", "-- Click To Continue --");
				EntityManager::getInstance().rootEntity->transform->AddChild(displayBox->transform);
				EntityManager::getInstance().entities.push_back(std::move(displayBox));
				rm->ModifyCurrency(-100);
				break;
			}
			}
		}, [](RunManager* rm) {rm->ModifyCurrency(25); }));
}
