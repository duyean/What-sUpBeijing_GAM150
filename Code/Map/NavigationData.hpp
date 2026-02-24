#pragma once
#include "NavigationDataClass.hpp"

//Class-based definition and implementation are in NavigationData.cpp

//any further functions that do not piggyback off NavigationDataClass go below.

void TravelNode(NavigationData& data, int newX, int newY);
void GetCurrentNodeInfo(NavigationData data);