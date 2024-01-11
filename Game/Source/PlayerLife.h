#pragma once
#pragma once
#ifndef __PLAYERLIFE_H__
#define __PLAYERLIFE__

#include "Entity.h"
#include "Point.h"
#include "Animation.h"
#include "Timer.h"

#include"List.h"
#include <stdio.h>

struct SDL_Texture;



class PlayerLife : public Entity
{
public:

	PlayerLife();

	virtual ~PlayerLife();

	bool Awake();

	bool Start();

	bool Update(float dt);

	bool CleanUp();


	void OnCollision(PhysBody* physA, PhysBody* physB);
	void OnEndCollision(PhysBody* physA, PhysBody* physB);

public:

	bool isPicked = false;

	Animation* currentAnimation1 = nullptr;
	List<Animation*> currentAnimation2;
	Animation* currentAnimation3 = nullptr;
	Animation* currentAnimation4 = nullptr;

	Animation fin_die;
	
	
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

	SDL_Texture* lifebar_fin_die_texture;
	SDL_Texture* boss_atack_2_texture;
	SDL_Texture* boss_atack_3_texture;
	SDL_Texture* boss_atack_4_texture;

	const char* lifebar_fin_die_texture_Path;
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

#endif // __ITEM_H__#pragma once
