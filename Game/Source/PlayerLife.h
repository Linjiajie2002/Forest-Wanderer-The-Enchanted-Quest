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
	Animation* currentAnimation2 = nullptr;;


	Animation Head_treatment;
	Animation Head_takehit;
	Animation Head_die;
	Animation Head_idle;

	Animation Middle_treatment_wb;
	Animation Middle_treatment_nb;
	Animation Middle_treatment_ab;
	Animation Middle_takehit_wb;
	Animation Middle_takehit_nb;
	Animation Middle_takehit_ab;
	Animation Middle_die;
	Animation Middle_idle;

	Animation Tail_treatment_nb;
	Animation Tail_treatment_ab;
	Animation Tail_takehit_nb;
	Animation Tail_takehit_ab;
	Animation Tail_die;
	Animation Tail_idle;




	Animation SPosition;
	SDL_Rect* spritePositions;

	int TSprite;
	int SpriteX;
	int SpriteY;
	int PhotoWeight;
	float speed;

	bool isFacingLeft;

	int lifePos_X;



private:

	SDL_Texture* lifebar_head_tail_texture;
	SDL_Texture* lifebar_mid_texture;


	const char* lifebar_head_tail_texture_Path;
	const char* lifebar_mid_texture_Path;


	SDL_Rect rect_1;
	SDL_Rect rect_2;


	SDL_Texture* Pathfindingtexture;
	const char* PathfindingPath;
	PhysBody* pbody;
	PhysBody* pbody1;
};

#endif // __ITEM_H__#pragma once
