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

	void getStateAnimation(EntityLifeBarState state);

	void resetAnimation(Animation& ani);

	void updateHeadAnimations();
	void updateMiddleAnimations();
	void updateTailAnimation();


	void OnCollision(PhysBody* physA, PhysBody* physB);
	void OnEndCollision(PhysBody* physA, PhysBody* physB);

public:

	bool isPicked = false;

	Animation* currentAnimation1 = nullptr;
	List<Animation*> currentAnimation2;
	Animation* currentAnimation3 = nullptr;
	
	//List<Animation> atack_2;

	Animation Head_treatment;
	Animation Head_takehit;
	Animation Head_die;
	Animation Head_idle;

	List<Animation>  Middle_treatment_wb;
	List<Animation>  Middle_treatment_nb;
	List<Animation>  Middle_treatment_ab;
	List<Animation>  Middle_takehit_wb;
	List<Animation>  Middle_takehit_nb;
	List<Animation>  Middle_takehit_ab;
	List<Animation>  Middle_die;
	List<Animation>  Middle_idle;
	List<Animation>  Middle_idle_nb;

	Animation Tail_treatment_nb;
	Animation Tail_treatment_ab;
	Animation Tail_takehit_nb;
	Animation Tail_takehit_ab;
	Animation Tail_die;
	Animation Tail_idle;
	Animation Tail_idle_nb;



	Animation inicializaAnimation;
	Animation SPosition;
	SDL_Rect* spritePositions;

	int TSprite;
	int SpriteX;
	int SpriteY;
	int PhotoWeight;
	float speed;

	bool isFacingLeft;


	int lifePos_X;

	int life = 10;
	bool playerTakeDmg = false;
	bool playerTakeDmg_Animation = false;
	int lifebar = life - 2;




private:

	SDL_Texture* lifebar_head_tail_texture;
	SDL_Texture* lifebar_mid_texture;


	const char* lifebar_head_tail_texture_Path;
	const char* lifebar_mid_texture_Path;


	SDL_Rect rect_1;
	List<SDL_Rect> rect_2;
	SDL_Rect rect_3;


	SDL_Texture* Pathfindingtexture;
	const char* PathfindingPath;
	PhysBody* pbody;
	PhysBody* pbody1;
};

#endif // __ITEM_H__#pragma once
