#pragma once
#ifndef _InputInterfaces_
#include <iostream>
#include "UIElement.hpp"


struct PointerEventData
{
    s32 x;
    s32 y;

    s32 delta_x;
    s32 delta_y;

    UIElement* currentUIObject;
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