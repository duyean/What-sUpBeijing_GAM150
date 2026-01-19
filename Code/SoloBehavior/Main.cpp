// ---------------------------------------------------------------------------
// includes

#include <crtdbg.h> // To check for memory leaks
#include <chrono>
#include "AEEngine.h"
#include "MeshGen.hpp"
#include "BaseSystems.hpp"
#include "EntityManager.hpp"
#include "PhysicSystem.hpp"
#include "Player.hpp"
#include "BoxCollider2D.hpp"
#include "HEALTHBAR1.hpp"
#include "HEALTHBAR2.hpp"


#define CAPSPEED 60.0
// ---------------------------------------------------------------------------
// main
MeshGen* MeshGen::instance = nullptr;
mutex MeshGen::mtx;

EntityManager* EntityManager::instance = nullptr;
mutex EntityManager::mtx;

PhysicSystem* PhysicSystem::instance = nullptr;
mutex PhysicSystem::mtx;


constexpr double FIXED_DT = 1.0 / CAPSPEED;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	int gGameRunning = 1;

	// Initialization of your own variables go here

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 1600, 900, 1, 60, false, NULL);

	// Changing the window title
	AESysSetWindowTitle("My New Demo!");

	// reset the system modules
	AESysReset();

	printf("Hello World\n");

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

	meshSystem->CreateTexture("./Assets/PlanetTexture.png", "PLANET");


	//Move all of these into a GameSceneManager/GameStateManager
	//Root
	auto r = std::make_unique<Entity>("ROOT");
	enSystem->rootEntity = r.get();
	AEVec2 pos = { 0.f,0.f };
	AEVec2 scale = { 1.f,1.f };
	enSystem->rootEntity->addComponent<Transform2D>(pos, scale, 0.f);
	enSystem->entities.push_back(std::move(r));
	


	auto e = std::make_unique<Entity>("BUTTONRED");
	Entity* ptr = e.get();
	pos = { -300.f,0.f };
	scale = { 100.f,100.f };
	ptr->addComponent<Transform2D>(pos, scale, 0.f); //this MUST exist on an entity
	ptr->addComponent<Mesh>("Circle", Color(255, 0, 0, 1), 100, MeshType::CIRCLE_B);
	ptr->addComponent<BoxCollider2D>(50.f,50.f);
	enSystem->rootEntity->transform->AddChild(ptr->transform);
	enSystem->entities.push_back(std::move(e));

    e = std::make_unique<Entity>("BUTTONGREEN");
	ptr = e.get();
	pos = { 300.f,0.f };
	scale = { 100.f,100.f };
	ptr->addComponent<Transform2D>(pos, scale, 0.f); //this MUST exist on an entity
	ptr->addComponent<Mesh>("Circle", Color(0, 255, 0, 1), 100, MeshType::CIRCLE_B);
	ptr->addComponent<BoxCollider2D>(50.f,50.f);
	enSystem->rootEntity->transform->AddChild(ptr->transform);
	enSystem->entities.push_back(std::move(e));

	e = std::make_unique<Entity>("HPBAR1");
	ptr = e.get();
	pos = { -600.f,350.f };
	scale = { 1200.f,30.f };
	ptr->addComponent<Transform2D>(pos, scale, 0.f); //this MUST exist on an entity
	ptr->addComponent<Mesh>("Box", Color(255, 0, 0, 1), 100, MeshType::BOX_BL);
	ptr->addComponent<BoxCollider2D>(50.f, 50.f);
	ptr->addComponent<Healthbar1>();
	enSystem->rootEntity->transform->AddChild(ptr->transform);
	enSystem->entities.push_back(std::move(e));
	

	for (int i = 0; i < 10; i++)
	{
		e = std::make_unique<Entity>("HPBAR2");
		ptr = e.get();
		pos = { -600.f + (((i) * (1200.f / 19.f)) * 2),300.f};
		scale = { 1200.f / 19.f,30.f };
		ptr->addComponent<Transform2D>(pos, scale, 0.f); //this MUST exist on an entity
		ptr->addComponent<Mesh>("Box", Color(255, 0, 0, 1), 100, MeshType::BOX_BL);
		ptr->addComponent<Healthbar2>(10.f * i);
		enSystem->rootEntity->transform->AddChild(ptr->transform);
		enSystem->entities.push_back(std::move(e));
		
	}

	e = std::make_unique<Entity>("PLAYER");
	ptr = e.get();
	pos = { 0.f,100.f };
	scale = { 30.f,30.f };
	ptr->addComponent<Transform2D>(pos, scale, 0.f); //this MUST exist on an entity
	ptr->addComponent<Mesh>("Circle", Color(0, 0, 255, 1), 100, MeshType::CIRCLE_B);
	ptr->addComponent<BoxCollider2D>(15.f, 15.f);
	ptr->addComponent<Player>();
	enSystem->rootEntity->transform->AddChild(ptr->transform);
	enSystem->entities.push_back(std::move(e));



	for (const auto& end : enSystem->entities)
	{
		end->init();
	}
	// Game Loop
	while (gGameRunning)
	{

		// Informing the system about the loop's start
		AESysFrameStart();

		// Basic way to trigger exiting the application
		// when ESCAPE is hit or when the window is closed
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

		// Your own rendering logic goes here

		//Temporary background color setter
		Color bgColor = Color(150, 150, 150, 1);
		float red = bgColor.normalize(static_cast<float>(bgColor.R));
		float green = bgColor.normalize(static_cast<float>(bgColor.G));
		float blue = bgColor.normalize(static_cast<float>(bgColor.B));
		AEGfxSetBackgroundColor(red, green, blue);

		// Informing the system about the loop's end
		AESysFrameEnd();

	}

	for (const auto& end : enSystem->entities)
	{
		end->destroy();
	}
	enSystem->entities.clear();

	// free the system
	AESysExit();
}