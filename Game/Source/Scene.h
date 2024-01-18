#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Player.h"
#include "Item.h"
#include "Effect.h"
#include "Enemy_Goblin.h"
#include "Boss.h"
#include "PlayerLife.h"
#include "Angel.h"
#include "Item.h"
#include "BossItem.h"
#include "Diamond.h"
#include "Cura.h"
 

struct SDL_Texture;

class Scene : public Module
{
public:

	Scene(bool start_Enabled=true);


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
	Boss* GetBoss();
	PlayerLife* GetPlayerLife();
	Angel* GetAngel();
	Item* GetItem();
	BossItem* GetBossItem();
	Diamond* GetDiamond();
	Cura* GetCura();

	bool LoadState(pugi::xml_node node);

	bool SaveState(pugi::xml_node node);

	pugi::xml_node nodeinfo(EntityType type);
	//std::vector<pugi::xml_node> Scene::nodeinfo(EntityType type);

	void LoadEntities(pugi::xml_node levelNode);



private:
	SDL_Texture* img;
	float textPosX, textPosY = 0;
	uint texW, texH;
	uint windowW, windowH;
	Player* player = new Player;
	Enemy_Goblin* enemy_goblin;
	Effect* effect;
	Boss* boss = new Boss;
	PlayerLife* playerlife;
	Angel*angel;
	Item* item;
	BossItem* bossitem;
	Diamond* diamond;
	Cura* cura;

public:

	SDL_Texture* Pathfindingtexture;
	const char* PathfindingPath;

	bool changeScena = false;
};

#endif // __SCENE_H__