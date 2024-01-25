#ifndef __GUICONTROLBUTTON_H__
#define __GUICONTROLBUTTON_H__

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"

class GuiControlButton : public GuiControl
{

public:

	GuiControlButton(uint32 id, SDL_Rect bounds, const char* text);
	virtual ~GuiControlButton();
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	bool Update(float dt);


public:

	SDL_Texture* fondotexture;
	const char* fondoPath;

	SDL_Texture* menutexture;
	const char* menuPath;

	SDL_Rect rect;

private:

	int mouseX, mouseY;
	unsigned int click;

	bool canClick = true;
	bool drawBasic = false;
};

#endif // __GUICONTROLBUTTON_H__