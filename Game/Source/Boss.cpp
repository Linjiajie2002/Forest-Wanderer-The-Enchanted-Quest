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
	boss_atack_2_texture = app->tex->Load(boss_atack_2_texture_Path);
	boss_atack_3_texture = app->tex->Load(boss_atack_3_texture_Path);

	currentAnimation1 = &atack_1;
	currentAnimation2 = &atack_2;
	currentAnimation3 = &atack_3;

	return true;
}

bool Boss::Update(float dt)
{



	if (app->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN) {

		inBossBattle = true;
		tpToinBossBattle = true;
	}

	rect_1 = currentAnimation1->GetCurrentFrame();
	app->render->DrawTexture(boss_atack_1_texture, 1350, 500, 1, SDL_FLIP_NONE, &rect_1);
	currentAnimation1->Update();

	rect_2 = currentAnimation2->GetCurrentFrame();
	app->render->DrawTexture(boss_atack_2_texture, 1350, 570, 1.5, SDL_FLIP_NONE, &rect_2);
	currentAnimation2->Update();

	rect_3 = currentAnimation3->GetCurrentFrame();
	app->render->DrawTexture(boss_atack_3_texture, 1350, 660, 2, SDL_FLIP_NONE, &rect_3);
	currentAnimation3->Update();

	//rect_3 = currentAnimation3->GetCurrentFrame();

	////app->render->DrawTexture(boss_atack_1_texture, 40, 570, 1 , SDL_FLIP_NONE,&rect);
	//app->render->DrawTexture(boss_atack_1_texture, 1350, 660, 2, SDL_FLIP_NONE, &rect_1);
	//app->render->DrawTexture(boss_atack_2_texture, 1350, 660, 2, SDL_FLIP_NONE, &rect_2);
	///**/app->render->DrawTexture(boss_atack_3_texture, 1350, 660, 2, SDL_FLIP_NONE, &rect_3); */


	//currentAnimation1->Update();
	///*currentAnimation2->Update();
	//currentAnimation3->Update();*/
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
		break;

	
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}