// ---------------------------------------------------------------------------
// includes

//#include "vld.h"
#include <crtdbg.h> // To check for memory leaks
#include <chrono>
#include "AEEngine.h"
#include "../Engine/MeshGen.hpp"
#include "../Engine/Entity.hpp"
#include "../Engine/EntityManager.hpp"
#include "../Engine/PhysicSystem.hpp"
#include "../Engine/RenderSystem.hpp"
#include "../Audio/AudioManager.hpp"

#include "../../SceneHandler_WZBJ_Pak.hpp"

//base inherit files
#include "../../BaseSystems_WZBJ_Pak.hpp"

#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#ifdef ALPHA_EDITOR
LRESULT CALLBACK EditorWndProc(HWND, UINT, WPARAM, LPARAM);
#endif

GameManager* gameManager = nullptr;


#define CAPSPEED 60.0

EntityManager* enSystem = &EntityManager::getInstance();

PhysicSystem* phSystem = &PhysicSystem::getInstance();

RenderSystem* rSystem = &RenderSystem::getInstance();

MeshGen* meshSystem = &MeshGen::getInstance();



void game_init(void)
{
	gameManager = GameManager::GetInstance();
	gameManager->Init();
	rSystem->init();
}

void game_update(void)
{
	gameManager->Render();
	gameManager->Update(static_cast<float>(AEFrameRateControllerGetFrameTime()));
}

void game_exit(void)
{
	gameManager->Exit();
	enSystem->forceClearAllDestroyed();
	GameManager::DestroyInstance();
	AudioManager::DestroyInstance();
}

constexpr double FIXED_DT = 1.0 / CAPSPEED;
// ---------------------------------------------------------------------------
// main


bool ConfirmQuit(HWND hwnd)
{
	int result = MessageBox(
		hwnd,
		"Are you sure you want to quit? Unsaved progress will be lost",
		"Confirm Exit",
		MB_YESNO | MB_ICONQUESTION
	);
	return result == IDYES;
}

LRESULT CALLBACK MyWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
	{
		

		if (ConfirmQuit(hwnd))
		{
			gameManager->quitGame = true;  // exits the game loop
			DestroyWindow(hwnd);           // closes the window
		}

		return 0;
	}
	}

	// Pass everything else to AEEngine's default handler
	return DefWindowProc(hwnd, msg, wParam, lParam);
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	LRESULT(CALLBACK * wndProc)(
		HWND, UINT, WPARAM, LPARAM
		) = nullptr;


	wndProc = MyWndProc;

	//_CrtSetBreakAlloc(111815);
	//_CrtSetBreakAlloc(111814);
	//_CrtSetBreakAlloc(111813);
	//_CrtSetBreakAlloc(111812);

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
	while (gameManager->quitGame != true)
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		// Close the window if press esacpe key
		if (AEInputCheckTriggered(AEVK_0) || 0 == AESysDoesWindowExist())
		{
			if (ConfirmQuit(AESysGetWindowHandle()))
				gameManager->quitGame = true;
		}

	

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


		// Informing the system about the loop's end
		AESysFrameEnd();
	}

	// free the system
	game_exit();
	AESysExit();

}