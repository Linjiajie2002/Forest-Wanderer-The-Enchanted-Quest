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

	void GetPoint(int color);
	void CheckPoint();
	void OnCollision(PhysBody* physA, PhysBody* physB);
	void OnEndCollision(PhysBody* physA, PhysBody* physB);

	void reLoadXML();

public:

	bool isPicked = false;

	Animation* currentAnimation1 = nullptr;
	Animation* currentAnimation2 = nullptr;
	Animation* currentAnimation3 = nullptr;
	List<Animation*> currentAnimation4;
	List<Animation*> currentAnimation5;
	List<Animation*> currentAnimation6;
	Animation* currentAnimation7 = nullptr;

	Animation angel_blue_start;
	Animation angel_blue_idle;
	Animation angel_blue_die;


	Animation angel_red_start;
	Animation angel_red_idle;
	Animation angel_red_die;

	Animation angel_yellow_start;
	Animation angel_yellow_idle;
	Animation angel_yellow_die;



	List<Animation> angel_borde_red_idle;
	List<Animation> angel_borde_yellow_idle;
	List<Animation> angel_borde_blue_idle;



	Animation SPosition;
	SDL_Rect* spritePositions;

	int TSprite;
	int SpriteX;
	int SpriteY;
	int PhotoWeight;
	float speed;
	int ballColor;
	bool isFacingLeft;
	bool getPoint = false;
	bool angleFinish = false;
	int attackMethod = 1;

	bool bluebar = false;
	int countBar = 0;
	Animation inicializaAnimation;
	

	bool Enter = false;
	bool deleteAngel = false;

	int blueball = 0;
	int redball = 0;
	int yelloweball = 0;


private:

	SDL_Texture* angel_blue_texture;
	SDL_Texture* angel_red_texture;
	SDL_Texture* angel_yellow_texture;

	SDL_Texture* angel_borde_blue_texture;
	SDL_Texture* angel_borde_red_texture;
	SDL_Texture* angel_borde_yellow_texture;

	const char* angel_blue_texture_Path;
	const char* angel_red_texture_Path;
	const char* angel_yellow_texture_Path;

	const char* angel_borde_blue_texture_Path;
	const char* angel_borde_red_texture_Path;
	const char* angel_borde_yellow_texture_Path;



	SDL_Rect rect_1;
	SDL_Rect rect_2;
	SDL_Rect rect_3;
	List<SDL_Rect> rect_4;
	List<SDL_Rect> rect_5;
	List<SDL_Rect> rect_6;

	SDL_Texture* Pathfindingtexture;
	const char* PathfindingPath;
	PhysBody* pbody;
	PhysBody* pbody1;
};

#endif // __ITEM_H__