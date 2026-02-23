#pragma once
#include "../Code/Engine_WZBJ_Pak.hpp"

class Character;

class RunManager : public SoloBehavior
{
	std::vector<Character*> party;

	//std::vector<Blessing> runBlessings;
public:
	void StartRun();
	void ResetRun();
};