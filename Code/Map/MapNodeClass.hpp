#pragma once
/*!************************************************************************
* \file MapNodeClass.hpp
* \author Daniel Tan
* \par DP email: t.daniel@digipen.edu
* \par Course: CSD1451
* \par Section: B
* \brief
*   This file defines a set of node types that can be used in the map, 
*	as well as a MapNode class that contains the node type and its connections to other nodes.
**************************************************************************/

/*!***********************************************************************
* \class NodeType
* \brief
*  The NodeType enum, which contains all the different ID types of nodes that can be used in the map.
*************************************************************************/
enum class NodeType
{
	//standard nodes
	Debug =				 0, //can also represent ungenerated node
	Empty =				 1,
	EnemyEncounter =	 2,
	RandomEvent =		 4,
	FixedEvent =		 5,
	Shop =				 3,

	//special nodes
	Entry =				-1,
	Exit =				-2,  //also represents boss node!!!

	//overlay nodes
	VisionFog =			-11,
	VisionClear =		-12	
};

/*!***********************************************************************
* \class MapNode
* \brief
*  The MapNode class, which contains the node type and its connections to other nodes in it's default compass directions.
*************************************************************************/
class MapNode
{
public:
	bool n, s, e, w; //connections
	NodeType type;
};

