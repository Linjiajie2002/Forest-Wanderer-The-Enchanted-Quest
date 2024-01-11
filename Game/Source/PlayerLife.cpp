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
#include "PlayerLife.h"
#include "Map.h"
#include "Timer.h"

#include "List.h"
#include <random>


PlayerLife::PlayerLife() : Entity(EntityType::BOSSITEM)
{
	name.Create("playerlife");
}

PlayerLife::~PlayerLife() {}

bool PlayerLife::Awake() {

	lifebar_fin_die_texture_Path = parameters.child("lifebar_fin_die").attribute("texturepath").as_string();
	TSprite = parameters.child("lifebar_fin_die").attribute("Tsprite").as_int();
	SpriteX = parameters.child("lifebar_fin_die").attribute("x").as_int();
	SpriteY = parameters.child("lifebar_fin_die").attribute("y").as_int();
	PhotoWeight = parameters.child("lifebar_fin_die").attribute("Pweight").as_int();
	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);
	fin_die.LoadAnim("PlayerLife", "lifebar_fin_die", spritePositions);

	return true;
}

bool PlayerLife::Start() {
	lifebar_fin_die_texture = app->tex->Load(lifebar_fin_die_texture_Path);


	currentAnimation1 = &fin_die;



	return true;
}

bool PlayerLife::Update(float dt)
{


	rect_1 = currentAnimation1->GetCurrentFrame();
	app->render->DrawTexture(lifebar_fin_die_texture, 1920, 950, 4, SDL_FLIP_NONE, &rect_1);

	currentAnimation1->Update();


	return true;
}

bool PlayerLife::CleanUp()
{
	return true;
}




void PlayerLife::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::PLAYER:
		break;
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}

void PlayerLife::OnEndCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::PLAYER:
		break;


	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}