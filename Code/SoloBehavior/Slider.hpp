#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "../UI_WZBJ_Pak.hpp"

class Slider : public SoloBehavior
{
private:
	//Button* button_inc = nullptr;
	//Button* button_dec = nullptr;
	Entity* slider = nullptr;

	float max_value;
	float value;
	float changeFactor;

	EntityManager* enSystem = nullptr;
	MeshGen* meSystem = nullptr;

	void Increase(float& val, float const& max_val);
	void Decrease(float& val);

	std::vector<Entity*>sliderComp;
public:
	
	TextBox* text = nullptr;
	Color slider_color = Color{ 100, 100, 100, 1.f };
	Color background_color = Color{ 200, 200, 200, 1.f };

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	void SliderSetActive(bool active);

	Slider(float& val, float const& max_val, float _changeFactor) :
		value(val), max_value(max_val), changeFactor(_changeFactor) { }
	~Slider() {}
	
};