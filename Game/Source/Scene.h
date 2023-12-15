#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Player.h"
#include "Item.h"
#include "Effect.h"
#include "Enemy_Goblin.h"

struct SDL_Texture;

class Scene : public Module
{
public:

	Scene();

	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();


	Player* GetPlayer();
	Effect* GetEffect();
	Enemy_Goblin* GetGoblin();

	bool LoadState(pugi::xml_node node);

	bool SaveState(pugi::xml_node node);

private:
	SDL_Texture* img;
	float textPosX, textPosY = 0;
	uint texW, texH;
	uint windowW, windowH;
	Player* player;
	Enemy_Goblin* enemy_goblin;
	Effect* effect;
public:

	SDL_Texture* Pathfindingtexture;
	const char* PathfindingPath;
};

#endif // __SCENE_H__