#include "GuiControlButton.h"
#include "Render.h"
#include "App.h"
#include "Audio.h"
#include "Textures.h"

GuiControlButton::GuiControlButton(uint32 id, SDL_Rect bounds, const char* text) : GuiControl(GuiControlType::BUTTON, id)
{
	this->bounds = bounds;
	this->text = text;

	canClick = true;
	drawBasic = false;
	pugi::xml_document configFile;
	pugi::xml_node menuconfig;
	pugi::xml_parse_result parseResult = configFile.load_file("config.xml");
	menuconfig = configFile.child("config").child("menu");

	fondoPath = menuconfig.child("fondo").attribute("texturePath").as_string();

	menuPath = menuconfig.child("menu").attribute("texturePath").as_string();

	fondotexture = app->tex->Load(fondoPath);
	menutexture = app->tex->Load(menuPath);
}

GuiControlButton::~GuiControlButton()
{
	
}



bool GuiControlButton::Update(float dt)
{

	rect = { 0,0,1920,1080 };
	app->render->DrawTexture(fondotexture, 1, 0, 0.8, SDL_FLIP_NONE, &rect, 0, 0);

	


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
				NotifyObserver();
			}
		}
		else {
			state = GuiControlState::NORMAL;
		}




		//L15: DONE 4: Draw the button according the GuiControl State
		switch (state)
		{
		case GuiControlState::DISABLED:
			app->render->DrawRectangle(bounds, 200, 200, 200, 255, true, false);
			break;
		case GuiControlState::NORMAL:
			app->render->DrawRectangle(bounds, 0, 0, 255, 255, true, false);
			rect = { 0,0,1920,1080 };
			app->render->DrawTexture(menutexture, -50, 30, 0.6, SDL_FLIP_NONE, &rect, 0, 0);
			//printf("Normal");
			break;
		case GuiControlState::FOCUSED:
			app->render->DrawRectangle(bounds, 0, 0, 20, 255, true, false);
			//printf("focuse");
			break;
		case GuiControlState::PRESSED:
			app->render->DrawRectangle(bounds, 0, 255, 0, 255, true, false);
			//printf("PRESSED");
			break;
		}

		app->render->DrawText(text.GetString(), bounds.x, bounds.y, bounds.w, bounds.h);




	}

	return false;
}

