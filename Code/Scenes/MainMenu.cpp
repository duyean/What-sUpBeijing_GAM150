/*!
@file SplashScreen.cpp
@author Tai Qian Yi (t.qianyi)
@course CSD11451
@section B
@Final Project
@date 13/1/26
@brief
This file contains the definitions for the collection of functions in MainMenu.hpp
*//*______________________________________________________________________*/
#include "MainMenu.hpp"

#include <iostream>

#include "../Code/BaseSystems/JSONSerializer/JSONSerializer.hpp"
#include "../JSONSerializer_WZBJ_Pak.hpp"

// This is all temporary btw
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

JSONSerializer* jsonSerializer = nullptr;

MainMenu::MainMenu()
{
	
}

MainMenu::~MainMenu()
{
}

/*!
@brief Initialize splash screen variables

Overwrites virtual GameState::Init().
This function loads splash screen image

@param void
@return void
*//*______________________________________________________________*/
void MainMenu::Load()
{
	jsonSerializer = new JSONSerializer();
	jsonSerializer->WriteIntoFile("Assets/test.json", WriteIntoJSON);

	std::cout << "Now in Main Menu!!" << std::endl;
}


/*!
@brief Clears splash screen variables

Overwrites virtual GameState::Exit().
This function frees splash screen image used.

@param void
@return void
*//*______________________________________________________________*/
void MainMenu::Unload()
{

	delete jsonSerializer;
}