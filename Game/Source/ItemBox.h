#pragma once
#ifndef __ITEMBOX_H__
#define __ITEMBOX_H__

#include "Entity.h"
#include "Point.h"
#include "Animation.h"


struct SDL_Texture;

class ItemBox : public Entity
{
public:

	ItemBox();

	virtual ~ItemBox();

	bool Awake();

	bool Start();

	bool Update(float dt);

	bool CleanUp();

public:

	bool isPicked = false;

	Animation* currentAnimation = nullptr;
	Animation openBox;


private:

	SDL_Texture* texture;
	SDL_Texture* Boxtexture;
	const char* texturePath;
	const char* BoxPath;
	PhysBody* pbody;
};

#endif // __ITEM_H__