#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Point.h"
#include "Animation.h"
#include "SDL/include/SDL.h"
#include "Physics.h"
#include "Render.h"

struct SDL_Texture;

class Player : public Entity
{
public:

	Player();
	
	virtual ~Player();

	bool Awake();

	bool Start();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	void OnCollision(PhysBody* physA, PhysBody* physB);


	Animation* currentAnimation = nullptr;

	Animation SPosition;
	Animation idle;
	Animation crouch;
	Animation run;
	Animation highjump;
	Animation slide;
	Animation idle2;
	Animation atack;
	Animation atack2;
	Animation atack3;
	Animation idle3;
	Animation die;
	Animation lowjump;
	
	SDL_Rect* spritePositions;


public:
	float speed = 0.2f;
	float crouchspeed = 0.1f;
	const char* texturePath;
	SDL_Texture* texture = NULL;
	PhysBody* pbody;
	int pickCoinFxId;

	Render* render = NULL;

	float jumpForce = 25;
	bool isFacingLeft = false;
	bool isHighJumping = false;

	uint width;
	uint height;
};

#endif // __PLAYER_H__