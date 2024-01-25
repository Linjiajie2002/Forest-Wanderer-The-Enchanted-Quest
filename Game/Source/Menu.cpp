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

Menu::Menu() : Module()
{
	name.Create("menu");
}

Menu::~Menu()
{}

// Called before render is available
bool Menu::Awake(pugi::xml_node& config)
{
	/*fondoPath = config.child("fondo").attribute("texturePath").as_string();

	menuPath = config.child("menu").attribute("texturePath").as_string();*/


	return true;
}

bool Menu::Start()
{
	//fondotexture = app->tex->Load(fondoPath);
	//menutexture = app->tex->Load(menuPath);
	return true;
}

bool Menu::Update(float dt)
{

	//rect = {0,0,1920,1080};
	//app->render->DrawTexture(fondotexture, 1, 0, 0.8, SDL_FLIP_NONE, &rect, 0, 0);

	//rect = { 0,0,1920,1080 };
	//app->render->DrawTexture(menutexture, -50, 30, 0.6, SDL_FLIP_NONE, &rect, 0, 0);



		
	return true;
}



bool Menu::CleanUp() {

	return true;
}

