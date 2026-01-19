/*!
@file Button.h
@author Wayne Lion (lion.w)
@course CSD1401
@section A
@Final Project
@date 16 September 2025
@brief
This file contains the declarations for Button related functions
*/
#pragma once
#include "../../BaseSystems_WZBJ_Pak.hpp"
#include <functional>

class Button
{
private:
	//What image to use the button's background
	Sprite m_ButtonBackground;
	//The color for the button's text
	Color4 textColor;
	//Where the button is. Note: ImageMode is CENTER for all buttons
	AEVec2 m_Position;
	//How big the button is, do not modify this lol.
	float height, width;
	//What text to display in the center of the button
	const char* m_ButtonText;
	//The original size of the button. This can be modified.
	float fixedHeight, fixedWidth;
	//Buffer to check whether the mouse is in the button's bounds
	bool hoverBuffer;

public:
	/*!
	What the button does after clicking it
	*/
	std::function<void()>OnClickFunction;
	/*!
	Checks whether the mouse is in the button's bounds.
	@param mousePos - The mouse's current position
	@return A boolean to indiciate whether the mouse is in the button
	*/
	bool CheckClick(AEVec2 mousePos) const;
	/*!
	Function to run when the button is clicked
	@param None
	@return None
	*/
	void OnClick(void);
	/*!
	Function to load the button data
	@param filePath - The path to the image for the button
	@return None
	*/
	void SetButtonImage(Sprite _sprite);
	/*!
	Set the text that appears in the button, this text will be at the centre
	@param text - The text to display
	@return None
	*/
	void SetButtonText(const char* text);

	void SetButtonPosition(AEVec2 pos);
	/*
	Function to render the button, called every frame.

	Make sure to call this function in your scene's Update()
	@param None
	@return None
	*/
	void Render(void);
	/*
	Function to update the button every frame.
	Input checks happen here.
	This function is called in Render()
	@param None
	@return None
	*/
	void Update(void);

	Button(void);
	Button(AEVec2, float, float, const char*, Color4 textColor = Color4(1,1,1,1));
	~Button(void);
};