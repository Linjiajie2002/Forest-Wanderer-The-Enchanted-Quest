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

	void DeadEffectFuncion();
	void ReviveEffectFuncion();

public:

	Animation* currentAnimation = nullptr;
	Animation dieEffect;
	Animation reviveEffect;


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

	bool check = false;

private:

	SDL_Texture* Effecttexture;
	const char* EffectPath;

	SDL_Texture* Effecttexture2;
	const char* EffectPath2;
	PhysBody* pbody;
};

#endif // __EFFECT_H__