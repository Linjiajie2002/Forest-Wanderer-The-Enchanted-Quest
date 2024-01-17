#pragma once
#pragma once
#ifndef __CURA_H__
#define __CURA_H__


#include "Entity.h"
#include "Point.h"
#include "Animation.h"
#include <cmath>
#include <tuple>
#include "SDL/include/SDL.h"
#include "Timer.h"

#include "List.h"

struct SDL_Texture;

class Cura : public Entity
{
public:

	Cura();
	virtual ~Cura();

	bool Awake();

	bool Start();

	bool Update(float dt);

	bool CleanUp();

	void DestroyCura();

	void OnCollision(PhysBody* physA, PhysBody* physB);

	void reLoadXML(pugi::xml_node& parameters);

	int getRemainingTime();

	int updateTimer(time_t start_time);

	std::string getTimeString(int elapsed_time);

	std::string formatCountdown(int total_seconds);


public:

	Animation* currentAnimation = nullptr;

	Animation idle;
	Animation start;
	Animation die;
	Animation SPosition;
	SDL_Rect* spritePositions;

	int TSprite;
	int SpriteX;
	int SpriteY;
	int PhotoWeight;
	int pos_X;
	int pos_Y;

	int numbers = -1;

	bool playerGetCura = false;
	bool playerCuraDie = false;

	SDL_Rect rect;



	uint32 secondsSinceStartup = 0;
	Timer startupTime;
private:

	SDL_Texture* Curatexture;
	const char* CuraPath;

	PhysBody* pbody;
};
#endif // __ITEM_H__