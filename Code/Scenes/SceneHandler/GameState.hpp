/******************************************************************************/
/*!
\file   GameState.hpp
\author Tai Qian Yi
\par    Email: t.qianyi\@digipen.edu
\par    DigiPen login: t.qianyi
\par    Course: CSD1451
\par    Section B
\brief  This file contains the declarations of virtual functions for Game states
*/
/******************************************************************************/
#pragma once

class GameState {

private:

public:
	GameState();
	~GameState();

	virtual void Load() { return; }					//Virtual Initialize function
	virtual void Unload() { return; }					  //Virtual Exit function
};