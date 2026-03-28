#pragma once
#include "../Engine_WZBJ_Pak.hpp"
#include "../UI_WZBJ_Pak.hpp"

class TutorialScreen : public SoloBehavior
{
public:
	enum struct TUTORIAL_TYPE
	{
		TUTORIAL_BASE_CAMP,
		TUTORIAL_EXPLORATION,
		TUTORIAL_COMBAT
	};
private:	
	EntityManager* enSystem = nullptr;
	MeshGen* meSystem = nullptr;
	std::vector<Entity*> prevDisplay;
	
	void NextSlide();
	void PrevSlide();

	TextBox* tutorial_tb = nullptr;
	Mesh* tutorial_img = nullptr;
	Button* nextButton = nullptr;
	Button* prevButton = nullptr;
	Button* closeButton = nullptr;

	#define BCT_PAGES 2
	#define ET_PAGES 2
	#define CT_PAGES 6

	const char* tutorialTitle = nullptr;
	struct TutorialPage
	{
		const char* textureDir;
		const char* textureName;
		const char* desc;
	};

	TutorialPage bc_tut_pages[BCT_PAGES] =
	{
		{"../../Assets/Images/BaseCampTutorial/bct_1.png", "bct1", "Welcome to your base! Use the WASD keys to move around!"},
		{"../../Assets/Images/BaseCampTutorial/bct_2.png", "bct2", "Visit the shop to buy Blessings and Artifacts to help in your run!"},
	};

	TutorialPage explr_tut_pages[ET_PAGES] =
	{
		{"../../Assets/Images/ExplorationTutorial/et_1.png", "et1", "In the exploration phase, you can traverse through area nodes. Traversible areas are marked by the black arrows."},
		{"../../Assets/Images/ExplorationTutorial/et_2.png", "et2", "Make use of the minimap to guide you! Each node is inidcated by a unique icon!"},
	};

	TutorialPage cmbt_tut_pages[CT_PAGES] =
	{
		{"../../Assets/Images/CombatTutorial/ct_0.png", "ct0", "Welcome to your first battle! This tutorial will teach you the basics of combat."},
		{"../../Assets/Images/CombatTutorial/ct_1.png", "ct1", "Choose which move to use by clicking on the buttons"},
		{"../../Assets/Images/CombatTutorial/ct_2.png", "ct2", "Your current chracter's health is displayed here."},
		{"../../Assets/Images/CombatTutorial/ct_3.png", "ct3", "Your current Party's health bar is displayed here."},
		{"../../Assets/Images/CombatTutorial/ct_4.png", "ct4", "Click on enemies to change your current target. The current target is marked by the red circle."},
		{"../../Assets/Images/CombatTutorial/ct_5.png", "ct5", "Some moves will either do buffs to your allies or debuffs to enemies. Choose wisely!"}
	};

	TUTORIAL_TYPE tut_type;

	int currentPage = 0;
	std::vector<TutorialPage> tutorialPages;

public:
	void ShowTutorial(bool canShow);
	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

	void AddPrevDisplayEntity(Entity* en);
	TutorialScreen(TUTORIAL_TYPE type) : tut_type(type){}
	~TutorialScreen() {};
};