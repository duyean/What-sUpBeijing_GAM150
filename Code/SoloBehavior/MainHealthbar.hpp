#pragma once
#include "AEEngine.h"
#include "../BaseSystems/Engine/OOP.hpp"
#include "../BaseSystems/Engine/EntityManager.hpp"

class MainHealthbar : public SoloBehavior
{
public:
	EntityManager* enSystem = nullptr;
	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	MainHealthbar() = default;
	~MainHealthbar() = default;
};

