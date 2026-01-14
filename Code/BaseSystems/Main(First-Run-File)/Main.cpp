// ---------------------------------------------------------------------------
// includes

#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"

#include <iostream>

//base inherit files
#include "../../BaseSystems_WZBJ_Pak.hpp"
#include "../Code/BaseSystems/JSONSerializer/JSONSerializer.hpp"
#include "../../JSONSerializer_WZBJ_Pak.hpp"


AEGfxVertexList* DrawFilledCircleMesh(int sides)
{
	//a
	AEGfxMeshStart();

	for (int i = 0; i <= sides; i++)
	{
		float angle1 = i * 2 * PI / sides;
		float angle2 = (i + 1) * 2 * PI / sides;
		AEGfxTriAdd(
			0.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f,
			cosf(angle1), sinf(angle1), 0xFFFFFFFF, 0.0f, 0.0f,
			cosf(angle2), sinf(angle2), 0xFFFFFFFF, 0.0f, 0.0f
		);
	}

	return AEGfxMeshEnd();
}

AEGfxVertexList* DrawSquare()
{
	AEGfxMeshStart();

	AEGfxTriAdd(
		0, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
		1, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		0, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		1, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		1, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		0, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	return AEGfxMeshEnd();
}

void WriteIntoJSON(rapidjson::PrettyWriter<rapidjson::FileWriteStream>& writer)
{
	writer.StartObject();
	writer.Key("test");
	writer.String("yay!");
	writer.EndObject();
}

void ReadFromJSON(rapidjson::Document& doc)
{
	std::cout << doc["test"].GetString();
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

	// Initialization of your own variables go here

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 1600, 900, 1, 60, false, NULL);

	// Changing the window title
	AESysSetWindowTitle("Solo Project 1");

	// reset the system modules
	AESysReset();

	printf("Hello World\n");

	JSONSerializer* jsonSerializer = new JSONSerializer();
	jsonSerializer->WriteIntoFile("Assets/test.json", WriteIntoJSON);

	Mesh heal, damage, playerSprite;

	Mesh healthBar, barBG, hpBarSegment;

	AEVec2 playerPos;
	AEVec2Zero(&playerPos);

	//AEGfxTriAdd(
	//	-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
	//	0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
	//	-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	//AEGfxTriAdd(
	//	0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
	//	0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
	//	-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxVertexList* square = DrawSquare();
	AEGfxVertexList* circle = DrawFilledCircleMesh(30);

	heal.SetMesh(circle);
	heal.SetScale(200, 200);
	heal.SetColor(Color4(0.f, 1.f, 0.f, 1.f));
	heal.SetPosition(-400.f, 0.f);
	heal.UpdateTransform();

	damage.SetMesh(circle);
	damage.SetScale(200, 200);
	damage.SetColor(Color4(1.f, 0.f, 0.f, 1.f));
	damage.SetPosition(400, 0.f);
	damage.UpdateTransform();

	playerSprite.SetMesh(circle);
	playerSprite.SetScale(50, 50);
	playerSprite.SetColor(Color4(1, 1, 1, 1));

	healthBar.SetMesh(square);
	healthBar.SetScale(600, 10);
	healthBar.SetPosition(-300, 400);
	healthBar.SetColor(Color4(1, 0, 0, 1));
	barBG = healthBar;
	barBG.SetColor(Color4(0.1f, .1f, .1f, 1));
	barBG.SetScale(606, 16);

	hpBarSegment.SetMesh(square);
	hpBarSegment.SetScale(30, 15);
	hpBarSegment.SetColor(Color4(1, 0, 0, 1));
	hpBarSegment.SetPosition(-300, 300);

	float health = 100;
	// Game Loop
	while (gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();
		float _dt = 1 / AEFrameRateControllerGetFrameRate();
		// Basic way to trigger exiting the application
		// when ESCAPE is hit or when the window is closed
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;

		if (AEInputCheckCurr(AEVK_W))
		{
			playerPos.y += 200 * _dt;
		}
		else if (AEInputCheckCurr(AEVK_S))
		{
			playerPos.y -= 200 * _dt;
		}

		if (AEInputCheckCurr(AEVK_A))
		{
			playerPos.x -= 200 * _dt;
		}

		if (AEInputCheckCurr(AEVK_D))
		{
			playerPos.x += 200 * _dt;
		}

		// JSON Serializer test
		if (AEInputCheckTriggered(AEVK_SPACE))
			jsonSerializer->ReadFromFile("Assets/test.json", ReadFromJSON);

		// Your own update logic goes here
		playerSprite.SetPosition(playerPos.x, playerPos.y);

		if (AEVec2Distance(&playerPos, &heal.position) <= 200)
		{
			health += 25 * _dt;
		}

		if (AEVec2Distance(&playerPos, &damage.position) <= 200)
		{
			health -= 25 * _dt;
		}

		float hpperc = health / 100.f;
		health = AEClamp(health, 0.f, 100.f);
		healthBar.SetScale(600 * hpperc, 10);
		healthBar.color = (health < 33.3f) ? Color4(1, 0, 0, 1) : Color4(0, 1, 1, 1);

		// Your own rendering logic goes here
		// Tell the Alpha Engine to set the background to black.
		AEGfxSetBackgroundColor(0.3f, 0.3f, 0.3f);
		heal.Draw();
		damage.Draw();
		playerSprite.Draw();

		barBG.Draw();
		healthBar.Draw();
		hpBarSegment.offset = { 0 };
		for (int i = 0; i < static_cast<int>(10 * hpperc); i++)
		{
			hpBarSegment.offset = {62.f * i, 0};
			hpBarSegment.Draw();
		}
		// Informing the system about the loop's end
		AESysFrameEnd();

	}

	// free the system
	delete jsonSerializer;
	AEGfxMeshFree(square);
	AESysExit();
}