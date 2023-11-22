#pragma once
#ifndef __ENEMY_GOBLIN_H__
#define __ENEMY_GOBLIN_H__

#include "Entity.h"
#include "Point.h"
#include "Animation.h"


struct SDL_Texture;

class Enemy_Goblin : public Entity
{
public:

	Enemy_Goblin();

	virtual ~Enemy_Goblin();

	bool Awake();

	bool Start();

	bool Update(float dt);

	bool CleanUp();

public:

	bool isPicked = false;

	Animation* currentAnimation = nullptr;

	Animation idle;
	Animation atack;
	Animation die;
	Animation take_hit;
	Animation run;

	Animation SPosition;
	SDL_Rect* spritePositions;

	int TSprite;
	int SpriteX;
	int SpriteY;
	int PhotoWeight;

private:

	SDL_Texture* Enemytexture;
	const char* EnemyPath;
	PhysBody* pbody;
};

#endif // __ITEM_H__