#pragma once
#include "../Engine_WZBJ_Pak.hpp"

class DisplayBox : public SoloBehavior
{
	float onClickDestroyTimer;
	const char* header;
	const char* title;
	const char* desc;
	const char* footer;

	std::vector<Entity*> children;
public:
	DisplayBox();
	DisplayBox(const char* head, const char* t, const char* d, const char* foot);
	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;
};