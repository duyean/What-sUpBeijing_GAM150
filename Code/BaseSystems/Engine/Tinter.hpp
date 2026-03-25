#pragma once
#ifndef _Bounce_
#include <iostream>
#include <cstdint>
#include <vector>
#include <crtdbg.h> // To check for memory leaks
#include <mutex>
#include <map>
#include <memory>
#include "AEEngine.h"
#include "OOP.hpp"
#include "Colors.hpp"
#include "Entity.hpp"


class Tinter : public SoloBehavior
{

    float duration = 1.f;
    float timer = 0.f;
    Color originalColor{};
    bool tinting = false;
public:
    void awake() override;
    void init() override;
    void update() override;
    void fixedUpdate() override;
    void destroy() override;
    void Trigger();
    Tinter(float _duration) : duration(_duration) {}
    ~Tinter() {}

};


#endif