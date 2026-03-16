#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "../UI_WZBJ_Pak.hpp"

class Slider : public SoloBehavior
{
private:
	Button* inc_button;
	Button* dec_button;
	TextBox* display;

	EntityManager* enSystem = nullptr;
	MeshGen* meSystem = nullptr;
public:
	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	Slider() = default;
	~Slider() {}
};