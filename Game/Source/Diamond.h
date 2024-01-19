#pragma once
#ifndef __DIAMOND_H__
#define __DIAMOND_H__


#include "Entity.h"
#include "Point.h"
#include "Animation.h"
#include <cmath>
#include <tuple>
#include "SDL/include/SDL.h"
#include "Timer.h"

#include "List.h"

struct SDL_Texture;

class Diamond : public Entity
{
public:

	Diamond();
	virtual ~Diamond();

	bool Awake();

	bool Start();

	bool Update(float dt);

	bool CleanUp();

	void DestroyDiamante();

	void OnCollision(PhysBody* physA, PhysBody* physB);

	void reLoadXML();

public:

	bool isPicked = false;
	Animation* currentAnimation = nullptr;

	Animation idle;

	
	Animation SPosition;
	SDL_Rect* spritePositions;

	int TSprite;
	int SpriteX;
	int SpriteY;
	int PhotoWeight;
	int pos_X;
	int pos_Y;

	bool victoria = false;
	bool lastDiamenteIsCreat = true;
	bool playerTakeDiamante = false;

	bool hecreado7diamante = false;

	bool GoCenterTime_determination;
	int playerGetDiamante = 0;

	SDL_Rect rect;
	

private:

	SDL_Texture* Diamondtexture;
	const char* DiamondPath;

	PhysBody* pbody;
};
#endif // __ITEM_H__