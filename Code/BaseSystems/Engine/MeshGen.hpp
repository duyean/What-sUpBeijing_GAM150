/*!
@file MeshGen.hpp
@author Tan Yifeng, Edmund (t.yifengedmund)
@course CSD11451
@section B
@Final Project GAM 150
@date 01/04/26
@brief
This file contains the MeshGen singleton class which handles the generation,
caching, and drawing of shapes, textures, fonts, and animated sprites
*//*______________________________________________________________________*/
#pragma once
#ifndef _MeshGen_
#include <iostream>
#include <cstdint>
#include <vector>
#include <crtdbg.h> // To check for memory leaks
#include <mutex>
#include <map>
#include <memory>
#include <utility>
#include "AEEngine.h"
#include "ECS.hpp"
#include "Mesh.hpp"
#include "Entity.hpp"
#include "Colors.hpp"
#include "Text.hpp"

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



	private:

		//DO a draw layer by adding draw queueing instead of letting things draw every loop

		MeshGen()
		{
			
		}

		~MeshGen()
		{

		}
	private:
		/*!***********************************************************************
		* \brief
		* Builds the base unit box mesh and stores it in the mesh cache
		* under the key "Box"
		*************************************************************************/
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

		/*!***********************************************************************
		* \brief
		* Builds the base circle mesh using triangle fan approximation and
		* stores it in the mesh cache under the key "Circle"
		*************************************************************************/
		void baseCircle()
		{
			//implement circle Mesh

			AEGfxMeshStart();

			for (int i = 0; i < 31; i++)
			{
				float angle1 = i * 2 * PI / 31;
				float angle2 = (i + 1) * 2 * PI / 31;
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

		MeshGen(const MeshGen&) = delete;
		MeshGen& operator=(const MeshGen&) = delete;

		std::vector<std::unique_ptr<IRenderable>> tempTexts;

		/*!***********************************************************************
		* \brief
		* Returns the singleton instance of MeshGen
		* \return
		* A reference to the single MeshGen instance
		*************************************************************************/
		static MeshGen& getInstance() {

			static MeshGen newInstance;
			return newInstance;
		}

		/*!***********************************************************************
		* \brief
		* Initialises the MeshGen system by building the base box and circle
		* meshes and loading the default font
		*************************************************************************/
		void initialize()
		{
			baseBox();
			baseCircle();
			SetFont("Assets/Fonts/liberation-mono.ttf", "liberi", 50);
		}

		/*!***********************************************************************
		* \brief
		* Draws a coloured box at the given world position, size, and rotation
		* \param[in] Xpos
		* The world X position of the box centre
		* \param[in] Ypos
		* The world Y position of the box centre
		* \param[in] width
		* The width of the box
		* \param[in] height
		* The height of the box
		* \param[in] color
		* The colour to render the box with
		* \param[in] Deg
		* The rotation angle in degrees
		*************************************************************************/
		void DrawBox(float Xpos, float Ypos, float width, float height, Color color, float Deg);

		/*!***********************************************************************
		* \brief
		* Draws a textured box at the given world position, size, and rotation
		* \param[in] Xpos
		* The world X position of the box centre
		* \param[in] Ypos
		* The world Y position of the box centre
		* \param[in] width
		* The width of the box
		* \param[in] height
		* The height of the box
		* \param[in] color
		* The colour tint to apply to the texture
		* \param[in] Deg
		* The rotation angle in degrees
		* \param[in] fileName
		* The key name of the cached texture to use
		*************************************************************************/
		void DrawBoxTexture(float Xpos, float Ypos, float width, float height, Color color, float Deg, const char* fileName);

		/*!***********************************************************************
		* \brief
		* Draws a coloured circle at the given world position and size
		* \param[in] Xpos
		* The world X position of the circle centre
		* \param[in] Ypos
		* The world Y position of the circle centre
		* \param[in] width
		* The width of the bounding box
		* \param[in] height
		* The height of the bounding box
		* \param[in] color
		* The colour to render the circle with
		*************************************************************************/
		void DrawCircle(float Xpos, float Ypos, float width, float height, Color color);

		/*!***********************************************************************
		* \brief
		* Draws a textured circle at the given world position and size
		* \param[in] Xpos
		* The world X position of the circle centre
		* \param[in] Ypos
		* The world Y position of the circle centre
		* \param[in] width
		* The width of the bounding box
		* \param[in] height
		* The height of the bounding box
		* \param[in] color
		* The colour tint to apply to the texture
		* \param[in] fileName
		* The key name of the cached texture to use
		*************************************************************************/
		void DrawCircleTexture(float Xpos, float Ypos, float width, float height, Color color, const char* fileName);

		/*!***********************************************************************
		* \brief
		* Draws a coloured box using AEVec2 position and scale
		* \param[in] position
		* The world position of the box centre
		* \param[in] scale
		* The width and height of the box
		* \param[in] color
		* The colour to render the box with
		* \param[in] Deg
		* The rotation angle in degrees
		*************************************************************************/
		//Overloaded Drawing
		void DrawBox(AEVec2 position, AEVec2 scale, Color color, float Deg);

		/*!***********************************************************************
		* \brief
		* Draws a coloured box anchored to the left edge using AEVec2 position and scale
		* \param[in] position
		* The world position of the box left edge
		* \param[in] scale
		* The width and height of the box
		* \param[in] color
		* The colour to render the box with
		* \param[in] Deg
		* The rotation angle in degrees
		*************************************************************************/
		void DrawBoxLeft(AEVec2 position, AEVec2 scale, Color color, float Deg);

		/*!***********************************************************************
		* \brief
		* Draws a textured box using AEVec2 position and scale with a pre-loaded texture pointer
		* \param[in] position
		* The world position of the box centre
		* \param[in] scale
		* The width and height of the box
		* \param[in] color
		* The colour tint to apply to the texture
		* \param[in] Deg
		* The rotation angle in degrees
		* \param[in] texture
		* Pointer to a pre-loaded AEGfxTexture
		*************************************************************************/
		void DrawBoxTexture(AEVec2 position, AEVec2 scale, Color color, float Deg, AEGfxTexture* texture);

		/*!***********************************************************************
		* \brief
		* Draws a coloured circle using AEVec2 position and scale
		* \param[in] position
		* The world position of the circle centre
		* \param[in] scale
		* The width and height of the bounding box
		* \param[in] color
		* The colour to render the circle with
		*************************************************************************/
		void DrawCircle(AEVec2 position, AEVec2 scale, Color color);

		/*!***********************************************************************
		* \brief
		* Draws a textured circle using AEVec2 position and scale with a pre-loaded texture pointer
		* \param[in] position
		* The world position of the circle centre
		* \param[in] scale
		* The width and height of the bounding box
		* \param[in] color
		* The colour tint to apply to the texture
		* \param[in] texture
		* Pointer to a pre-loaded AEGfxTexture
		*************************************************************************/
		void DrawCircleTexture(AEVec2 position, AEVec2 scale, Color color, AEGfxTexture* texture);

		/*!***********************************************************************
		* \brief
		* Retrieves a cached vertex list mesh by its key name, loading it
		* from file if not already cached
		* \param[in] fileName
		* The key name of the mesh to retrieve
		* \return
		* A pointer to the cached AEGfxVertexList
		*************************************************************************/
		AEGfxVertexList* getMesh(const char* fileName);

		/*!***********************************************************************
		* \brief
		* Retrieves a cached texture by its key name, loading it from file
		* if not already cached
		* \param[in] fileName
		* The key name of the texture to retrieve
		* \return
		* A pointer to the cached AEGfxTexture
		*************************************************************************/
		AEGfxTexture* getTexture(const char* fileName);

		/*!***********************************************************************
		* \brief
		* Loads a texture from a file path and stores it in the texture cache
		* under the given key name
		* \param[in] filePath
		* The file path to the texture resource
		* \param[in] fileName
		* The key name to cache the texture under
		*************************************************************************/
		void CreateTexture(const char* filePath, const char* fileName);

		/*!***********************************************************************
		* \brief
		* Creates and draws an animated sprite at the given world position
		* \param[in] Xpos
		* The world X position of the sprite centre
		* \param[in] Ypos
		* The world Y position of the sprite centre
		* \param[in] width
		* The width of the sprite
		* \param[in] height
		* The height of the sprite
		* \param[in] animationSpeed
		* The playback speed of the animation
		* \param[in] face
		* The facing direction of the sprite
		* \param[in] Deg
		* The rotation angle in degrees
		* \param[in] color
		* The colour tint to apply
		* \param[in] fileName
		* The key name of the sprite sheet texture
		*************************************************************************/
		void CreateAnimatedSprite(float Xpos, float Ypos, float width, float height, float animationSpeed, int face, float Deg, Color color, const char* fileName);

		/*!***********************************************************************
		* \brief
		* Creates and registers a sprite sheet with the given grid dimensions and FPS
		* \param[in] column
		* The number of columns in the sprite sheet
		* \param[in] row
		* The number of rows in the sprite sheet
		* \param[in] fps
		* The animation playback speed in frames per second
		* \param[in] fileName
		* The key name of the sprite sheet texture
		*************************************************************************/
		void CreateSpriteSheet(int column, int row, int fps, const char* fileName);

		/*!***********************************************************************
		* \brief
		* Loads a font from a file path and caches it under the given key name
		* \param[in] filePath
		* The file path to the font resource
		* \param[in] fileName
		* The key name to cache the font under
		* \param[in] pixelSize
		* The pixel size to load the font at
		*************************************************************************/
		void SetFont(const char* filePath, const char* fileName, int pixelSize);

		/*!***********************************************************************
		* \brief
		* Retrieves the font ID for a cached font by its key name
		* \param[in] fontFile
		* The key name of the cached font
		* \return
		* The s8 font ID used by the rendering system
		*************************************************************************/
		s8 GetFontID(const char* fontFile);

		/*!***********************************************************************
		* \brief
		* Draws a string of text at the given world position using a cached font
		* \param[in] Xpos
		* The world X position of the text
		* \param[in] Ypos
		* The world Y position of the text
		* \param[in] scale
		* The scale of the rendered text
		* \param[in] color
		* The colour to render the text with
		* \param[in] text
		* The string of text to render
		* \param[in] fileName
		* The key name of the cached font to use
		* \param[in] align
		* The text alignment (LEFT, CENTER, RIGHT)
		* \param[in] layer
		* The draw order depth layer
		*************************************************************************/
		void DrawFont(float Xpos, float Ypos, float scale, Color color, const char* text, const char* fileName, TextAlignment align = TextAlignment::LEFT, int layer = 500);

		/*!***********************************************************************
		* \brief
		* Renders a Text component object using the rendering system
		* \param[in] text
		* A pointer to the Text component to render
		*************************************************************************/
		void RenderFont(Text* const text);

		/*!***********************************************************************
		* \brief
		* Removes a specific font from the font cache by key name
		* \param[in] name
		* The key name of the font to remove
		*************************************************************************/
		void ClearFont(string name);

		/*!***********************************************************************
		* \brief
		* Removes all fonts from the font cache
		*************************************************************************/
		void ClearAllFont();

		/*!***********************************************************************
		* \brief
		* Removes a specific mesh from the mesh cache by key name
		* \param[in] name
		* The key name of the mesh to remove
		*************************************************************************/
		void ClearMesh(string name);

		/*!***********************************************************************
		* \brief
		* Removes a specific texture from the texture cache by key name
		* \param[in] name
		* The key name of the texture to remove
		*************************************************************************/
		void ClearTex(string name);

		/*!***********************************************************************
		* \brief
		* Removes all meshes and textures from their respective caches
		*************************************************************************/
		void ClearAllMesh();
	};



#endif

