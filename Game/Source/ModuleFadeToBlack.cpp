#include "ModuleFadeToBlack.h"


#include "SDL/include/SDL_render.h"
#include "App.h"
#include "Window.h"
#include "Textures.h"

#include <iostream>

using namespace std;

ModuleFadeToBlack::ModuleFadeToBlack() : Module()
{
	//screenRect = { 0, 0,(int)app->win->GetScale(),(int)app->win->GetScale() };
	////app->win->GetScale()


	//fadeIn.PushBack({ 0, 0, 320, 242 });
	//fadeIn.PushBack({ 0,	242, 320, 242 });
	//fadeIn.PushBack({ 0, 484, 320, 242 });
	//fadeIn.PushBack({ 0, 726, 320, 242 });
	//fadeIn.PushBack({ 0, 726, 320, 242 });
	//fadeIn.speed = 0.3f;
	//fadeIn.loop = false;

	//fadeOut.PushBack({ 0, 726, 320, 242 });
	//fadeOut.PushBack({ 0, 484, 320, 242 });
	//fadeOut.PushBack({ 0,242, 320, 242 });
	//fadeOut.PushBack({ 0, 0, 320, 242 });
	//fadeOut.PushBack({ 0, 0, 0, 0 });
	//fadeOut.speed = 0.3f;
	//fadeOut.loop = false;



}

ModuleFadeToBlack::~ModuleFadeToBlack()
{}

// Called before render is available
bool ModuleFadeToBlack::Awake(pugi::xml_node& config)
{
	
	bool ret = true;

	//Uint32 flags = SDL_RENDERER_ACCELERATED;

	//if (config.child("vsync").attribute("value").as_bool(true) == true)
	//{
	//	flags |= SDL_RENDERER_PRESENTVSYNC;
	//	//LOG("Using vsync");
	//}

	//renderer = SDL_CreateRenderer(app->win->window, -1, flags);

	//if (renderer == NULL)
	//{
	//	//LOG("Could not create the renderer! SDL_Error: %s\n", SDL_GetError());
	//	ret = false;
	//}
	//else
	//{
	//	camera.w = app->win->screenSurface->w;
	//	camera.h = app->win->screenSurface->h;
	//	camera.x = 0;
	//	app->render->camera.y = -701;
	//}

	return ret;
}

bool ModuleFadeToBlack::Start()
{
	//LOG("Preparing Fade Screen");

	//fadeInOut_texture = app->tex->Load("Assets/Interface/Menu/fade.png");
	//

	//// Enable blending mode for transparency
	//SDL_SetRenderDrawBlendMode(app->render->renderer, SDL_BLENDMODE_BLEND);
	return true;
}

bool ModuleFadeToBlack::Update(float dt)
{

	//// Exit this function if we are not performing a fade
	//if (currentStep == Fade_Step::NONE) return true;

	//if (currentStep == Fade_Step::TO_BLACK)
	//{
	//	fadeOut.Reset();
	//	currentAnimation = &fadeIn;
	//	++frameCount;
	//	if (frameCount >= maxFadeFrames)
	//	{
	//		// TODO 1: Enable / disable the modules received when FadeToBlacks() gets called
	//		moduleToDisable->Disable();
	//		moduleToEnable->Enable();

	//		currentStep = Fade_Step::FROM_BLACK;
	//	}
	//}
	//else
	//{
	//	fadeIn.Reset();
	//	currentAnimation = &fadeOut;
	//	--frameCount;
	//	if (frameCount <= 0)
	//	{
	//		currentStep = Fade_Step::NONE;
	//	}
	//}



	//currentAnimation->Update();

	return true;
}


//bool ModuleFadeToBlack::PostUpdate()
//{
//
//
//	//// Exit this function if we are not performing a fade
//	//if (currentStep == Fade_Step::NONE) return true;
//
//	//float fadeRatio = (float)frameCount / (float)maxFadeFrames;
//
//
//
//	//// Render the black square with alpha on the screen
//	//SDL_SetRenderDrawColor(app->render->renderer, 0, 0, 0, (Uint8)(fadeRatio * 255.0f));
//	//SDL_RenderFillRect(app->render->renderer, &screenRect);
//
//	//SDL_Rect rect = currentAnimation->GetCurrentFrame();
//
//
//	//if (currentStep == Fade_Step::TO_BLACK) {
//
//	//	app->render->DrawTexture(fadeInOut_texture, app->render->camera.x / app->win->GetScale() - 320, 0, SDL_FLIP_NONE, &rect);
//	//	app->render->DrawTexture(fadeInOut_texture, app->render->camera.x / app->win->GetScale(), 0, SDL_FLIP_NONE, &rect);
//	//	app->render->DrawTexture(fadeInOut_texture, app->render->camera.x / app->win->GetScale() + 320, 0, SDL_FLIP_NONE, &rect);
//	//	
//	//}
//	//else {
//
//	//	app->render->DrawTexture(fadeInOut_texture, app->render->camera.x / app->win->GetScale() - 320, 0, SDL_FLIP_NONE, &rect);
//	//	app->render->DrawTexture(fadeInOut_texture, app->render->camera.x / app->win->GetScale(), 0, SDL_FLIP_NONE, &rect);
//	//	app->render->DrawTexture(fadeInOut_texture, app->render->camera.x / app->win->GetScale() + 320, 0, SDL_FLIP_NONE, &rect);
//	//}
//
//
//	return true;
//}


bool ModuleFadeToBlack::CleanUp() {

	return true;
}
bool ModuleFadeToBlack::FadeToBlack(Module* moduleToDisable, Module* moduleToEnable, float frames)
{
	bool ret = false;

	//// If we are already in a fade process, ignore this call
	//if (currentStep == Fade_Step::NONE)
	//{
	//	currentStep = Fade_Step::TO_BLACK;
	//	frameCount = 0;
	//	maxFadeFrames = frames;

	//	// TODO 1: We need to keep track of the modules received in FadeToBlack(...)
	//	this->moduleToDisable = moduleToDisable;
	//	this->moduleToEnable = moduleToEnable;
	//	//App->activeModule = moduleToEnable;

	//	ret = true;
	//}

	return ret;
}