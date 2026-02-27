/*!
@file RunManager.hpp
@author Wayne Lion (lion.w)
@course CSD11451
@section B
@Final Project
@date 25/2/26
@brief
This file contains the interface for a Run Manager for our game.
*//*______________________________________________________________________*/

#pragma once
#include "../Code/Engine_WZBJ_Pak.hpp"
#include "../Combat/Blessing/Blessing.hpp"
#include <memory>

//Forward declare the character class
class Character;

class RunManager
{
	//Stores the current characters in the player's party
	std::vector<Character*> party;

	//Stores the current blessings obtained upon the current run
	std::vector<std::unique_ptr<Blessing>> runBlessings;
public:

	//Singleton accessor for this class
	static RunManager& Instance();

	//Starts a new run
	void StartRun();

	//Ends the current run
	void ResetRun();

	//Add a blessing to the current run
	void AddBlessing(std::unique_ptr<Blessing> blessing);

	//Get the current list of blessings
	const std::vector<std::unique_ptr<Blessing>>& GetBlessings() const;
};