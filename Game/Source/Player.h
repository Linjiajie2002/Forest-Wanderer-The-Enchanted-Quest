#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Point.h"
#include "Animation.h"
#include "SDL/include/SDL.h"

struct SDL_Texture;

class Player : public Entity
{
public:

	Player();
	
	virtual ~Player();

	bool Awake();

	bool Start();

	bool Update(float dt);

	bool CleanUp();

	void OnCollision(PhysBody* physA, PhysBody* physB);


	Animation* currentAnimation = nullptr;

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




public:
	float speed = 0.2f;
	const char* texturePath;
	SDL_Texture* texture = NULL;
	PhysBody* pbody;
	int pickCoinFxId;

	float jumpForce = 5;
	bool isFacingLeft = false;
};

#endif // __PLAYER_H__