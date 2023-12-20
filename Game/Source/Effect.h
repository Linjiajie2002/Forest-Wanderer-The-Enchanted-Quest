#ifndef __EFFECT_H__
#define __EFFECT_H__

#include "Entity.h"
#include "Point.h"
#include "Animation.h"

struct SDL_Texture;

class Effect : public Entity
{
public:

	Effect();

	virtual ~Effect();

	bool Awake();

	bool Start();

	bool Update(float dt);

	bool CleanUp();

	void EffectFuncion();
	void ReviveEffectFuncion();

public:

	Animation* currentAnimation = nullptr;
	Animation* currentAnimation2 = nullptr;
	Animation* currentAnimation3 = nullptr;
	
	Animation OroEffect;
	Animation GhostEffect;
	Animation dieEffect;

	Animation SPosition;


	int TSprite;
	int SpriteX;
	int SpriteY;
	int PhotoWeight;
	SDL_Rect* spritePositions;
	


	Animation SPosition2;
	int TSprite2;
	int SpriteX2;
	int SpriteY2;
	int PhotoWeight2;
	SDL_Rect* spritePositions2;

	Animation Gravity_Void;
	int TSprite3;
	int SpriteX3;
	int SpriteY3;
	int PhotoWeight3;
	SDL_Rect* spritePositions3;

	
	bool check = false;
	bool sonid_vic = false;
	
private:

	SDL_Texture* Effecttexture;
	const char* EffectPath;

	SDL_Texture* Effecttexture2;
	const char* EffectPath2;

	SDL_Texture* Effecttexture3;
	const char* EffectPath3;
	PhysBody* pbody;
	
};

#endif // __EFFECT_H__