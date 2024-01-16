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
	void boss_atack_4(bool inversaAtack);
	void goBossBattle();

	void OnCollision(PhysBody* physA, PhysBody* physB);
	void OnEndCollision(PhysBody* physA, PhysBody* physB);

	void reLoadXML(pugi::xml_node& parameters);

public:

	bool isPicked = false;

	Animation* currentAnimation1 = nullptr;
	List<Animation*> currentAnimation2 ;
	Animation* currentAnimation3 = nullptr;
	Animation* currentAnimation4 = nullptr;

	Animation atack_1;
	List<Animation> atack_2;
	Animation atack_3;
	
	Animation atack_4_start;
	Animation atack_4_running;
	Animation atack_4_end;

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
	Animation inicializaAnimation;
	int numeroAtack = 4;
	int maxNumAtack = 0;
	bool allPrint = false;
	int distancia = 0;

	int aumentaDistanciaColison = 0;
	int aumentaDistanciaColison_suport = 0;
	//Atack3
	bool direction_Atack = false;

	//Atack4
	float velocitat = 0;

	float atack4_posX;
	int atack4_posX_R= 1420;

	int atack4_posX_L = 2290;
	int atack4_posY;

	bool goFight = false;
	int atack2_posY;

	Player* player;

	int deadenemy;

	bool inBossBattle = false;
	bool tpToinBossBattle = false;

	bool crearCollision = false;

	Timer atack1_Collision;
	
	List<Timer> atack2_Collision;

	bool atackTouch = false;

	struct PhysBodyWithTimer {
		PhysBody* pbody2;
		Timer timer;

		// Constructor para facilitar la creaci¨®n
		PhysBodyWithTimer(PhysBody* pb) : pbody2(pb) {}
	};

	std::vector<PhysBodyWithTimer> physBodiesWithTimers;
private:

	SDL_Texture* boss_atack_1_texture;
	SDL_Texture* boss_atack_2_texture;
	SDL_Texture* boss_atack_3_texture;
	SDL_Texture* boss_atack_4_texture;

	const char* boss_atack_1_texture_Path;
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
	PhysBody* pbody2;
	std::vector<PhysBody*> physBodies;
};

#endif // __ITEM_H__