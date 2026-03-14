#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "../Code/Combat/Blessing/Blessing.hpp"

class ShopBlessing : public SoloBehavior
{
public:
	std::string GetTextureName();
	BLESSING_ID GetBlessingId();

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	ShopBlessing();
	~ShopBlessing();
private:
	BLESSING_ID blessingId;
	std::string texture;
};

