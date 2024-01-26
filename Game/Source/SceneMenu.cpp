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
	bool ret = true;


	fondoPath = config.child("menu").child("fondo").attribute("texturePath").as_string();
	Credits_Path = config.child("menu").child("credits").attribute("texturePath").as_string();
	title_Path = config.child("menu").child("title").attribute("texturePath").as_string();
	normal_Path = config.child("menu").child("normal").attribute("texturePath").as_string();
	barra_Path = config.child("menu").child("barra").attribute("texturePath").as_string();
	box_Path = config.child("menu").child("box").attribute("texturePath").as_string();
	victoria_Path = config.child("menu").child("victoria").attribute("texturePath").as_string();
	gameOver_Path = config.child("menu").child("gameOver").attribute("texturePath").as_string();


	return ret;
}

// Called before the first frame
bool SceneMenu::Start()
{
	app->win->GetWindowSize(windowW, windowH);

	//app->map->Load();

	fondotexture = app->tex->Load(fondoPath);
	Credits_texture = app->tex->Load(Credits_Path);
	title_texture = app->tex->Load(title_Path);
	normal_texture = app->tex->Load(normal_Path);
	barra_texture = app->tex->Load(barra_Path);
	box_texture = app->tex->Load(box_Path);
	victoria_texture = app->tex->Load(victoria_Path);
	gameOver_texture = app->tex->Load(gameOver_Path);

	if (!app->scene->GetItem()->victoria && !app->scene->GetPlayer()->lose) {
		menu();
	}
	else {

		showButton = true;
	}
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


	SDL_Rect rect1 = { 0,0,1920,1080 };
	app->render->DrawTexture(fondotexture, -320, 0, 0.8, SDL_FLIP_NONE, &rect1, 0, 0);

	app->render->DrawTexture(title_texture, -160, -30, 0.7, SDL_FLIP_NONE, &rect1, 0, 0);


	if (app->scene->GetItem()->victoria) {

		app->render->DrawTexture(victoria_texture, -160, -60, 0.7, SDL_FLIP_NONE, &rect1, 0, 0);
		if (showButton) {
			victoria();
			showButton = false;
		}
	}
	else if (app->scene->GetPlayer()->lose) {

		app->render->DrawTexture(gameOver_texture, -160, -60, 0.7, SDL_FLIP_NONE, &rect1, 0, 0);

		if (showButton) {
			victoria();
			showButton = false;
		}


	}
	else {
		if (showMenu) {
			menu();
			showMenu = false;
		}

		if (!showMenu && showCredits) {
			SDL_Rect rect2 = { 0,0,1920,1080 };
			app->render->DrawTexture(Credits_texture, -63, 50, 0.6, SDL_FLIP_NONE, &rect2, 0, 0);

			if (showButton) {
				creditos();
				showButton = false;
			}
		}

		if (!showMenu && showSetting) {
			printSetting();

			if (showButton) {
				setting();
				showButton = false;
			}
		}

	}
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

	for (auto obj : deleteControl) {
		app->guiManager->DestroyGuiControl(obj);
	}

	return true;
}

GuiControlButton* SceneMenu::GetGuiControlButton()
{
	return gcButtom;
}

void SceneMenu::menu()
{

	SDL_Rect btPos = { windowW / 2 - 50, windowH / 2 - 130 , 200,50 };
	gcButtom = (GuiControlButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, "PLAY", btPos, this);
	deleteControl.push_back(gcButtom);

	SDL_Rect btPos1 = { windowW / 2 - 50, windowH / 2 - 30, 200,50 };
	gcButtom = (GuiControlButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, "CONTINUE", btPos1, this);
	deleteControl.push_back(gcButtom);

	SDL_Rect btPos2 = { windowW / 2 - 50, windowH / 2 + 70, 200,50 };
	gcButtom = (GuiControlButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, "SETTINGS", btPos2, this);
	deleteControl.push_back(gcButtom);

	SDL_Rect btPos3 = { windowW / 2 - 50, windowH / 2 + 170, 200,50 };
	gcButtom = (GuiControlButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, "CREDITS", btPos3, this);
	deleteControl.push_back(gcButtom);

	SDL_Rect btPos4 = { windowW / 2 - 50, windowH / 2 + 270, 200,50 };
	gcButtom = (GuiControlButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, "EXIT", btPos4, this);
	deleteControl.push_back(gcButtom);
}

void SceneMenu::creditos()
{
	SDL_Rect btPos3 = { windowW / 2 - 50, windowH / 2 + 230, 200,50 };
	gcButtom = (GuiControlButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, "RETURN", btPos3, this);
	deleteControl.push_back(gcButtom);
}

bool SceneMenu::OnGuiMouseClickEvent(GuiControl* control)
{
	switch (control->id)
	{
	case 1:
		app->scene->GetItem()->victoria = false;
		app->scene->GetPlayer()->lose = false;
		newgame = true;
		app->scenemenu->Disable();
		app->SaveRequest();
		app->fade->FadeToBlack(app->scenemenu, app->scene, 10);

		printf("play");
		break;

	case 2:
			newScena = false;
			printf("continue");

			app->scenemenu->Disable();
			app->scene->GetItem()->victoria = false;
			app->scene->GetPlayer()->lose = false;
			app->fade->FadeToBlack(app->scenemenu, app->scene, 10);
			app->scene->GetPlayerLife()->newmap = false;
			app->LoadRequest();
			app->scene->GetPlayerLife()->newmap = true;

		break;
	case 3:
		newScena = false;
		printf("setting");

		for (GuiControl* obj : deleteControl) {
			obj->state = GuiControlState::DISABLED;
			app->guiManager->DestroyGuiControl(obj);
		}

		showMenu = false;
		showSetting = true;
		showButton = true;
		break;
	case 4:
		newScena = false;
		printf("credits");
		for (GuiControl* obj : deleteControl) {
			obj->state = GuiControlState::DISABLED;
			app->guiManager->DestroyGuiControl(obj);
		}
		showMenu = false;
		showCredits = true;
		showButton = true;
		break;
	case 5:
		newScena = false;
		printf("exit");
		app->closeGame = false;
		break;
	case 6:
		newScena = false;
		printf("return");
		for (GuiControl* obj : deleteControl) {
			obj->state = GuiControlState::DISABLED;
			app->guiManager->DestroyGuiControl(obj);
		}
		showMenu = true;
		showCredits = false;
		showSetting = false;
		app->scene->GetItem()->victoria = false;
		app->scene->GetPlayer()->lose = false;
		app->scene->GetPlayer()->dieCount = 0;
		app->guiManager->DestroyGuiControl(gcButtom);
		break;
	}


	return false;
}

void SceneMenu::setting()
{
	SDL_Rect btPos3 = { windowW / 2 - 50, windowH / 2 + 250, 200,50 };
	gcButtom = (GuiControlButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, "RETURN", btPos3, this);
	deleteControl.push_back(gcButtom);

}

void SceneMenu::printSetting()
{
	settingPosX = -300;
	SDL_Rect btPos1 = { 0,0, 1920,1080 };
	app->render->DrawTexture(normal_texture, settingPosX, -150, 0.7, SDL_FLIP_NONE, &btPos1, 0, 0);
	app->render->DrawText("MUSICA", 320, 210, 100, 50);

	app->render->DrawTexture(normal_texture, settingPosX, -50, 0.7, SDL_FLIP_NONE, &btPos1, 0, 0);
	app->render->DrawText("FX VOLUME", 320, 310, 120, 50);


	app->render->DrawTexture(normal_texture, settingPosX, 50, 0.7, SDL_FLIP_NONE, &btPos1, 0, 0);
	app->render->DrawText("FULL SCREEN", 320, 410, 140, 50);

	app->render->DrawTexture(normal_texture, settingPosX, 150, 0.7, SDL_FLIP_NONE, &btPos1, 0, 0);
	app->render->DrawText("VSync", 320, 510, 100, 50);

	app->render->DrawTexture(barra_texture, settingPosX + 10, -235, 0.8, SDL_FLIP_NONE, &btPos1, 0, 0);
	app->render->DrawTexture(barra_texture, settingPosX + 10, -135, 0.8, SDL_FLIP_NONE, &btPos1, 0, 0);

	app->render->DrawTexture(box_texture, -40, -125, 0.6, SDL_FLIP_NONE, &btPos1, 0, 0);
	app->render->DrawTexture(box_texture, -40, -25, 0.6, SDL_FLIP_NONE, &btPos1, 0, 0);

}

void SceneMenu::victoria()
{

	SDL_Rect btPos3 = { windowW / 2 - 50, windowH / 2 + 100, 200,50 };
	gcButtom = (GuiControlButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, "RETURN", btPos3, this);
	deleteControl.push_back(gcButtom);

	SDL_Rect btPos4 = { windowW / 2 - 50, windowH / 2 + 250, 200,50 };
	gcButtom = (GuiControlButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, "EXIT", btPos4, this);
	deleteControl.push_back(gcButtom);
}


