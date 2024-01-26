#include "ModuleFadeToBlack.h"


#include "SDL/include/SDL_render.h"
#include "App.h"
#include "Window.h"
#include "Textures.h"
#include "Map.h"
#include "Player.h"
#include "Scene.h"
#include "Menu.h"
#include "Render.h"

#include <iostream>

using namespace std;

Menu::Menu(bool start_Enabled) : Module(start_Enabled)
{
	name.Create("menu");
}

Menu::~Menu()
{}

// Called before render is available
bool Menu::Awake(pugi::xml_node& config)
{
	title_Path = config.child("title").attribute("texturePath").as_string();


	return true;
}

bool Menu::Start()
{
	title_texture = app->tex->Load(title_Path);
	return true;
}

bool Menu::Update(float dt)
{
	/*SDL_Rect btPos1 = { 0,0, 1920,1080 };
		
	app->render->DrawTexture(title_texture, -160, -30, 0.7, SDL_FLIP_NONE, &btPos1, 0, 0);

	app->render->DrawTexture(title_texture, -160, 130, 0.7, SDL_FLIP_NONE, &btPos1, 0, 0);*/

	return true;
}



bool Menu::CleanUp() {

	return true;
}

