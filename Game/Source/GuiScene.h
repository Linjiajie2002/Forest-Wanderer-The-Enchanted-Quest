#ifndef __GUISCENE_H__
#define __GUISCENE_H__

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"

class GuiScene : public GuiControl
{

public:

	GuiScene(uint32 id, SDL_Rect bounds, const char* text);
	virtual ~GuiScene();

	// Called each loop iteration
	bool Update(float dt);


public:

	SDL_Texture* fondotexture;
	const char* fondoPath;

	SDL_Texture* menutexture;
	const char* menuPath;

	SDL_Texture* normal_texture;
	const char* normal_Path;

	SDL_Texture* focused_texture;
	const char* focused_Path;

	SDL_Texture* pressed_texture;
	const char* pressed_Path;
	SDL_Rect rect;


	bool newScena = false;

private:

	int mouseX, mouseY;
	unsigned int click;

	bool canClick = true;
	bool drawBasic = false;
};

#endif // __GUICONTROLBUTTON_H__#pragma once
