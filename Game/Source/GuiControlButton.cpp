#include "GuiControlButton.h"
#include "Render.h"
#include "App.h"
#include "Audio.h"
#include "Textures.h"
#include "Scene.h"
#include "Map.h"
#include "GuiManager.h"

GuiControlButton::GuiControlButton(uint32 id, SDL_Rect bounds, const char* text) : GuiControl(GuiControlType::BUTTON, id)
{
	this->bounds = bounds;
	this->text = text;

	canClick = true;
	drawBasic = false;
	pugi::xml_document configFile;
	pugi::xml_node menuconfig;
	pugi::xml_parse_result parseResult = configFile.load_file("config.xml");
	menuconfig = configFile.child("config").child("scenemenu").child("menu");

	fondoPath = menuconfig.child("fondo").attribute("texturePath").as_string();
	menuPath = menuconfig.child("menu").attribute("texturePath").as_string();
	normal_Path = menuconfig.child("normal").attribute("texturePath").as_string();
	focused_Path = menuconfig.child("focused").attribute("texturePath").as_string();
	pressed_Path = menuconfig.child("pressed").attribute("texturePath").as_string();


	fondotexture = app->tex->Load(fondoPath);
	menutexture = app->tex->Load(menuPath);
	normal_texture = app->tex->Load(normal_Path);
	focused_texture = app->tex->Load(focused_Path);
	pressed_texture = app->tex->Load(pressed_Path);

}

GuiControlButton::~GuiControlButton()
{}

bool GuiControlButton::Update(float dt)
{
	
	/*SDL_Rect rect1 = { 0,0,1920,1080 };
	app->render->DrawTexture(fondotexture, 0, 0, 0.7, SDL_FLIP_NONE, &rect1, 0, 0);*/
	
	buttonstate();
	if (newScena) {
		switch (id)
		{
		case 1:
			
			newgame = true;
			app->guiManager->Disable();
			app->scenemenu->Disable();
			app->SaveRequest();
			app->fade->FadeToBlack(app->scenemenu,app->scene,10);
			
			printf("play");
			break;

		case 2:
			newScena = false;
			printf("continue");

			app->guiManager->Disable();
			app->scenemenu->Disable();

			app->fade->FadeToBlack(app->scenemenu, app->scene, 10);
			app->scene->GetPlayerLife()->newmap = false;
			app->LoadRequest();
			app->scene->GetPlayerLife()->newmap = true;

			break;
		case 3:
			newScena = false;
			printf("setting");
			break;
		case 4:
			newScena = false;
			printf("credits");

			break;

		case 5:
			newScena = false;
			printf("exit");
			app->closeGame = false;
			break;
		}
	
	}

	

	return false;
}

void GuiControlButton::buttonstate()
{
	if (state != GuiControlState::DISABLED)
	{
		// L15: DONE 3: Update the state of the GUiButton according to the mouse position
		app->input->GetMousePosition(mouseX, mouseY);

		//If the position of the mouse if inside the bounds of the button 
		if (mouseX > bounds.x && mouseX < bounds.x + bounds.w && mouseY > bounds.y && mouseY < bounds.y + bounds.h) {

			state = GuiControlState::FOCUSED;

			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT) {
				state = GuiControlState::PRESSED;
			}

			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP) {
				state = GuiControlState::PRESSED_UP;
				NotifyObserver();
			}
		}
		else {
			state = GuiControlState::NORMAL;
		}


		//app->render->DrawText(text.GetString(), bounds.x, bounds.y, bounds.w, bounds.h);
		//L15: DONE 4: Draw the button according the GuiControl State
		switch (state)
		{
		case GuiControlState::DISABLED:
			newScena = true;
			app->render->DrawRectangle(bounds, 200, 200, 200, 255, true, false);
			break;
		case GuiControlState::NORMAL:
			rect = { 0,0,1920,1080 };
			app->render->DrawTexture(normal_texture, bounds.x / 2 - 390, bounds.y - 370, 0.7, SDL_FLIP_NONE, &rect, 0, 0);
			//printf("Normal");
			break;
		case GuiControlState::FOCUSED:
			app->render->DrawTexture(focused_texture, bounds.x / 2 - 390, bounds.y - 270, 0.7, SDL_FLIP_NONE, &rect, 0, 0);
			break;
		case GuiControlState::PRESSED:
			app->render->DrawTexture(pressed_texture, bounds.x / 2 - 390, bounds.y - 270, 0.7, SDL_FLIP_NONE, &rect, 0, 0);
			break;

		case GuiControlState::PRESSED_UP:
			newScena = true;
			app->render->DrawTexture(pressed_texture, bounds.x / 2 - 390, bounds.y - 270, 0.7, SDL_FLIP_NONE, &rect, 0, 0);
			break;
		
	}

		app->render->DrawText(text.GetString(), bounds.x, bounds.y, bounds.w / 2, bounds.h / 2);

	}
}

