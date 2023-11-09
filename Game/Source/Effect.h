#ifndef __EFFECT_H__
#define __EFFECT_H__

#include "Entity.h"
#include "Point.h"
#include "Animation.h"

class Effect : public Entity
{
public:

	Effect();

	virtual ~Effect();

	bool Awake();

	bool Start();

	bool Update(float dt);

	bool CleanUp();

public:

	Animation* currentAnimation = nullptr;
	Animation dieEffect;

	Animation SPosition;
	SDL_Rect* spritePositions;

	int TSprite;
	int SpriteX;
	int SpriteY;
	int PhotoWeight;

private:

	SDL_Texture* Effecttexture;
	const char* EffectPath;
	PhysBody* pbody;
};

#endif // __ITEM_H__