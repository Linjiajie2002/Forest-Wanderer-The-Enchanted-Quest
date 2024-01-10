#pragma once
#ifndef __BOSS_H__
#define __BOSS_H__

#include "Entity.h"
#include "Point.h"
#include "Animation.h"
#include "Timer.h"

#include"List.h"

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

	void boss_atack_1(int playerPosX);
	void boss_atack_2(bool inversaAtack, int numberAtack);
	void boss_atack_3(bool inversaAtack);


	void OnCollision(PhysBody* physA, PhysBody* physB);
	void OnEndCollision(PhysBody* physA, PhysBody* physB);

public:

	bool isPicked = false;

	Animation* currentAnimation1 = nullptr;
	List<Animation*> currentAnimation2 ;
	Animation* currentAnimation3 = nullptr;

	Animation atack_1;
	List<Animation> atack_2;
	Animation atack_3;
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

	int attackMethod = 1 ;

	//Atack 1
	bool getPlayerPosition = false;
	int player_x;
	Timer atack1_Getposition;

	//Atack 2
	Timer atack2_generAtack;
	int numeroAtack = 4;
	int maxNumAtack = 0;
	bool allPrint = false;
	int distancia = 0;

	//Atack3
	bool direction_Atack = false;


	Player* player;

	int deadenemy;

	bool inBossBattle = false;
	bool tpToinBossBattle = false;



private:

	SDL_Texture* boss_atack_1_texture;
	SDL_Texture* boss_atack_2_texture;
	SDL_Texture* boss_atack_3_texture;

	const char* boss_atack_1_texture_Path;
	const char* boss_atack_2_texture_Path;
	const char* boss_atack_3_texture_Path;

	SDL_Rect rect_1;
	List<SDL_Rect> rect_2;
	SDL_Rect rect_3;


	SDL_Texture* Pathfindingtexture;
	const char* PathfindingPath;
	PhysBody* pbody;
	PhysBody* pbody1;
};

#endif // __ITEM_H__