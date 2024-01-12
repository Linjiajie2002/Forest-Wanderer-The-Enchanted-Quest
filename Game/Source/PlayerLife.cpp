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

	lifebar_head_tail_texture_Path = parameters.child("lifebar_head_tail").attribute("texturepath").as_string();
	TSprite = parameters.child("lifebar_head_tail").attribute("Tsprite").as_int();
	SpriteX = parameters.child("lifebar_head_tail").attribute("x").as_int();
	SpriteY = parameters.child("lifebar_head_tail").attribute("y").as_int();
	PhotoWeight = parameters.child("lifebar_head_tail").attribute("Pweight").as_int();
	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);
	//Head
	Head_idle.LoadAnim("PlayerLife_head", "Head_idle", spritePositions);
	Head_treatment.LoadAnim("PlayerLife_head", "Head_treatment", spritePositions);
	Head_takehit.LoadAnim("PlayerLife_head", "Head_takehit", spritePositions);
	Head_die.LoadAnim("PlayerLife_head", "Head_die", spritePositions);
	//Tail
	Tail_treatment_nb.LoadAnim("PlayerLife_head", "Tail_treatment_nb", spritePositions);
	Tail_treatment_ab.LoadAnim("PlayerLife_head", "Tail_treatment_ab", spritePositions);
	Tail_takehit_nb.LoadAnim("PlayerLife_head", "Tail_takehit_nb", spritePositions);
	Tail_takehit_ab.LoadAnim("PlayerLife_head", "Tail_takehit_ab", spritePositions);
	Tail_die.LoadAnim("PlayerLife_head", "Tail_die", spritePositions);
	Tail_idle.LoadAnim("PlayerLife_head", "Tail_idle", spritePositions);


	lifebar_mid_texture_Path = parameters.child("lifebar_mid").attribute("texturepath").as_string();
	TSprite = parameters.child("lifebar_mid").attribute("Tsprite").as_int();
	SpriteX = parameters.child("lifebar_mid").attribute("x").as_int();
	SpriteY = parameters.child("lifebar_mid").attribute("y").as_int();
	PhotoWeight = parameters.child("lifebar_mid").attribute("Pweight").as_int();
	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);
	
	Middle_idle.LoadAnim("PlayerLife_mid", "Middle_idle", spritePositions);
	Middle_treatment_wb.LoadAnim("PlayerLife_mid", "Middle_treatment_wb", spritePositions);
	Middle_treatment_nb.LoadAnim("PlayerLife_mid", "Middle_treatment_nb", spritePositions);
	Middle_treatment_ab.LoadAnim("PlayerLife_mid", "Middle_treatment_ab", spritePositions);
	Middle_takehit_wb.LoadAnim("PlayerLife_mid", "Middle_takehit_wb", spritePositions);
	Middle_takehit_nb.LoadAnim("PlayerLife_mid", "Middle_takehit_nb", spritePositions);
	Middle_takehit_ab.LoadAnim("PlayerLife_mid", "Middle_takehit_ab", spritePositions);
	Middle_die.LoadAnim("PlayerLife_mid", "Middle_die", spritePositions);

	return true;
}

bool PlayerLife::Start() {
	lifebar_head_tail_texture = app->tex->Load(lifebar_head_tail_texture_Path);

	lifebar_mid_texture = app->tex->Load(lifebar_mid_texture_Path);


	currentAnimation1 = &Head_idle;

	currentAnimation2 = &Middle_idle;


	return true;
}

bool PlayerLife::Update(float dt)
{
	//36

	currentAnimation1 = &Head_die;
	rect_1 = currentAnimation1->GetCurrentFrame();
	app->render->DrawTexture(lifebar_head_tail_texture, 60, 15, 2, SDL_FLIP_NONE, &rect_1, 0, 0);
	currentAnimation1->Update();


	currentAnimation2 = &Middle_die;
	for (int i = 0; i < 1; i++)
	{
		lifePos_X = 96 + i * 30;
		rect_2 = currentAnimation2->GetCurrentFrame();
		app->render->DrawTexture(lifebar_mid_texture, lifePos_X, 15, 2, SDL_FLIP_NONE, &rect_2, 0, 0);
		currentAnimation2->Update();
	}

	


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