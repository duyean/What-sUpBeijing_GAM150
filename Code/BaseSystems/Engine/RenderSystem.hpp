/*!
@file RenderSystem.hpp
@author Tan Yifeng, Edmund (t.yifengedmund)
@course CSD11451
@section B
@Final Project GAM 150
@date 01/04/26
@brief
This file contains the RenderSystem singleton class which handles sorting
and rendering of all Mesh and Text objects in the scene
*//*______________________________________________________________________*/
#pragma once
#ifndef _RenderSystem_
#include <iostream>
#include <cstdint>
#include <vector>
#include <crtdbg.h> // To check for memory leaks
#include <mutex>
#include <memory>
#include <algorithm>
#include "AEEngine.h"
#include "Colors.hpp"
#include "Mesh.hpp"
#include "Text.hpp"

using namespace std;

class MeshGen;

class RenderSystem
{
public:

	bool needsSort = false;

	/*!***********************************************************************
	* \brief
	* Draws a Mesh component using the rendering system
	* \param[in] mesh
	* A reference to the Mesh component to draw
	*************************************************************************/
	void Draw(const Mesh& mesh);

	/*!***********************************************************************
	* \brief
	* Draws a Text component using the rendering system
	* \param[in] text
	* A pointer to the Text component to draw
	*************************************************************************/
	void Draw(Text* text) const;

	/*!***********************************************************************
	* \brief
	* Iterates over all entities, sorting and rendering their Mesh and Text
	* components in draw order
	* \param[in] entities
	* A reference to the list of all managed entities
	*************************************************************************/
	void RenderObjects(const std::vector<std::unique_ptr<Entity>>& entities);

	/*!***********************************************************************
	* \brief
	* Initialises the RenderSystem and acquires a reference to the MeshGen instance
	*************************************************************************/
	void init();

private:

	MeshGen* meshSystem = nullptr;
	RenderSystem()
	{
		
	}

	~RenderSystem()
	{
		
	}

public:


	RenderSystem(const RenderSystem&) = delete;
	RenderSystem& operator=(const RenderSystem&) = delete;

	/*!***********************************************************************
	* \brief
	* Returns the singleton instance of RenderSystem
	* \return
	* A reference to the single RenderSystem instance
	*************************************************************************/
	static RenderSystem& getInstance() {

		static RenderSystem instance;
		return instance;
	}
	
};



#endif

