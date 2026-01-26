#pragma once
#ifndef _InputInterfaces_
#include <iostream>


enum class MouseButton
{
    LEFT,
    RIGHT,
    MIDDLE
};

struct PointerEventData
{
    int x;
    int y;

    int deltaX;
    int deltaY;

    MouseButton button;
    int clickCount;
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

struct IDrag
{
    virtual ~IDrag() = default;
    virtual void OnDrag(const PointerEventData& event) = 0;
};



#endif