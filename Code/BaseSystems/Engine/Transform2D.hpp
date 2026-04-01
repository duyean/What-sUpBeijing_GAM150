/*!
@file Transform2D.hpp
@author Tan Yifeng, Edmund (t.yifengedmund)
@course CSD11451
@section B
@Final Project GAM 150
@date 01/04/26
@brief
This file contains the Transform2D component which manages the world and
local position, rotation, and scale of an entity, with support for
parent-child hierarchies
*//*______________________________________________________________________*/
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
	bool activeDirty = false;

	Transform2D* parent = nullptr;
	std::vector<Transform2D*> children;

	/*!***********************************************************************
	* \brief
	* Adds a child Transform2D to this transform's hierarchy and sets
	* the child's parent pointer
	* \param[in] child
	* A pointer to the Transform2D to add as a child
	*************************************************************************/
	void AddChild(Transform2D* child) {
		children.push_back(child);
		child->parent = this;
	}

	/*!***********************************************************************
	* \brief
	* Called once when the component is first created, before init
	*************************************************************************/
	void awake() override;

	/*!***********************************************************************
	* \brief
	* Called once before the first update, used for initialisation
	*************************************************************************/
	void init() override;

	/*!***********************************************************************
	* \brief
	* Called every frame, propagates dirty transform changes down the hierarchy
	*************************************************************************/
	void update() override;

	/*!***********************************************************************
	* \brief
	* Called at a fixed timestep, used for physics-based updates
	*************************************************************************/
	void fixedUpdate() override;

	/*!***********************************************************************
	* \brief
	* Called when the component is destroyed, used for cleanup
	*************************************************************************/
	void destroy() override;

	/*!***********************************************************************
	* \brief
	* Propagates transform changes from parent to child transforms in the hierarchy
	*************************************************************************/
	void syncTransform();

	/*!***********************************************************************
	* \brief
	* Marks this transform and all its children as dirty so they will
	* be recalculated on the next update
	*************************************************************************/
	void MarkDirty();

	/*!***********************************************************************
	* \brief
	* Returns the world space position of this transform
	* \return
	* The world position as an AEVec2
	*************************************************************************/
	AEVec2 getPosition() const;

	/*!***********************************************************************
	* \brief
	* Sets the world space position of this transform, marking it dirty
	* \param[in] worldPos
	* The new world position to assign
	*************************************************************************/
	void setPosition(const AEVec2& worldPos);

	/*!***********************************************************************
	* \brief
	* Returns the local position of this transform relative to its parent
	* \return
	* The local position as an AEVec2
	*************************************************************************/
	AEVec2 getLocalPosition() const;

	/*!***********************************************************************
	* \brief
	* Sets the local position of this transform relative to its parent,
	* marking it dirty
	* \param[in] pos
	* The new local position to assign
	*************************************************************************/
	void setLocalPosition(const AEVec2& pos);

	/*!***********************************************************************
	* \brief
	* Returns the world space rotation of this transform in degrees
	* \return
	* The world rotation in degrees
	*************************************************************************/
	float getRotation() const;

	/*!***********************************************************************
	* \brief
	* Sets the world space rotation of this transform in degrees,
	* marking it dirty
	* \param[in] worldDegrees
	* The new world rotation in degrees
	*************************************************************************/
	void setRotation(float worldDegrees);

	/*!***********************************************************************
	* \brief
	* Returns the local rotation of this transform in degrees relative to its parent
	* \return
	* The local rotation in degrees
	*************************************************************************/
	float getLocalRotation() const;

	/*!***********************************************************************
	* \brief
	* Sets the local rotation of this transform in degrees relative to its parent,
	* marking it dirty
	* \param[in] degrees
	* The new local rotation in degrees
	*************************************************************************/
	void setLocalRotation(float degrees);

	/*!***********************************************************************
	* \brief
	* Returns the world space scale of this transform
	* \return
	* The world scale as an AEVec2
	*************************************************************************/
	AEVec2 getScale() const;

	/*!***********************************************************************
	* \brief
	* Sets the world space scale of this transform, marking it dirty
	* \param[in] worldScale
	* The new world scale to assign
	*************************************************************************/
	void setScale(const AEVec2& worldScale);

	/*!***********************************************************************
	* \brief
	* Returns the local scale of this transform relative to its parent
	* \return
	* The local scale as an AEVec2
	*************************************************************************/
	AEVec2 getLocalScale() const;

	/*!***********************************************************************
	* \brief
	* Sets the local scale of this transform relative to its parent,
	* marking it dirty
	* \param[in] _scale
	* The new local scale to assign
	*************************************************************************/
	void setLocalScale(const AEVec2& _scale);

	Transform2D() {

	}

	/*!***********************************************************************
	* \brief
	* Constructs a Transform2D with given local position, scale, and rotation
	* \param[in] pos
	* The initial local position
	* \param[in] sca
	* The initial local scale
	* \param[in] degree
	* The initial local rotation in degrees
	*************************************************************************/
	Transform2D(AEVec2 pos, AEVec2 sca, float degree) {
		localPosition = pos;
		localScale = sca;
		localDeg = degree;
	}

	/*!***********************************************************************
	* \brief
	* Constructs a Transform2D with given local position components, scale
	* components, and rotation
	* \param[in] x
	* The initial local X position
	* \param[in] y
	* The initial local Y position
	* \param[in] scaleX
	* The initial local X scale
	* \param[in] scaleY
	* The initial local Y scale
	* \param[in] degree
	* The initial local rotation in degrees
	*************************************************************************/
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

