#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "../UI_WZBJ_Pak.hpp"

class CurrencyDisplay : public SoloBehavior
{
private:
	EntityManager* enSystem = nullptr;
	void DisplayCurrency();
public:	
	TextBox* textbox = nullptr;

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	CurrencyDisplay() {}
	~CurrencyDisplay() {}
};