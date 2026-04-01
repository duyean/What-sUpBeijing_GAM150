/*!
@file Mesh.hpp
@author Tan Yifeng, Edmund (t.yifengedmund)
@course CSD11451
@section B
@Final Project GAM 150
@date 01/04/26
@brief
This file contains the Mesh component class and the SpriteSheetMesh class,
which manage vertex lists, textures, and draw order for renderable entities
*//*______________________________________________________________________*/
#pragma once
#ifndef _Mesh_
#include <iostream>
#include <cstdint>
#include <vector>
#include <crtdbg.h> // To check for memory leaks
#include <mutex>
#include <map>
#include <memory>
#include "AEEngine.h"
#include "ECS.hpp"
#include "Colors.hpp"
#include "OOP.hpp"
#include "Transform2D.hpp"
#include "Renderable.hpp"

using namespace std;

//test
//test2
enum MeshType{
	BOX_B,
	BOX_BL,
	BOX_T,
	CIRCLE_B,
	SPRITE_T
};

class MeshGen;

class Mesh : public SoloBehavior, public IRenderable
{
public:

	MeshType type = BOX_T;

	AEGfxVertexList* targetMesh = nullptr;
	AEGfxTexture* pTex = nullptr;
	Color color;

private:
	MeshGen* meshSystem = nullptr;

public:

	/*!***********************************************************************
	* \brief
	* Called once when the component is first created, before init
	*************************************************************************/
	void awake() override;

	/*!***********************************************************************
	* \brief
	* Called once before the first update, used for initialisation
	*************************************************************************/
	void init() override;

	/*!***********************************************************************
	* \brief
	* Called every frame
	*************************************************************************/
	void update() override;

	/*!***********************************************************************
	* \brief
	* Called at a fixed timestep, used for physics-based updates
	*************************************************************************/
	void fixedUpdate() override;

	/*!***********************************************************************
	* \brief
	* Called when the component is destroyed, used for cleanup
	*************************************************************************/
	void destroy() override;

	/*!***********************************************************************
	* \brief
	* Draws this mesh using its current transform, texture, and colour
	*************************************************************************/
	void Draw();

	/*!***********************************************************************
	* \brief
	* Loads and assigns a vertex list mesh from the given file path
	* \param[in] fileName
	* The file path to the mesh resource
	*************************************************************************/
	void setMesh(char const* fileName);

	/*!***********************************************************************
	* \brief
	* Loads and assigns a texture from the given file path
	* \param[in] fileName
	* The file path to the texture resource
	*************************************************************************/
	void setTexture(char const* fileName);

	Mesh() {

	}

	/*!***********************************************************************
	* \brief
	* Constructs a Mesh with pre-loaded vertex list, texture, colour,
	* draw order, and mesh type
	* \param[in] t
	* Pointer to a pre-loaded vertex list
	* \param[in] p
	* Pointer to a pre-loaded texture
	* \param[in] col
	* The colour tint to apply
	* \param[in] depth
	* The draw order depth layer
	* \param[in] ty
	* The mesh type enum value
	*************************************************************************/
	Mesh(AEGfxVertexList* t, AEGfxTexture* p, Color col, int depth, MeshType ty) {
		targetMesh = t;
		pTex = p;
		drawOrder = depth;
		type = ty;
		color = col;
	}

	/*!***********************************************************************
	* \brief
	* Constructs a Mesh by loading both a mesh and texture from file paths
	* \param[in] filenameM
	* The file path to the mesh resource
	* \param[in] filenameT
	* The file path to the texture resource
	* \param[in] col
	* The colour tint to apply
	* \param[in] depth
	* The draw order depth layer
	* \param[in] t
	* The mesh type enum value
	*************************************************************************/
	//Init with this please
	Mesh(const char* filenameM, const char* filenameT, Color col, int depth, MeshType t) {
		setMesh(filenameM);
		setTexture(filenameT);
		drawOrder = depth;
		type = t;
		color = col;
	}

	/*!***********************************************************************
	* \brief
	* Constructs a Mesh by loading only a mesh from file, with no texture.
	* Intended for BOX and CIRCLE mesh types
	* \param[in] filenameM
	* The file path to the mesh resource
	* \param[in] col
	* The colour tint to apply
	* \param[in] depth
	* The draw order depth layer
	* \param[in] t
	* The mesh type enum value
	*************************************************************************/
	//Only for BOX and CIRCLE no TEX
	Mesh(const char* filenameM, Color col, int depth, MeshType t) {
		setMesh(filenameM);
		drawOrder = depth;
		type = t;
		color = col;
	}

	~Mesh()
	{

	}
};



class SpriteSheetMesh : Mesh
{
	int row = 0;
	int column = 0;
	int currentFrame = 0;
	int FPS = 0;
	float currentTime = 0;
	bool leftFace = true;
	bool isPlaying = false;

public:
	/*!***********************************************************************
	* \brief
	* Default constructor, initialises all sprite sheet parameters to zero
	*************************************************************************/
	SpriteSheetMesh() {
		row = 0;
		column = 0;
		currentFrame = 0;
		FPS = 0;
		currentTime = 0;
	}

	/*!***********************************************************************
	* \brief
	* Constructs a SpriteSheetMesh with explicit animation parameters
	* \param[in] r
	* Number of rows in the sprite sheet
	* \param[in] c
	* Number of columns in the sprite sheet
	* \param[in] cF
	* The starting frame index
	* \param[in] fps
	* The playback speed in frames per second
	* \param[in] cT
	* The initial elapsed time
	*************************************************************************/
	SpriteSheetMesh(int r, int c, int cF, int fps, float cT) {
		row = r;
		column = c;
		currentFrame = cF;
		FPS = fps;
		currentTime = cT;
	}

	~SpriteSheetMesh() {

	}
};

#endif

