#pragma once
#include "../SceneHandler_WZBJ_Pak.hpp"
#include "../Engine_WZBJ_Pak.hpp"
#include "NavigationData.hpp"

using namespace std;

class EntityManager;


class MapDisplay : public SoloBehavior
{
private:

public:
	NavigationData& map;
	std::list<Entity*> mapNodesReal;
	std::list<Entity*> mapNodesFog;

	EntityManager* enSystem = nullptr;

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	MapDisplay(NavigationData& _map) : mapNodesReal{ nullptr }, mapNodesFog{ nullptr }, map{ _map } {}
	~MapDisplay() {}

};