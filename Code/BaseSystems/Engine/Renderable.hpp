/*!
@file Renderable.hpp
@author Tan Yifeng, Edmund (t.yifengedmund)
@course CSD11451
@section B
@Final Project GAM 150
@date 01/04/26
@brief
This file contains the IRenderable interface which provides a draw order
property for any object that participates in the rendering system
*//*______________________________________________________________________*/
#pragma once
#ifndef REND_
#define REND_

#include "AEEngine.h"
#include "Colors.hpp"

class IRenderable {
public:
    int drawOrder = 100;
    virtual ~IRenderable() = default;
};

#endif

