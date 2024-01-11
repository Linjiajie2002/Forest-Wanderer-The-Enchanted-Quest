#pragma once
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

	void calculateNURBS(iPoint p1, iPoint p2, iPoint p3, double t, iPoint* result);


	void OnCollision(PhysBody* physA, PhysBody* physB);
	void OnEndCollision(PhysBody* physA, PhysBody* physB);

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

	int attackMethod = 1;

	//Atack 1
	bool getPlayerPosition = false;
	int player_x;
	Timer atack1_Getposition;

	//Atack 2
	Timer atack2_generAtack;
	Animation inicializaAnimation;
	int numeroAtack = 4;
	int maxNumAtack = 0;
	bool allPrint = false;
	int distancia = 0;

	//Atack3
	bool direction_Atack = false;

	//Atack4
	float velocitat = 0;

	float atack4_posX;
	int atack4_posX_R = 1420;

	int atack4_posX_L = 2290;
	int atack4_posY;


	int deadenemy;

	bool inBossBattle = false;
	bool tpToinBossBattle = false;


	double result_x = 0.00;
	double result_y = 0.00;


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