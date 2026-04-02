#pragma once
/*!************************************************************************
* \file Map.hpp
* \author Daniel Tan
* \par DP email: t.daniel@digipen.edu
* \par Course: CSD1451
* \par Section: B
* \brief
*   This file defines functions that are related to the Map class.
**************************************************************************/

//Class-based definition and implementation are in MapClass.cpp

//any further functions that do not piggyback off MapClass go below.
/*!***********************************************************************
* \brief
* Checks a MapNode class to see if it is an end node (has only one connection)
* \param[in] node
*  The MapNode to check
* \return
*  bool
*************************************************************************/
bool isEndNode(MapNode node);
