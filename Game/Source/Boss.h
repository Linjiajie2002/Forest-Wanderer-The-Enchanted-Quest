#pragma once
#ifndef __BOSS_H__
#define __BOSS_H__

#include "Entity.h"
#include "Point.h"
#include "Animation.h"


struct SDL_Texture;

class Boss : public Entity
{
public:

	Boss();

	virtual ~Boss();

	bool Awake();

	bool Start();

	bool Update(float dt);

	bool CleanUp();

	void OnCollision(PhysBody* physA, PhysBody* physB);
	void OnEndCollision(PhysBody* physA, PhysBody* physB);

public:

	bool isPicked = false;

	Animation* currentAnimation1 = nullptr;
	Animation* currentAnimation2 = nullptr;

	Animation atack_1;
	Animation atack_2;
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

	int lastY;
	int lastX;


	int walkFrameCount = 0;
	bool rddirection;
	int enemywalk;
	bool enemyidle = true;
	int timeidle;
	bool rdinWork = false;
	bool walkrdinWork = true;
	int enemyAreaLimitR, enemyAreaLimitL;

	float rangeSize = 700.0f;
	float leftTopX;
	float leftTopY;
	float rightBottomX;
	float rightBottomY;


	float atk_rangeSize = 20.0f;
	float atk_leftTopX;
	float atk_leftTopY;
	float atk_rightBottomX;
	float atk_rightBottomY;

	Player* player;

	int deadenemy;





private:

	SDL_Texture* boss_atack_1_texture;
	SDL_Texture* boss_atack_2_texture;
	SDL_Texture* boss_atack_3_texture;

	const char* boss_atack_1_texture_Path;
	const char* boss_atack_2_texture_Path;
	const char* boss_atack_3_texture_Path;

	SDL_Texture* Pathfindingtexture;
	const char* PathfindingPath;
	PhysBody* pbody;
	PhysBody* pbody1;
};

#endif // __ITEM_H__