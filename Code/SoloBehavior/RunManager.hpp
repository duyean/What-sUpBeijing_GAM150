#pragma once
#include "../Code/Engine_WZBJ_Pak.hpp"
#include "../Combat/Blessing/Blessing.hpp"
#include <memory>

class Character;

class RunManager
{
	std::vector<Character*> party;

	std::vector<std::unique_ptr<Blessing>> runBlessings;
public:
	static RunManager& Instance();
	void StartRun();
	void ResetRun();
};