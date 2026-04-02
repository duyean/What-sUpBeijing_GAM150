#pragma once
#include "NavigationDataClass.hpp"
/*!************************************************************************
* \file NavigationData.hpp
* \author Daniel Tan
* \par DP email: t.daniel@digipen.edu
* \par Course: CSD1451
* \par Section: B
* \brief
*   This file defines a set of functions that are related to the NavigationData class.
**************************************************************************/

//Class-based definition and implementation are in NavigationData.cpp

//any further functions that do not piggyback off NavigationDataClass go below.

/*!***********************************************************************
* \brief
*  Moves the player to the new x and y position on the playMap, and updates the current node information in the NavigationData class
* \param[in] data
*  The data object containing the current map and player position information to be manipulated and updated
* \param[in] newX
*  The new x <Horizontal> position to move the player to on the playMap
* \param[in] newY
*  The new y <Vertical> position to move the player to on the playMap
* \return
*  void
*************************************************************************/
void TravelNode(NavigationData& data, int newX, int newY);
/*!***********************************************************************
* \brief
*  Debug function that prints the current node information to the console, including the current player position and the node type of the current node on the playMap
* \param[in] data
*  The data object containing the current map and player position information to be read
* \return
*  void (THE RETURN IS IN THE DEBUG CONSOLE THAT NEEDS TO BE TURNED ON TO SEE)
*************************************************************************/
void GetCurrentNodeInfo(NavigationData& data);