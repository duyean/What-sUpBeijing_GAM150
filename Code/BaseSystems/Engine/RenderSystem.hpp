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
	void Draw(const Mesh& mesh);
	void Draw(Text* text) const;
	void RenderObjects(const std::vector<std::unique_ptr<Entity>>& entities);
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

	static RenderSystem& getInstance() {

		static RenderSystem instance;
		return instance;
	}
	
};



#endif