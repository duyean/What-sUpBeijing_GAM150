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
#include "../Engine/ECS.hpp"
#include "../Engine/Colors.hpp"
#include "../Engine/OOP.hpp"
#include "../Engine/Transform2D.hpp"

using namespace std;

enum MeshType{
	BOX_B,
	BOX_BL,
	BOX_T,
	CIRCLE_B,
	SPRITE_T
};


class Mesh : public SoloBehavior
{
public:

	MeshType type = BOX_T;

	AEGfxVertexList* targetMesh = nullptr;
	AEGfxTexture* pTex = nullptr;
	Color color;


	int drawOrder = 100;


public:

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	void Draw();

	void setMesh(char const* fileName);
	void setTexture(char const* fileName);

	Mesh() {

	}

	Mesh(AEGfxVertexList* t, AEGfxTexture* p, Color col, int depth, MeshType ty) {
		targetMesh = t;
		pTex = p;
		drawOrder = depth;
		type = ty;
		color = col;
	}
	//Init with this please
	Mesh(const char* filenameM, const char* filenameT, Color col, int depth, MeshType t) {
		setMesh(filenameM);
		setTexture(filenameT);
		drawOrder = depth;
		type = t;
		color = col;
	}

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
	SpriteSheetMesh() {
		row = 0;
		column = 0;
		currentFrame = 0;
		FPS = 0;
		currentTime = 0;
	}


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