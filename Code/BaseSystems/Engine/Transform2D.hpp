#pragma once
#ifndef _Transform_
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


using namespace std;


class Transform2D : public SoloBehavior
{

	AEVec2 localPosition = {};
	AEVec2 localRotation = {};
	AEVec2 localScale = {};

	AEVec2 position = {};
	AEVec2 rotation = {};
	AEVec2 scale = {};


	float Deg = 0.f;
	float localDeg = 0.f;

	bool dirty = false;

public:
	Transform2D* parent = nullptr;
	std::vector<Transform2D*> children;


	void AddChild(Transform2D* child) {
		children.push_back(child);
		child->parent = this;
	}

	

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	void syncTransform();

	void MarkDirty();

	AEVec2 getPosition() const;

	void setPosition(const AEVec2& worldPos);

	AEVec2 getLocalPosition() const;

	void setLocalPosition(const AEVec2& pos);

	float getRotation() const;

	void setRotation(float worldDegrees);
	

	float getLocalRotation() const;
	void setLocalRotation(float degrees);

	AEVec2 getScale() const;

	void setScale(const AEVec2& worldScale);

	AEVec2 getLocalScale() const;
	void setLocalScale(const AEVec2& scale);

	Transform2D() {

	}

	Transform2D(AEVec2 pos, AEVec2 sca, float degree) {
		localPosition = pos;
		localScale = sca;
		localDeg = degree;
	}

	Transform2D(float x, float y, float scaleX, float scaleY, float degree) {
		localPosition.x = x;
		localPosition.y = y;
		localScale.x = scaleX;
		localScale.y = scaleY;
		localDeg = degree;
	}

	~Transform2D()
	{

	}

};


#endif