#pragma once
#ifndef _Overload_
#include <iostream>
#include <cstdint>
#include <vector>
#include <crtdbg.h> // To check for memory leaks
#include <mutex>
#include <map>
#include <memory>
#include "AEEngine.h"


AEVec2 operator+(const AEVec2& lhs, const AEVec2& rhs);

AEVec2 operator-(const AEVec2& lhs, const AEVec2& rhs);

AEVec2 operator*(const AEVec2& lhs, const AEVec2& rhs);

AEVec2 operator/(const AEVec2& lhs, const AEVec2& rhs);

AEVec2 abs(const AEVec2& lhs);
#endif