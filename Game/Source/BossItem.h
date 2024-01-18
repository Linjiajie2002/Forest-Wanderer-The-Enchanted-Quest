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
	void CheckBallStarT(int tipo);
	iPoint randPosition();
	int randBall();

	void actualizarAnimacion();
	void OnCollision(PhysBody* physA, PhysBody* physB);
	void OnEndCollision(PhysBody* physA, PhysBody* physB);

	void reLoadXML();

public:

	bool isPicked = false;

	Animation* currentAnimation1 = nullptr;
	List<Animation*> currentAnimation2;
	Animation* currentAnimation3 = nullptr;
	Animation* currentAnimation4 = nullptr;

	Animation atack_1;
	List<Animation> atack_2;
	Animation atack_3;

	Animation ball_blue_start;
	Animation ball_blue_running;
	Animation ball_blue_end;

	Animation ball_red_start;
	Animation ball_red_running;
	Animation ball_red_end;

	Animation ball_yellow_start;
	Animation ball_yellow_running;
	Animation ball_yellow_end;

	Animation die;
	Animation take_hit;




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
	bool crearBoyd = false;
	bool playerTouchBall = false;
	bool oneTouch = false;
	

	int ballColor;

	float energyPos_X = 1920;
	float energyPos_Y = 780;

	iPoint ballPosition;
	int ballType;

	Timer deleteBall;
	Timer timeWait;

private:

	SDL_Texture* ball_blue_texture;
	SDL_Texture* boss_atack_2_texture;
	SDL_Texture* boss_atack_3_texture;
	SDL_Texture* boss_atack_4_texture;

	const char* ball_blue_texture_Path;
	const char* boss_atack_2_texture_Path;
	const char* boss_atack_3_texture_Path;
	const char* boss_atack_4_texture_Path;



	SDL_Rect rect_1;
	List<SDL_Rect> rect_2;
	SDL_Rect rect_3;
	SDL_Rect rect_4;


	SDL_Texture* Pathfindingtexture;
	const char* PathfindingPath;
	PhysBody* pbody;
	PhysBody* pbody1;
};

#endif // __ITEM_H__