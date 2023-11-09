#pragma once
#ifndef __SHOP_H__
#define __SHOP_H__

#include "Entity.h"
#include "Point.h"
#include "Animation.h"


struct SDL_Texture;

class Shop : public Entity
{
public:

	Shop();

	virtual ~Shop();

	bool Awake();

	bool Start();

	bool Update(float dt);

	bool CleanUp();

public:

	bool isPicked = false;

	Animation* currentAnimation = nullptr;
	Animation idle;
	Animation openBox;
	Animation closeBox;
	Animation SPosition;
	SDL_Rect* spritePositions;

	int TSprite;
	int SpriteX;
	int SpriteY;
	int PhotoWeight;

private:

	SDL_Texture* Shoptexture;
	const char* ShopPath;
	PhysBody* pbody;
};

#endif // __ITEM_H__