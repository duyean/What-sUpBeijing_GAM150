/*!
@file CreditsScreen.hpp
@author Tai Qian Yi (t.qianyi)
@course CSD11451
@section B
@Final Project
@date 13/1/26
@brief
This file contains the declarations of functions for the credits screen
*//*______________________________________________________________________*/

#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "../UI_WZBJ_Pak.hpp"

class CreditsScreen : public SoloBehavior
{
private:	
	// pointer to the entitymanager
	EntityManager* enSystem = nullptr;
	// the display
	std::vector<Entity*> prevDisplay;

	// if the credits is displayed
	bool isDisplaying = false;
	// the scroll of the credits
	float scrollOffset = 0.f;
	// starting position of the credits
	float startingPos = -360.f;

	// pointers to entities related to the credits
	Entity* logo = nullptr;
	Entity* title = nullptr;
	Entity* LeftText = nullptr;
	Entity* RightText = nullptr;
	Entity* Footer = nullptr;

public:
	/*!***********************************************************************
	* \brief
	*  This function shows or hides the credits screen
	* \param[in] canShow
	*  If the credits should be shown
	* \return
	*  void
	*************************************************************************/
	void ShowCredits(bool canShow);
	/*!***********************************************************************
	* \brief
	*  Override for SoloBehavior's awake() function
	* \return
	*  void
	*************************************************************************/
	void awake() override;
	/*!***********************************************************************
	* \brief
	*  Override for SoloBehavior's init() function
	* \return
	*  void
	*************************************************************************/
	void init() override;
	/*!***********************************************************************
	* \brief
	*  Override for SoloBehavior's update() function
	* \return
	*  void
	*************************************************************************/
	void update() override;
	/*!***********************************************************************
	* \brief
	*  Override for SoloBehavior's fixedUpdate() function
	* \return
	*  void
	*************************************************************************/
	void fixedUpdate() override;
	/*!***********************************************************************
	* \brief
	*  Override for SoloBehavior's destroy() function
	* \return
	*  void
	*************************************************************************/
	void destroy() override;

	/*!***********************************************************************
	* \brief
	*  This function returns if the credits are currently on display
	* \return
	*  If the credits are displaying
	*************************************************************************/
	bool IsDisplaying() const { return isDisplaying; }
	/*!***********************************************************************
	* \brief
	*  This function adds display entities to a vector
	* \param[in] en
	*  Pointer to an entity to add into the prevDisplay vector
	* \return
	*  void
	*************************************************************************/
	void AddPrevDisplayEntity(Entity* en);
	/*!***********************************************************************
	* \brief
	*  Default constructor
	*************************************************************************/
	CreditsScreen() : isDisplaying(false){}
	/*!***********************************************************************
	* \brief
	*  Default destructor
	*************************************************************************/
	~CreditsScreen() {};
};