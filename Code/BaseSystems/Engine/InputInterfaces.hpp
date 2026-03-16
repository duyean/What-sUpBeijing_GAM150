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
    virtual void OnPointerDown(const PointerEventData& event) = 0;
};

struct IPointerUp
{
    virtual ~IPointerUp() = default;
    virtual void OnPointerUp(const PointerEventData& event) = 0;
};

struct IPointerTriggered
{
    virtual ~IPointerTriggered() = default;
    virtual void OnPointerTriggered(const PointerEventData& event) = 0;
};

struct IDrag
{
    virtual ~IDrag() = default;
    virtual void OnDrag(const PointerEventData& event) = 0;
};



#endif