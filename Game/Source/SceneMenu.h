#pragma once
#ifndef __SCENEMENU_H__
#define __SCENEMENU_H__

#include "Module.h"
#include "Player.h"
#include "Item.h"
#include "Effect.h"
#include "Enemy_Goblin.h"
#include "Boss.h"
#include "PlayerLife.h"
#include "Angel.h"
#include "Item.h"
#include "BossItem.h"
#include "Diamond.h"
#include "Cura.h"
#include "Teleport.h"
#include "GuiControl.h"
#include "GuiControlButton.h"

struct SDL_Texture;

class SceneMenu : public Module
{
public:

	SceneMenu(bool start_Enabled = true);


	// Destructor
	virtual ~SceneMenu();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();


	GuiControlButton* GetGuiControlButton();
	void menu();
	void creditos();
	bool OnGuiMouseClickEvent(GuiControl* control);
	void setting();

private:
	SDL_Texture* img;
	float textPosX, textPosY = 0;
	uint texW, texH;

	std::vector<GuiControl*> deleteControl;
public:

	uint windowW, windowH;
	GuiControlButton* gcButtom;


	SDL_Texture* fondotexture;
	const char* fondoPath;

	SDL_Texture* title_texture;
	const char* title_Path;

	SDL_Texture* normal_texture;
	const char* normal_Path;


	SDL_Texture* Credits_texture;
	const char* Credits_Path;




	bool newScena = false;
	bool newgame = false;

	bool showMenu = true;
	bool showCredits = false;
	bool showSetting = false;
	bool showButton = false;
};

#endif // __SCENE_H__