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
	void LastEffect();
	void goMap2();
	void reLoadXML();

public:

	Animation* currentAnimation = nullptr;
	Animation* currentAnimation2 = nullptr;
	Animation* currentAnimation3 = nullptr;
	Animation* currentAnimation4 = nullptr;
	
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
	Animation Gravity_Void;
	Animation DiamanteEffect;
	
	bool check = false;
	bool sonid_vic = false;
	
private:

	SDL_Texture* Effecttexture;
	const char* EffectPath;

	SDL_Texture* Effecttexture2;
	const char* EffectPath2;

	SDL_Texture* Effecttexture3;
	const char* EffectPath3;

	SDL_Texture* Effecttexture4;
	const char* EffectPath4;
	PhysBody* pbody;
	
};

#endif // __EFFECT_H__