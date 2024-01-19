#pragma once
#ifndef __TELEPORT_H__
#define __TELEPORT_H__


#include "Entity.h"
#include "Point.h"
#include "Animation.h"
#include <cmath>
#include <tuple>
#include "SDL/include/SDL.h"
#include "Timer.h"

#include "List.h"

struct SDL_Texture;

class Teleport : public Entity
{
public:

	Teleport();
	virtual ~Teleport();

	bool Awake();

	bool Start();

	bool Update(float dt);

	bool CleanUp();

	void OnCollision(PhysBody* physA, PhysBody* physB);

	void reLoadXML();

public:

	Animation* currentAnimation = nullptr;

	Animation idle;
	Animation save;

	Animation SPosition;
	SDL_Rect* spritePositions;

	int TSprite;
	int SpriteX;
	int SpriteY;
	int PhotoWeight;
	int pos_X;
	int pos_Y;

	SDL_Rect rect;


private:

	SDL_Texture* TeleportTexture;
	const char* TeleportTexturePath;
	PhysBody* pbody;
};
#endif // __ITEM_H__#pragma once
