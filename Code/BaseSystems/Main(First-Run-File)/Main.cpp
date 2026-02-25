// ---------------------------------------------------------------------------
// includes

#include <crtdbg.h> // To check for memory leaks
#include <chrono>
#include "AEEngine.h"
#include "../Engine/MeshGen.hpp"
#include "../Engine/Entity.hpp"
#include "../Engine/EntityManager.hpp"
#include "../Engine/PhysicSystem.hpp"
#include "../Engine/RenderSystem.hpp"


#include "../../SceneHandler_WZBJ_Pak.hpp"

//base inherit files
#include "../../BaseSystems_WZBJ_Pak.hpp"

#include "../Engine/Editor/Editor.hpp"


#ifdef ALPHA_EDITOR
LRESULT CALLBACK EditorWndProc(HWND, UINT, WPARAM, LPARAM);
#endif

GameManager* gameManager = nullptr;


#define CAPSPEED 60.0
MeshGen* meshSystem = &MeshGen::getInstance();

EntityManager* enSystem = &EntityManager::getInstance();

PhysicSystem* phSystem = &PhysicSystem::getInstance();

RenderSystem* rSystem = &RenderSystem::getInstance();



void game_init(void)
{
	gameManager = GameManager::GetInstance();
	gameManager->Init();
	meshSystem->initialize();
	rSystem->init();

}

void game_update(void)
{

	gameManager->Render();
	gameManager->Update(AEFrameRateControllerGetFrameTime());
}

void game_exit(void)
{
	gameManager->Exit();
	enSystem->forceClearAllDestroyed();
	GameManager::DestroyInstance();
}

constexpr double FIXED_DT = 1.0 / CAPSPEED;
// ---------------------------------------------------------------------------
// main

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	int gGameRunning = 1;



	LRESULT(CALLBACK * wndProc)(
		HWND, UINT, WPARAM, LPARAM
		) = nullptr;


    #ifdef ALPHA_EDITOR
	wndProc = EditorWndProc;
    #endif

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 1600, 900, 1, 60, false, wndProc);

	// Window Title
	AESysSetWindowTitle("Gam150");

	// reset the system modules
	AESysReset();


	//Game Initialization
	game_init();

	//FixedUpdate
	auto currentTime = std::chrono::high_resolution_clock::now();
	double accumulator = 0.0;

	//Move all of these into a GameSceneManager/GameStateManager
   //Root
	enSystem->entities.reserve(1000);

	// Game Loop
	while (gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		// Close the window if press esacpe key
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;

	

		//Chrono stuff
		auto newTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> frameTime = newTime - currentTime;
		currentTime = newTime;

		if (frameTime.count() > 0.25) {
			frameTime = std::chrono::duration<double>(0.25);
		}
		accumulator += frameTime.count();


	 	// Your own update logic goes here
		// Game Update 
		//gameManager->Update(AEFrameRateControllerGetFrameTime());
		// Game rendering
		//gameManager->Render();
		// Game Fixed Update


		//rSystem->RenderObjects(enSystem->entities);

		// Game Update and rendering
		game_update();
		gameManager->FixedUpdate(FIXED_DT, accumulator);
		enSystem->clearAllDestroyed();
		//change to optimized move and pop once drawing layers are implemented


#ifdef ALPHA_EDITOR
		//Editor code
		ImGuiLayer::Begin();
		EditorApp::Draw();
		ImGuiLayer::End();
#endif

		// Informing the system about the loop's end
		AESysFrameEnd();
	}

	// free the system
	game_exit();
	AESysExit();
}