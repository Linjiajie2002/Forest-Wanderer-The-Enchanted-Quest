#pragma once
#ifndef __ENEMY_FLYEYE_H__
#define __ENEMY_FLYEYE_H__

#include "Entity.h"
#include "Point.h"
#include "Animation.h"


struct SDL_Texture;

class Enemy_Flyeye : public Entity
{
public:

	Enemy_Flyeye();

	virtual ~Enemy_Flyeye();

	bool Awake();

	bool Start();

	bool Update(float dt);

	bool CleanUp();

	void OnCollision(PhysBody* physA, PhysBody* physB);
	void OnEndCollision(PhysBody* physA, PhysBody* physB);


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
	float speed;

	int countFrame = 0;
	bool isFacingLeft;

	bool inEenemyArea = true;

	bool touchR = false;
	bool touchL = false;

	int life = 3;
	bool isDead = false;
	bool isTakehit = false;
	bool AtackPlayer = false;
	Timer attackTimer;
	Timer timerAtaque;
	bool canatake = false;
	PhysBody* attackParticle;

	int enemyAreaLimitR;
	int enemyAreaLimitL;

	int lastY;
	int lastX;


private:

	SDL_Texture* Enemytexture;
	SDL_Texture* Pathfindingtexture;
	const char* EnemyPath;
	const char* PathfindingPath;
	PhysBody* pbody;
	PhysBody* pbody1;
};

#endif // __ITEM_H__