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

	void Camera();
	void LoadPersonB();
	void ShakeCamera(int xOffset, int yOffset);

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
	Animation atackarrow;
	Animation idle3;
	Animation die;
	Animation lowjump;

	Animation arrowAtack1;
	Animation arrowAtack2;
	
	SDL_Rect* spritePositions;


public:
	float speed;
	float crouchspeed;
	float jumpForce;
	
	const char* texturePath;
	const char* texturePath2;
	SDL_Texture* texture = NULL;
	PhysBody* pbody;
	int pickCoinFxId;

	Render* render = NULL;

	bool isFacingLeft = false;
	bool isHighJumping = false;

	uint width;
	uint height;

	//Jump
	bool canJump = true;
	bool playerOnPlatform = true;
	int jumpCount = 0;
	bool isDead = false;
	bool AniplayerOnPlatform = false;

	bool starFram = false;
	
	//Atack
	int atackTypeCount = 0;
	bool isAtack = false;
	bool isAtackarrow = false;
	bool canAtack = true;
	uint64 frameCount = 0;


	//climb
	bool onWall =false;

	bool MoveCamere = false;

	int TSprite;
	int SpriteX;
	int SpriteY;
	int PhotoWeight;
	
	int cameraUP;

	//Shake
	int shakeDuration = 0; 
	int shakeMagnitude = 5;

	bool shake = false;

	int xOffset = (rand() % (2 * shakeMagnitude + 1)) - shakeMagnitude;
	int yOffset = (rand() % (2 * shakeMagnitude + 1)) - shakeMagnitude;

	int originalX = 0;
	int originalY = 0;

	bool changePeson = false;
	bool isAir = false;

};

#endif // __PLAYER_H__