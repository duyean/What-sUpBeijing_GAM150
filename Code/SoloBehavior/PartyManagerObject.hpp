/*!************************************************************************
* \file PartyManagerObject.hpp
* \author Tai Yang Tat Bryson
* \par DP email: t.yangtatbryson\@digipen.edu
* \par Course: CSD1451-b
* \brief
*   This file implements functions regarding a SCRAPPED party manager
**************************************************************************/

#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "../Code/SoloBehavior/DecisionBoxManager.hpp"

/*!***********************************************************************
* \class PartyManagerObject
* \brief
*  The SoloBehavior object for the PartyManager
*************************************************************************/
class PartyManagerObject : public SoloBehavior
{
public:
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
	PartyManagerObject();
	/*!***********************************************************************
	* \brief
	*  Overloaded constructor
	* \param[in] box
	*  The DecisionBoxManager related to the PartyManager
	*************************************************************************/
	PartyManagerObject(DecisionBoxManager* box);
	/*!***********************************************************************
	* \brief
	*  Default destructor
	*************************************************************************/
	~PartyManagerObject();
private:
	// The decision box linked to the PartyManager
	DecisionBoxManager* decisionBox{ nullptr };

	/*!***********************************************************************
	* \brief
	*  Logic for BoxCollider2D onHit
	* \param[in] other
	*  The other collider
	* \return
	*  void
	*************************************************************************/
	void onHit(BoxCollider2D* other);
	/*!***********************************************************************
	* \brief
	*  Logic for BoxCollider2D onStay
	* \param[in] other
	*  The other collider
	* \return
	*  void
	*************************************************************************/
	void onStay(BoxCollider2D* other);
	/*!***********************************************************************
	* \brief
	*  Logic for BoxCollider2D onExit
	* \param[in] other
	*  The other collider
	* \return
	*  void
	*************************************************************************/
	void onExit(BoxCollider2D* other);
};

