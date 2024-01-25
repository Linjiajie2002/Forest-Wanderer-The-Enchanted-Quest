#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "Effect.h"
#include "Enemy_Goblin.h"
#include "Enemy_Flyeye.h"
#include "Boss.h"
#include "BossItem.h"
#include "PlayerLife.h"
#include "Angel.h"
#include "Diamond.h"
#include "Cura.h"
#include "Teleport.h"
#include "GuiControl.h"
#include "GuiManager.h"
#include "GuiControlButton.h"
#include "SceneMenu.h"

#include "Defs.h"
#include "Log.h"
#include <map>

SceneMenu::SceneMenu(bool start_Enabled) : Module(start_Enabled)
{
	name.Create("scenemenu");
}

// Destructor
SceneMenu::~SceneMenu()
{}

// Called before render is available
bool SceneMenu::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;
	

	return ret;
}

// Called before the first frame
bool SceneMenu::Start()
{
	app->win->GetWindowSize(windowW, windowH);

	//app->map->Load();

	SDL_Rect btPos = { windowW / 2 -50, windowH / 2 - 130 , 200,50 };
	gcButtom = (GuiControlButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "PLAY", btPos, this);

	SDL_Rect btPos1 = { windowW / 2 - 50, windowH / 2 - 30, 200,50 };
	gcButtom = (GuiControlButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "CONTINUE", btPos1, this);

	SDL_Rect btPos2 = { windowW / 2 - 50, windowH / 2 + 70, 200,50 };
	gcButtom = (GuiControlButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "SETTINGS", btPos2, this);

	SDL_Rect btPos3 = { windowW / 2 - 50, windowH / 2 + 170, 200,50 };
	gcButtom = (GuiControlButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "CREDITS", btPos3, this);

	SDL_Rect btPos4 = { windowW / 2 - 50, windowH / 2 + 270, 200,50 };
	gcButtom = (GuiControlButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, "EXIT", btPos4, this);

	return true;
}

// Called each loop iteration
bool SceneMenu::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool SceneMenu::Update(float dt)
{
	

	return true;
}

// Called each loop iteration
bool SceneMenu::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool SceneMenu::CleanUp()
{

	LOG("Freeing scene");

	return true;
}

