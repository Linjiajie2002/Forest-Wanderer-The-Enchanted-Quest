#pragma once
#ifndef __BOSSITEM_H__
#define __BOSSITEM_H__

#include "Entity.h"
#include "Point.h"
#include "Animation.h"
#include "Timer.h"

#include"List.h"
#include <stdio.h>

struct SDL_Texture;



class BossItem : public Entity
{
public:

	BossItem();

	virtual ~BossItem();

	bool Awake();

	bool Start();

	bool Update(float dt);

	bool CleanUp();


	void randCreatEnergyBall(iPoint ballPosition);
	void randCreatCura(iPoint curaPosition);
	void CheckBallStarT(int tipo);
	iPoint randPosition();
	int randBall();
	void ball();
	void cura();

	void actualizarAnimacion();
	void OnCollision(PhysBody* physA, PhysBody* physB);
	void OnEndCollision(PhysBody* physA, PhysBody* physB);

	void reLoadXML();

public:

	bool isPicked = false;

	Animation* currentAnimation1 = nullptr;
	Animation* currentAnimation2 = nullptr;


	Animation ball_blue_start;
	Animation ball_blue_running;
	Animation ball_blue_end;

	Animation ball_red_start;
	Animation ball_red_running;
	Animation ball_red_end;

	Animation ball_yellow_start;
	Animation ball_yellow_running;
	Animation ball_yellow_end;

	
	Animation idle;
	Animation start;
	Animation die;


	Animation SPosition;
	SDL_Rect* spritePositions;

	int TSprite;
	int SpriteX;
	int SpriteY;
	int PhotoWeight;
	float speed;

	bool isFacingLeft;

	bool crearBall = false;
	bool firstBall = true;
	bool crearBallrd = false;
	bool playerTouchBall = false;
	bool oneTouch = false;
	

	int ballColor;

	bool crearCura = false;
	bool crearCurard = false;
	bool playerTouchCura = false;
	bool oneTouch_cura = false;
	bool playerTakeCura = false;
	bool playerGetPoint = true;

	float energyPos_X = 1920;
	float energyPos_Y = 780;

	iPoint ballPosition;
	iPoint curaPosition;
	int ballType;

	Timer deleteBall;
	Timer deleteCura;
	Timer timeWait;
	Timer curatimeWait;

private:

	SDL_Texture* ball_blue_texture;
	SDL_Texture* cura_texture;


	const char* ball_blue_texture_Path;
	const char* cura_texture_Path;



	SDL_Rect rect_1;
	SDL_Rect rect_2;

	PhysBody* pbody;
	PhysBody* pbody1;
};

#endif // __ITEM_H__