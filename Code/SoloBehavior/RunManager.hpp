#pragma once
#include "../Code/Engine_WZBJ_Pak.hpp"
#include "../Combat/Blessing/Blessing.hpp"
#include <memory>

class Character;

class RunManager : public SoloBehavior
{
	std::vector<Character*> party;

	std::vector<std::unique_ptr<Blessing>> runBlessings;
public:
	void StartRun();
	void ResetRun();
};