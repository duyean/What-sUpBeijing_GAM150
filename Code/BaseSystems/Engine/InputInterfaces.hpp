/*!
@file InputInterfaces.hpp
@author Tan Yifeng, Edmund (t.yifengedmund)
@course CSD11451
@section B
@Final Project GAM 150
@date 01/04/26
@brief
This file contains pointer input event data structures and pure virtual
interfaces for handling mouse pointer events such as press, release,
trigger, and drag
*//*______________________________________________________________________*/
#pragma once
#ifndef _InputInterfaces_
#include <iostream>


struct PointerEventData
{
    //mouse world space x coordinates
    s32 x;
    //mouse world space y coordinates
    s32 y;

    //mouse screen space x coordinates
    s32 delta_x;
    //mouse screen space y coordinates
    s32 delta_y;
};

struct IPointerDown
{
    virtual ~IPointerDown() = default;

	/*!***********************************************************************
	* \brief
	* Called when a pointer (mouse button) press is detected
	* \param[in] event
	* The pointer event data containing position information
	*************************************************************************/
    virtual void OnPointerDown(const PointerEventData& event) = 0;
};

struct IPointerUp
{
    virtual ~IPointerUp() = default;

	/*!***********************************************************************
	* \brief
	* Called when a pointer (mouse button) release is detected
	* \param[in] event
	* The pointer event data containing position information
	*************************************************************************/
    virtual void OnPointerUp(const PointerEventData& event) = 0;
};

struct IPointerTriggered
{
    virtual ~IPointerTriggered() = default;

	/*!***********************************************************************
	* \brief
	* Called when a pointer click is fully triggered (press and release)
	* \param[in] event
	* The pointer event data containing position information
	*************************************************************************/
    virtual void OnPointerTriggered(const PointerEventData& event) = 0;
};

struct IDrag
{
    virtual ~IDrag() = default;

	/*!***********************************************************************
	* \brief
	* Called while the pointer is being dragged (held and moved)
	* \param[in] event
	* The pointer event data containing position and delta information
	*************************************************************************/
    virtual void OnDrag(const PointerEventData& event) = 0;
};



#endif

