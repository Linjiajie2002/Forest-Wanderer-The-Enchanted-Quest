#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "Boss.h"
#include "Map.h"

#include <random>

Boss::Boss() : Entity(EntityType::BOSS)
{
	name.Create("boss");
}

Boss::~Boss() {}

bool Boss::Awake() {

	boss_atack_1_texture_Path = parameters.child("boss_atack").child("atack1").attribute("texturepath").as_string();
	TSprite = parameters.child("boss_atack").child("atack1").attribute("Tsprite").as_int();
	SpriteX = parameters.child("boss_atack").child("atack1").attribute("x").as_int();
	SpriteY = parameters.child("boss_atack").child("atack1").attribute("y").as_int();
	PhotoWeight = parameters.child("boss_atack").child("atack1").attribute("Pweight").as_int();
	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);
	atack_1.LoadAnim("Boss", "atack_1", spritePositions);


	boss_atack_2_texture_Path = parameters.child("boss_atack").child("atack2").attribute("texturepath").as_string();
	TSprite = parameters.child("boss_atack").child("atack2").attribute("Tsprite").as_int();
	SpriteX = parameters.child("boss_atack").child("atack2").attribute("x").as_int();
	SpriteY = parameters.child("boss_atack").child("atack2").attribute("y").as_int();
	PhotoWeight = parameters.child("boss_atack").child("atack2").attribute("Pweight").as_int();
	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);
	atack_2.LoadAnim("Boss", "atack_2", spritePositions);



	boss_atack_3_texture_Path = parameters.child("boss_atack").child("atack3").attribute("texturepath").as_string();
	TSprite = parameters.child("boss_atack").child("atack3").attribute("Tsprite").as_int();
	SpriteX = parameters.child("boss_atack").child("atack3").attribute("x").as_int();
	SpriteY = parameters.child("boss_atack").child("atack3").attribute("y").as_int();
	PhotoWeight = parameters.child("boss_atack").child("atack3").attribute("Pweight").as_int();
	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);
	atack_3.LoadAnim("Boss", "atack_3", spritePositions);

	return true;
}

bool Boss::Start() {
	boss_atack_1_texture = app->tex->Load(boss_atack_1_texture_Path);
	boss_atack_2_texture = app->tex->Load(boss_atack_3_texture_Path);

	currentAnimation1 = &atack_1;
	currentAnimation2 = &atack_3;

	return true;
}

bool Boss::Update(float dt)
{

	SDL_Rect rect = currentAnimation2->GetCurrentFrame();


	//app->render->DrawTexture(boss_atack_1_texture, 40, 570, 1 , SDL_FLIP_NONE,&rect);
	app->render->DrawTexture(boss_atack_2_texture, 40, 660, 2, SDL_FLIP_NONE, &rect);


	currentAnimation2->Update();
	return true;
}

bool Boss::CleanUp()
{
	return true;
}



void Boss::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::PLAYER:
		AtackPlayer = true;
		break;

	case ColliderType::ENEMYAREA:
		inEenemyArea = true;
		break;

	case ColliderType::CLOSEATK_PLAYER:
		isTakehit = true;
		life--;
		break;
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}

void Boss::OnEndCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::PLAYER:
		AtackPlayer = false;
		break;

	case ColliderType::ENEMYAREA:
		inEenemyArea = false;
		break;
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}