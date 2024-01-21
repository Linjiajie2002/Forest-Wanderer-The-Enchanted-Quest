#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Point.h"
#include "Animation.h"
#include "SDL/include/SDL.h"
#include "Physics.h"
#include "Render.h"
#include "Timer.h"
#include "vector"

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



	void Camera(float dt);
	void ShakeCamera(int xOffset, int yOffset);
	void keyInput(float dt);
	void godMod(float dt);
	void OnCollision(PhysBody* physA, PhysBody* physB);
	void OnEndCollision(PhysBody* physA, PhysBody* physB);

	void reLoadXML();
	/*void reLoadXML(std::vector<pugi::xml_node>  parameter);*/

	void AtackAnimation(char* atackname);
	void RetAtkAni(Animation* ani, bool* anib);

	


public:
	Animation* currentAnimation = nullptr;

	Animation SPosition;

	Animation idle;
	Animation run;
	Animation defend_on;
	Animation defend_off;
	Animation takehit;
	Animation die;

	Animation Jump_UP;
	Animation Jump_DOWN;
	Animation Jump_DOWN_LOOP;

	Animation crouch;
	Animation highjump;
	Animation slide;
	Animation roll;
	Animation onground;

	Animation close_atk;
	Animation air_atk;
	Animation arrow_atk;
	Animation scope_atk;
	Animation sp_atk;


	Animation* ResetAtackAnimation = nullptr;
	SDL_Rect* spritePositions;


	float speed;
	float crouchspeed;
	float jumpForce;

	int pickCoinFxId;

	int soundjump;
	int finallevel;
	int escudo;
	int intro;

	bool NoControl = true;

	b2Vec2 vel;
	
	const char* texturePath;
	const char* texturePath2;
	SDL_Texture* texture = NULL;
	PhysBody* pbody;

	PhysBody* pbody_closeAtk;


	bool jumping = false;

	Render* render = NULL;

	bool isFacingLeft = false;
	bool isHighJumping = false;

	bool newMap = false;

	uint width;
	uint height;
	//Jump
	bool canJump = true;
	bool playerOnPlatform = true;
	bool playerCheckAir = false;
	int jumpCount = 0;
	bool isDead = false;
	bool AniplayerOnPlatform = false;

	bool starFram = false;
	int noTp = true;
	//Atack
	int atackTypeCount = 0;
	bool isAtack = false;
	bool isAtackarrow = false;
	
	bool is_close_atk = false;
	bool is_sp_atk = false;

	bool* checkisAtk = nullptr;
	Animation* checkAtk;
	bool* atkReset = nullptr;
	char* atkAniname = nullptr;


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
	int firstTouchPlantform = 0;

	bool shake = false;

	int xOffset = (rand() % (2 * shakeMagnitude + 1)) - shakeMagnitude;
	int yOffset = (rand() % (2 * shakeMagnitude + 1)) - shakeMagnitude;

	int originalX = 0;
	int originalY = 0;

	bool changePeson = false;
	bool isAir = false;
	bool palyergethit = false;
	bool isPosibleRevive = false;


	bool In_defend = true;
	bool test2 = false;
	PhysBody* attackParticle;
	Timer timerAtaque;
	bool inEnemyArear = false;
	double lerpvelocidad_x;
	double lerpvelocidad_y;
	bool isVictoria = false;

	bool enble = false;

	int yCameraOffset = 0;



};

#endif // __PLAYER_H__