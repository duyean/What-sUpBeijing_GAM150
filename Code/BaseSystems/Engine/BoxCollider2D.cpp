#include "BoxCollider2D.hpp"
#include "Entity.hpp"
#include "PhysicSystem.hpp"

//Setup Physics System
PhysicSystem* phSystem = PhysicSystem::getInstance();

void BoxCollider2D::awake()
{
	phSystem->registerCollider(this);
}


void BoxCollider2D::init()
{
	
}

void BoxCollider2D::update()
{

}

void BoxCollider2D::fixedUpdate()
{
	
}

void BoxCollider2D::destroy()
{
	phSystem->unregisterCollider(this);
	onEnter.clear();
	onStay.clear();
	onExit.clear();

}
