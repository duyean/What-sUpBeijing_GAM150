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

	virtual void Init() { return; }					//Virtual Initialize function
	virtual void Update(float _dt) { return; }		//Virtual Update function to calculate frame
	virtual void Render() { return; }				//Virtual Render function
	virtual void Exit() { return; }					//Virtual Exit function
};