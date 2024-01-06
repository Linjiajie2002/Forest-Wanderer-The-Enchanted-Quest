#include "ModuleFadeToBlack.h"


#include "SDL/include/SDL_render.h"
#include "App.h"
#include "Window.h"
#include "Textures.h"
#include "Map.h"

#include <iostream>

using namespace std;

ModuleFadeToBlack::ModuleFadeToBlack() : Module()
{

}

ModuleFadeToBlack::~ModuleFadeToBlack()
{}

// Called before render is available
bool ModuleFadeToBlack::Awake(pugi::xml_node& config)
{

	return true;
}

bool ModuleFadeToBlack::Start()
{
	return true;
}

bool ModuleFadeToBlack::Update(float dt)
{

	return true;
}



bool ModuleFadeToBlack::CleanUp() {

	return true;
}
void ModuleFadeToBlack::ResetMap()
{
	app->map->Disable();
	moduleToDisable->Disable();
	//moduleToEnable->Enable();
	app->entityManager->Disable();

	app->map->Enable();
	moduleToEnable->Enable();
	app->entityManager->Enable();
}
