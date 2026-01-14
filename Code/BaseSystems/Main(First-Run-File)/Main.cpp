// ---------------------------------------------------------------------------
// includes

#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include "../../SceneHandler_WZBJ_Pak.hpp"

GameManager* gameManager = nullptr;

void game_init(void)
{
	gameManager = GameManager::GetInstance();
	gameManager->Init();
}

void game_update(void)
{
	gameManager->Update(AEFrameRateControllerGetFrameTime());
	gameManager->Render();
}

void game_exit(void)
{
	gameManager->Exit();
	GameManager::DestroyInstance();
}

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

	//Game Initialization
	game_init();

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 1600, 900, 1, 60, false, NULL);

	// Window Title
	AESysSetWindowTitle("Gam150");

	// reset the system modules
	AESysReset();

	// Game Loop
	while (gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		// Close the window if press esacpe key
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;

		// Game Update and rendering
		game_update();

		// Informing the system about the loop's end
		AESysFrameEnd();

	}

	// free the system
	game_exit();
	AESysExit();
}