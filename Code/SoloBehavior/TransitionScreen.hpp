/******************************************************************************/
/*!
\file   TransitionScreen.hpp
\author Tai Qian Yi
\par    Email: t.qianyi\@digipen.edu
\par    DigiPen login: t.qianyi
\par    Course: CSD1451
\par    Section B
\brief  This file contains the declarations of functions for TransitionScreen 
		class
*/
/******************************************************************************/

#pragma once
#ifndef _HealthBar1_
#include <iostream>
#include <cstdint>
#include <vector>
#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include "../BaseSystems/Engine/OOP.hpp"
#include "../BaseSystems/Engine/Colors.hpp"
#include "../BaseSystems/EaseFunctions/Math.hpp"
#include "../BaseSystems/Engine/EntityManager.hpp"
#include "../SceneHandler_WZBJ_Pak.hpp"
#include "../Scenes/SceneHandler/GameStateManager.hpp"

using namespace std;

//enum for the different transition states
enum T_State
{
	T_IN,
	T_OUT,
	T_FADE_OUT,
	T_BLACK_OUT,
	DONE,
	T_NONE
};

class EntityManager;

class TransitionScreen: public SoloBehavior
{
private:
	//transition screen variables
	float transitionSpeed;
	float currFadeTime;
	float maxFadeTime;
	float ts_opacity;
	int ts_color;
	bool t_buffer; // a trigger buffer for the transition screen when calling reset
	bool scene_t_buffer; //scene transition buffer
	GameStateManager::SCENES nextScene = GameStateManager::NUM_SCENES; //default value NUM_SCENES (not a valid scene)
	T_State state;

public:

	EntityManager* enSystem = nullptr;

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;
	/*!***********************************************************************
	\brief This function sets the current transition screen's state to the
		   new state
	\param _state
	new state to set transition screen to
	*************************************************************************/
	void SetState(T_State _state) { state = _state; t_buffer = true; }
	/*!***********************************************************************
	\brief This function activates the transition screen before switching to
		   the new scene
	\param gs
	new game state to transition to
	*************************************************************************/
	void TransitionToScene(GameStateManager::SCENES gs);
	/*!***********************************************************************
	\brief This function makes the transition screen fade from white to black
		   before switching scenes. (USED FOR FINAL LEVEL AFTER BOSS)
	\param gs
	new game state to transition to
	*************************************************************************/
	void FadeOutToScene(GameStateManager::SCENES gs);
	/*!***********************************************************************
	\brief This function makes the transition screen fade to black
		   before switching scenes. (USED WHEN GAME OVER)
	\param gs
	new game state to transition to
	*************************************************************************/
	void BlackOutToScene(GameStateManager::SCENES gs);
	/*!***********************************************************************
	\brief Accessor for the current state the transition screen is on
	\return T_State
	current state of the transition screen
	*************************************************************************/
	T_State GetState() const { return state; }

	//default cstr
	TransitionScreen() = default;
	/*!***********************************************************************
	\brief Non default constructor for transition screen
	\param _state
	current state of the transition screen to set to
	*************************************************************************/
	TransitionScreen(T_State _state)
		:ts_color(255), ts_opacity(1.f), currFadeTime(0.f), maxFadeTime(12.f),
		scene_t_buffer(false), transitionSpeed(1500.f), t_buffer(false), state(_state) {}
	//dstr
	~TransitionScreen(){}

};


#endif