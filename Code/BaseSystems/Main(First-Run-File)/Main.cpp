// ---------------------------------------------------------------------------
// includes

#include <crtdbg.h> // To check for memory leaks
#include <chrono>
#include "AEEngine.h"
#include "../Engine/MeshGen.hpp"
#include "../Engine/Entity.hpp"
#include "../Engine/EntityManager.hpp"
#include "../Engine/PhysicSystem.hpp"


#include "../../SceneHandler_WZBJ_Pak.hpp"

GameManager* gameManager = nullptr;


#define CAPSPEED 60.0
MeshGen* MeshGen::instance = nullptr;
mutex MeshGen::mtx;

EntityManager* EntityManager::instance = nullptr;
mutex EntityManager::mtx;

PhysicSystem* PhysicSystem::instance = nullptr;
mutex PhysicSystem::mtx;



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

	//Game Initialization
	game_init();

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 1600, 900, 1, 60, false, NULL);

	// Window Title
	AESysSetWindowTitle("Gam150");

	// reset the system modules
	AESysReset();


	//FixedUpdate
	auto currentTime = std::chrono::high_resolution_clock::now();
	double accumulator = 0.0;

	//SetUp Meshes
	MeshGen* meshSystem = MeshGen::getInstance();

	//Setup EntityManager System
	EntityManager* enSystem = EntityManager::getInstance();

	//Setup Physics System
	PhysicSystem* phSystem = PhysicSystem::getInstance();

	meshSystem->initialize();

	//Move all of these into a GameSceneManager/GameStateManager
   //Root
	auto r = std::make_unique<Entity>("ROOT");
	enSystem->rootEntity = r.get();
	AEVec2 pos = { 0.f,0.f };
	AEVec2 scale = { 1.f,1.f };
	enSystem->rootEntity->addComponent<Transform2D>(pos, scale, 0.f);
	enSystem->entities.push_back(std::move(r));


	for (const auto& end : enSystem->entities)
	{
		end->init();
	}

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
	    //Update everything
		for (const auto& end : enSystem->entities)
		{
			end->update();
		}

		// Game Update and rendering
		game_update();


		//Fixed Update everything
		if (accumulator >= FIXED_DT)
		{
			for (const auto& end : enSystem->entities)
			{
				end->fixedUpdate();
			}
			phSystem->fixedUpdate(FIXED_DT);
			accumulator -= FIXED_DT;
		}


		// Informing the system about the loop's end
		AESysFrameEnd();

	}

	// free the system
	game_exit();
	AESysExit();
}