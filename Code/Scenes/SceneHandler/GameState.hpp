/*!
@file GameState.h
@author Tai Qian Yi (t.qianyi)
@course CSD11451
@section B
@Final Project
@date 12/1/26
@brief
This file contains the declarations of virtual functions for Game states
*//*______________________________________________________________________*/
#pragma once

class GameState {

private:

public:
	GameState();
	~GameState();

	virtual void Load() { return; }					//Virtual Initialize function
	virtual void Unload() { return; }					//Virtual Exit function
};