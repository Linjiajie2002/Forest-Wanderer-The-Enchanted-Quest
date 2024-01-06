#pragma once
#ifndef __MODULEFADETOBLACK_H__
#define __MODULEFADETOBLACK_H__

#include "Module.h"
#include "Animation.h"
#include "SDL\include\SDL_rect.h"

struct SDL_Texture;

class ModuleFadeToBlack : public Module
{
public:
	//Constructor
	ModuleFadeToBlack();

	//Destructor
	~ModuleFadeToBlack();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	
	bool Update(float dt);
	

	// Called before quitting
	bool CleanUp();


	void ResetMap();
	// Called from another module
	// Starts the fade process which has two steps, fade_out and fade_in
	// After the first step, the modules should be switched
	//bool FadeToBlack(Module* toDisable, Module* toEnable, float frames = 60);

private:

	enum Fade_Step
	{
		NONE,
		TO_BLACK,
		FROM_BLACK
	} currentStep = Fade_Step::NONE;

	// A frame count system to handle the fade time and ratio
	Uint32 frameCount = 0;
	Uint32 maxFadeFrames = 0;

	// The rectangle of the screen, used to render the black rectangle
	SDL_Rect screenRect;

	// The modules that should be switched after the first step
	Module* moduleToEnable = nullptr;
	Module* moduleToDisable = nullptr;


	SDL_Texture* fadeInOut_texture;
	Animation fadeIn;
	Animation fadeOut;
	Animation* currentAnimation = nullptr;

};

#endif //__MODULEFADETOBLACK_H__