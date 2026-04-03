/*!
@file CurrencyDisplay.hpp
@author Tai Qian Yi (t.qianyi)
@course CSD11451
@section B
@Final Project
@date 13/1/26
@brief
This file contains the declarations of functions for displaying of currency (UNUSED)
*//*______________________________________________________________________*/

#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "../UI_WZBJ_Pak.hpp"

class CurrencyDisplay : public SoloBehavior
{
private:
	// pointer to the entity manager
	EntityManager* enSystem = nullptr;

	/*!***********************************************************************
	* \brief
	*  This function displays currency
	* \return
	*  void
	*************************************************************************/
	void DisplayCurrency();
public:	
	// pointer to textbox that contains the currency
	TextBox* textbox = nullptr;

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
	*  Default constructor
	*************************************************************************/
	CurrencyDisplay() {}
	/*!***********************************************************************
	* \brief
	*  Default destructor
	*************************************************************************/
	~CurrencyDisplay() {}
};