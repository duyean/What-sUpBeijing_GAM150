#pragma once
#ifndef _MeshGen_
#include <iostream>
#include <cstdint>
#include <vector>
#include <crtdbg.h> // To check for memory leaks
#include <mutex>
#include <map>
#include <memory>
#include "AEEngine.h"
#include "ECS.hpp"
#include "MeshNew.hpp"
#include "Entity.hpp"
#include "Colors.hpp"

using namespace std;


	//Singleton class MeshGen Run once before game loop starts
	class MeshGen
	{
		static MeshGen* instance;

		static mutex mtx;

		//Mesh Shapes (Built Once per program start)
		std::vector<SpriteSheetMesh*> sSprite;
		std::map<string, AEGfxVertexList* > pMesh;
		std::map<string, AEGfxTexture* > pTex;
		std::map<string, s8> pFont;



	public:

		//DO a draw layer by adding draw queueing instead of letting things draw every loop

		MeshGen()
		{
			
		}

		~MeshGen()
		{

		}
	private:
		void baseBox()
		{
			AEGfxMeshStart();

			AEGfxTriAdd(
				-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
				0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
				-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

			AEGfxTriAdd(
				0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
				0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
				-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

			pMesh.insert({ "Box",  AEGfxMeshEnd() });

		}
		void baseCircle()
		{
			//implement circle Mesh

			AEGfxMeshStart();

			for (int i = 0; i <= 32; i++)
			{
				float angle1 = i * 2 * PI / 32;
				float angle2 = (i + 1) * 2 * PI / 32;
				AEGfxTriAdd(
					0.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f,
					cosf(angle1), sinf(angle1), 0xFFFFFFFF, 0.0f, 0.0f,
					cosf(angle2), sinf(angle2), 0xFFFFFFFF, 0.0f, 0.0f
				);
			}

			pMesh.insert({ "Circle",  AEGfxMeshEnd() });


		}
	public:
		//Singleton functions

		MeshGen(const MeshGen& obj) = delete;

		static MeshGen* getInstance() {
			if (instance == nullptr)
			{
				lock_guard<mutex> lock(mtx);
				if (instance == nullptr) {
					instance = new MeshGen();
				}
			}

			return instance;
		}

		void initialize()
		{
			baseBox();
			baseCircle();
		}

		void DrawBox(float Xpos, float Ypos, float width, float height, Color color, float Deg);

		void DrawBoxTexture(float Xpos, float Ypos, float width, float height, Color color, float Deg, const char* fileName);

		void DrawCircle(float Xpos, float Ypos, float width, float height, Color color);

		void DrawCircleTexture(float Xpos, float Ypos, float width, float height, Color color, const char* fileName);

		//Overloaded Drawing
		void DrawBox(AEVec2 position, AEVec2 scale, Color color, float Deg);

		void DrawBoxLeft(AEVec2 position, AEVec2 scale, Color color, float Deg);

		void DrawBoxTexture(AEVec2 position, AEVec2 scale, Color color, float Deg, AEGfxTexture* texture);

		void DrawCircle(AEVec2 position, AEVec2 scale, Color color);

		void DrawCircleTexture(AEVec2 position, AEVec2 scale, Color color, AEGfxTexture* texture);

		AEGfxVertexList* getMesh(const char* fileName);

		AEGfxTexture* getTexture(const char* fileName);

		void CreateTexture(const char* filePath, const char* fileName);

		void CreateAnimatedSprite(float Xpos, float Ypos, float width, float height, float animationSpeed, int face, float Deg, Color color, const char* fileName);

		void CreateSpriteSheet(int column, int row, int fps, const char* fileName);

		void SetFont(const char* filePath, const char* fileName, int pixelSize);

		void DrawFont(float Xpos, float Ypos, float scale, Color color, const char* text, const char* fileName);

		void ClearFont(string name);

		void ClearAllFont();

		void ClearMesh(string name);

		void ClearTex(string name);

		void ClearAllMesh();
	};



#endif