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