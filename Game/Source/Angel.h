#pragma once
#ifndef __ANGEL_H__
#define __ANGEL_H__

#include "Entity.h"
#include "Point.h"
#include "Animation.h"
#include "Timer.h"

#include"List.h"

struct SDL_Texture;

class Angel : public Entity
{
public:

	Angel();

	virtual ~Angel();

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
	Animation* currentAnimation3 = nullptr;
	Animation* currentAnimation4 = nullptr;

	Animation angel_blue_start;
	Animation angel_blue_idle;
	Animation angel_blue_die;


	Animation angel_red_start;
	Animation angel_red_idle;
	Animation angel_red_die;

	Animation angel_yellow_start;
	Animation angel_yellow_idle;
	Animation angel_yellow_die;



	Animation angel_blue_bar;

	




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

	bool Enter = false;
	bool deleteAngel = false;


private:

	SDL_Texture* angel_blue_texture;
	SDL_Texture* angel_red_texture;
	SDL_Texture* angel_yellow_texture;
	SDL_Texture* boss_atack_4_texture;

	const char* angel_blue_texture_Path;
	const char* angel_red_texture_Path;
	const char* angel_yellow_texture_Path;
	const char* boss_atack_4_texture_Path;



	SDL_Rect rect_1;
	SDL_Rect rect_2;
	SDL_Rect rect_3;
	SDL_Rect rect_4;


	SDL_Texture* Pathfindingtexture;
	const char* PathfindingPath;
	PhysBody* pbody;
	PhysBody* pbody1;
};

#endif // __ITEM_H__