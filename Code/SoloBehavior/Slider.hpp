#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "../UI_WZBJ_Pak.hpp"

class Slider : public SoloBehavior
{
private:
	Button* button_inc = nullptr;
	Button* button_dec = nullptr;

	int max_value = 10;
	int value = 0;

	EntityManager* enSystem = nullptr;
	MeshGen* meSystem = nullptr;

public:
	using Callback = std::function<void()>;
	TextBox* text = nullptr;
	Color slider_color;
	Color background_color;

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	void Increase();
	void Decrease();

	Slider() {}
	~Slider() {}

private:
	Callback onIncrease;
	Callback onDecrease;
};