#include "ModuleFadeToBlack.h"


#include "SDL/include/SDL_render.h"
#include "App.h"
#include "Window.h"
#include "Textures.h"
#include "Map.h"
#include "Player.h"
#include "Scene.h"

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

    if (currentStep == Fade_Step::NONE) return true;

    if (currentStep == Fade_Step::TO_BLACK)
    {
        ++frameCount;
        if (frameCount >= maxFadeFrames)
        {

			app->entityManager->Disable();
            app->map->Disable();
			moduleToDisable->Disable();
			app->entityManager->CleanUp();

			pugi::xml_document configFile;
			pugi::xml_node SceneInfo;
			pugi::xml_parse_result parseResult = configFile.load_file("config.xml");
			SceneInfo = configFile.child("config").child("scene");

			app->map->Enable();
            moduleToEnable->Enable();
			moduleToEnable->Awake(SceneInfo);
			app->entityManager->Enable();
			

            currentStep = Fade_Step::FROM_BLACK;
        }
    }
    else
    {
        --frameCount;
        if (frameCount <= 0)
        {
            currentStep = Fade_Step::NONE;
        }
    }
	return true;
}



bool ModuleFadeToBlack::CleanUp() {


	return true;
}
void ModuleFadeToBlack::ResetMap()
{
	app->map->Disable();
	moduleToDisable->Disable();
	app->entityManager->Disable();

	app->map->Enable();
	moduleToEnable->Enable();
	app->entityManager->Enable();
}

bool ModuleFadeToBlack::FadeToBlack(Module* toDisable, Module* toEnable, float frames)
{
	bool ret = false;

	if (currentStep == Fade_Step::NONE)
	{
		
		currentStep = Fade_Step::TO_BLACK;
		frameCount = 0;
		maxFadeFrames = frames;

		this->moduleToDisable = toDisable;
		this->moduleToEnable = toEnable;

		ret = true;
	}

	return ret;
	
	
	
	
}
