#include "ModuleFadeToBlack.h"


#include "SDL/include/SDL_render.h"
#include "App.h"
#include "Window.h"
#include "Textures.h"
#include "Map.h"
#include "Player.h"
#include "Scene.h"
#include "Menu.h"

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
	printf("%s",config.name());
	fondoPath = config.child("fondo").attribute("texturePath").as_string();


	return true;
}

bool Menu::Start()
{
	fondotexture = app->tex->Load(fondoPath);
	return true;
}

bool Menu::Update(float dt)
{

		
	return true;
}



bool Menu::CleanUp() {

	return true;
}

