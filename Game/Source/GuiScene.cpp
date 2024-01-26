#include "GuiControlButton.h"
#include "Render.h"
#include "App.h"
#include "Audio.h"
#include "Textures.h"
#include "Scene.h"
#include "GuiScene.h"

GuiScene::GuiScene(uint32 id, SDL_Rect bounds, const char* text) : GuiControl(GuiControlType::BUTTON, id)
{

}

GuiScene::~GuiScene()
{

}



bool GuiScene::Update(float dt)
{
	
	return false;
}

