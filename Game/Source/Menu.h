#pragma once
#pragma once
#ifndef __MENU_H__
#define __MENU_H__

#include "Module.h"
#include "Animation.h"
#include "SDL\include\SDL_rect.h"

struct SDL_Texture;

class Menu : public Module
{
public:
	//Constructor
	Menu(bool start_Enabled = true);

	//Destructor
	~Menu();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called before the first frame
	bool Start();

	// Called each loop iteration

	bool Update(float dt);


	// Called before quitting
	bool CleanUp();

public:
	SDL_Texture* fondotexture;
	const char* fondoPath;

	SDL_Texture* menutexture;
	const char* menuPath;
	SDL_Rect rect;

private:


};

#endif //__MODULEFADETOBLACK_H__