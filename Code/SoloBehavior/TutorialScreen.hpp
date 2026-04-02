/******************************************************************************/
/*!
\file   TutorialScreen.hpp
\author Tai Qian Yi
\par    Email: t.qianyi\@digipen.edu
\par    DigiPen login: t.qianyi
\par    Course: CSD1451
\par    Section B
\brief  This file contains the declarations of functions for Tutorial Screen
*/
/******************************************************************************/
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
		TUTORIAL_COMBAT,
		HOW_TO_PLAY
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
	#define ET_PAGES 4
	#define CT_PAGES 7

	const char* tutorialTitle = nullptr;
	struct TutorialPage
	{
		const char* textureDir;
		const char* textureName;
		const char* desc;
	};

	TutorialPage bc_tut_pages[BCT_PAGES] =
	{
		{"../../Assets/Images/BaseCampTutorial/bct_1.png", "bct1", "Welcome to your Odium! The capital is under attack and you need to drive the enemies back! Use the WASD keys to move around!"},
		{"../../Assets/Images/BaseCampTutorial/bct_2.png", "bct2", "Visit the shop to buy Blessings and Artifacts to help in your run!"},
	};

	TutorialPage explr_tut_pages[ET_PAGES] =
	{
		{"../../Assets/Images/ExplorationTutorial/et_1.png", "et1", "In the exploration phase, you can traverse through area nodes. Traversible areas are marked by the black arrows."},
		{"../../Assets/Images/ExplorationTutorial/et_2.png", "et2", "Make use of the minimap to guide you! Each node is inidcated by a unique icon!"},
		{"../../Assets/Images/ExplorationTutorial/et_3.png", "et3", "Minibosses are marked by the orange question marks. Defeat minibosses to gain party members!"},
		{"../../Assets/Images/ExplorationTutorial/et_4.png", "et4", "The boss node is marked by the red exit icon! Find the boss and defeat it to advance! Defeat all 3 bosses to acheive victory!"}
	};

	TutorialPage cmbt_tut_pages[CT_PAGES] =
	{
		{"../../Assets/Images/CombatTutorial/ct_0.png", "ct0", "Welcome to your first battle! This tutorial will teach you the basics of combat."},
		{"../../Assets/Images/CombatTutorial/ct_1.png", "ct1", "Choose which move to use by clicking on the buttons. Characters have action points. More powerful moves will cost action points while weaker moves will gain action points."},
		{"../../Assets/Images/CombatTutorial/ct_2.png", "ct2", "Your current character's action points and the turn number are displayed here."},
		{"../../Assets/Images/CombatTutorial/ct_3.png", "ct3", "Your current Party's health bar is displayed here. Use it to track each Party Member's health!"},
		{"../../Assets/Images/CombatTutorial/ct_4.png", "ct4", "Click on enemies to change your current target. The current target is marked by the red crosshair."},
		{"../../Assets/Images/CombatTutorial/ct_5.png", "ct5", "Some moves will either do buffs to your allies or debuffs to enemies. Choose wisely!"},
		{"../../Assets/Images/CombatTutorial/ct_6.png", "ct6", "Watch out! If any of your allies fall, you will lose them permanently!"}
	};

	TUTORIAL_TYPE tut_type;

	int currentPage = 0;
	std::vector<TutorialPage> tutorialPages;

public:
/*!***********************************************************************
\brief Function to toggle tuorial page showing
\param canShow
*************************************************************************/
	void ShowTutorial(bool canShow);

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

/*!***********************************************************************
\brief Function to add previous display objects to hide them
\param en
Pointer to the display Entity object
*************************************************************************/
	void AddPrevDisplayEntity(Entity* en);
/*!***********************************************************************
\brief Single arguement contructor of the Tutorial Screen
\param type
The type of tutorial we want
*************************************************************************/
	TutorialScreen(TUTORIAL_TYPE type) : tut_type(type){}
	~TutorialScreen() {};
};