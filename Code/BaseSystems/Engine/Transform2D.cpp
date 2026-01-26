#include "Transform2D.hpp"
#include "../EaseFunctions/AEVEC2OVERLOAD.hpp"

//Transforms
void Transform2D::awake()
{

}
void Transform2D::init()
{

}

void Transform2D::MarkDirty()
{
    dirty = true;
    for (auto* child : children)
    {
        child->MarkDirty();
    }
}

AEVec2 Transform2D::getPosition() const {
    if (parent) return parent->getPosition() + localPosition;
    return localPosition;
}

void Transform2D::setPosition(const AEVec2& worldPos) {
    localPosition = parent ? worldPos - parent->getPosition() : worldPos;
    MarkDirty();
    syncTransform();
}

AEVec2 Transform2D::getLocalPosition() const { return localPosition; }

void Transform2D::setLocalPosition(const AEVec2& pos) {
	localPosition = pos;
	MarkDirty();
	syncTransform();
}

float Transform2D::getRotation() const { // world rotation getter
	return parent ? parent->getRotation() + localDeg : localDeg;
}

void Transform2D::setRotation(float worldDegrees) { // world rotation setter
	localDeg = parent ? worldDegrees - parent->getRotation() : worldDegrees;
	MarkDirty();
	syncTransform();
}

float Transform2D::getLocalRotation() const { return localDeg; }
void Transform2D::setLocalRotation(float degrees) {
	localDeg = degrees;
	MarkDirty();
	syncTransform();
}

AEVec2 Transform2D::getScale() const { // world scale getter
	return parent ? parent->getScale() * localScale : localScale; // component-wise multiply
}

void Transform2D::setScale(const AEVec2& worldScale) { // world scale setter
	localScale = parent ? worldScale / parent->getScale() : worldScale;
	MarkDirty();
	syncTransform();
}

AEVec2 Transform2D::getLocalScale() const { return localScale; }
void Transform2D::setLocalScale(const AEVec2& scale) {
	localScale = scale;
	MarkDirty();
	syncTransform();
}

void Transform2D::syncTransform()
{
    if (dirty)
    {
        if (parent) {
            position = parent->position + localPosition;
            rotation = parent->rotation + localRotation;
            Deg = parent->Deg + localDeg;
            scale = parent->scale * localScale;
        }
        else {
            position = localPosition;
            rotation = localRotation;
            Deg = localDeg;
            scale = localScale;
        }

        for (Transform2D* child : children) {
            child->syncTransform();
        }
    }
}

void Transform2D::update()
{
    syncTransform();
    
}
void Transform2D::fixedUpdate()
{

}
void Transform2D::destroy()
{

}