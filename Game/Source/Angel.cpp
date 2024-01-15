#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "Angel.h"
#include "Map.h"
#include "Timer.h"
#include "Boss.h"

#include "List.h"
#include <random>

Angel::Angel() : Entity(EntityType::BOSS)
{
	name.Create("boss");
}

Angel::~Angel() {}

bool Angel::Awake() {

	angel_blue_texture_Path = parameters.child("angel_all").child("angel_texture1").attribute("texturepath").as_string();
	angel_red_texture_Path = parameters.child("angel_all").child("angel_texture2").attribute("texturepath").as_string();
	angel_yellow_texture_Path = parameters.child("angel_all").child("angel_texture3").attribute("texturepath").as_string();
	TSprite = parameters.child("angel_all").attribute("Tsprite").as_int();
	SpriteX = parameters.child("angel_all").attribute("x").as_int();
	SpriteY = parameters.child("angel_all").attribute("y").as_int();
	PhotoWeight = parameters.child("angel_all").attribute("Pweight").as_int();
	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);

	angel_blue_start.LoadAnim("angel", "angel_all_start", spritePositions);
	angel_blue_idle.LoadAnim("angel", "angel_all_idle", spritePositions);
	angel_blue_die.LoadAnim("angel", "angel_all_die", spritePositions);

	angel_red_start.LoadAnim("angel", "angel_all_start", spritePositions);
	angel_red_idle.LoadAnim("angel", "angel_all_idle", spritePositions);
	angel_red_die.LoadAnim("angel", "angel_all_die", spritePositions);

	angel_yellow_start.LoadAnim("angel", "angel_all_start", spritePositions);
	angel_yellow_idle.LoadAnim("angel", "angel_all_idle", spritePositions);
	angel_yellow_die.LoadAnim("angel", "angel_all_die", spritePositions);




	angel_borde_blue_texture_Path = parameters.child("borde").child("angel_texture1").attribute("texturepath").as_string();
	angel_borde_red_texture_Path = parameters.child("borde").child("angel_texture2").attribute("texturepath").as_string();
	angel_borde_yellow_texture_Path = parameters.child("borde").child("angel_texture3").attribute("texturepath").as_string();
	TSprite = parameters.child("borde").attribute("Tsprite").as_int();
	SpriteX = parameters.child("borde").attribute("x").as_int();
	SpriteY = parameters.child("borde").attribute("y").as_int();
	PhotoWeight = parameters.child("borde").attribute("Pweight").as_int();
	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);

	angel_borde_red_idle.LoadAnim("angel_borde", "angel_borde_blue", spritePositions);
	angel_borde_yellow_idle.LoadAnim("angel_borde", "angel_borde_blue", spritePositions);
	angel_borde_blue_idle.LoadAnim("angel_borde", "angel_borde_blue", spritePositions);

	return true;
}

bool Angel::Start() {

	//boss_atack_1_texture = app->tex->Load(boss_atack_1_texture_Path);
	/*if (app->scene->changeScena) {
		app->scene->changeScena = false;
		angel_blue_texture_Path = parameters.child("angel_all").child("angel_texture1").attribute("texturepath").as_string();
		angel_red_texture_Path = parameters.child("angel_all").child("angel_texture2").attribute("texturepath").as_string();
		angel_yellow_texture_Path = parameters.child("angel_all").child("angel_texture3").attribute("texturepath").as_string();

		angel_borde_blue_texture_Path = parameters.child("borde").child("angel_texture1").attribute("texturepath").as_string();
		angel_borde_red_texture_Path = parameters.child("borde").child("angel_texture2").attribute("texturepath").as_string();
		angel_borde_yellow_texture_Path = parameters.child("borde").child("angel_texture3").attribute("texturepath").as_string();
	}*/

	if (app->scene->changeScena) {
		Awake();
	}
	angel_blue_texture = app->tex->Load(angel_blue_texture_Path);
	angel_red_texture = app->tex->Load(angel_red_texture_Path);
	angel_yellow_texture = app->tex->Load(angel_yellow_texture_Path);

	angel_borde_blue_texture = app->tex->Load(angel_borde_blue_texture_Path);
	angel_borde_red_texture = app->tex->Load(angel_borde_red_texture_Path);
	angel_borde_yellow_texture = app->tex->Load(angel_borde_yellow_texture_Path);



	currentAnimation1 = &angel_red_idle;

	currentAnimation2 = &angel_yellow_idle;

	currentAnimation3 = &angel_blue_idle;

	currentAnimation4 = &angel_borde_red_idle;

	currentAnimation5 = &angel_borde_yellow_idle;

	currentAnimation6 = &angel_borde_blue_idle;

	return true;
}

bool Angel::Update(float dt)
{

	/*printf("\nBlueball: %d", blueball);
	printf("\nRedball: %d", redball);
	printf("\nYellowball: %d", yelloweball);*/


	CheckPoint();

	if (blueball == 5 && redball == 5 && yelloweball == 5) {
		currentAnimation1 = &angel_red_die;
		currentAnimation2 = &angel_yellow_die;
		currentAnimation3 = &angel_blue_die;
		Enter = false;
		
		app->scene->GetItem()->LastDiamante();
	}

	//if (app->scene->GetItem()->victoria && Enter)
	//{
	//	//printf("\n%s", currentAnimation1->getNameAnimation());

	//	currentAnimation1 = &angel_red_die;
	//	currentAnimation2 = &angel_yellow_die;
	//	currentAnimation3 = &angel_blue_die;
	//	Enter = false;

	//}
	//else 
	if (app->scene->GetBoss()->inBossBattle && Enter) {
		currentAnimation1 = &angel_red_start;
		currentAnimation2 = &angel_yellow_start;
		currentAnimation3 = &angel_blue_start;
		Enter = false;
		deleteAngel = false;

	}




	if (currentAnimation1->HasFinished() && currentAnimation1->getNameAnimation() == "angel_all_start") {
		currentAnimation1 = &angel_red_idle;
		currentAnimation2 = &angel_yellow_idle;
		currentAnimation3 = &angel_blue_idle;
		app->scene->GetBossItem()->crearBall = true;
		app->scene->GetBossItem()->timeWait.Start();
		app->scene->GetBossItem()->deleteBall.Start();
		angel_red_start.Reset();
		angel_yellow_start.Reset();
		angel_blue_start.Reset();

		app->scene->GetBoss()->getPlayerPosition = true;
		app->scene->GetBoss()->attackMethod = 1;
		

	}



	if (currentAnimation1->HasFinished() && currentAnimation1->getNameAnimation() == "angel_all_die") {
		deleteAngel = true;
		angel_red_die.Reset();
		angel_yellow_die.Reset();
		angel_blue_die.Reset();


		currentAnimation1 = &angel_red_start;
		currentAnimation2 = &angel_yellow_start;
		currentAnimation3 = &angel_blue_start;
	}


	if (deleteAngel == false && app->scene->GetBoss()->inBossBattle) {
		rect_1 = currentAnimation1->GetCurrentFrame();
		app->render->DrawTexture(angel_red_texture, 1550, 600, 0.5, SDL_FLIP_NONE, &rect_1);
		currentAnimation1->Update();

		rect_2 = currentAnimation2->GetCurrentFrame();
		app->render->DrawTexture(angel_yellow_texture, 1900, 600, 0.5, SDL_FLIP_NONE, &rect_2);
		currentAnimation2->Update();

		rect_3 = currentAnimation3->GetCurrentFrame();
		app->render->DrawTexture(angel_blue_texture, 2250, 600, 0.5, SDL_FLIP_NONE, &rect_3);
		currentAnimation3->Update();

		rect_4 = currentAnimation4->GetCurrentFrame();
		app->render->DrawTexture(angel_borde_red_texture, 1573, 770, 2, SDL_FLIP_NONE, &rect_4);

		rect_5 = currentAnimation5->GetCurrentFrame();
		app->render->DrawTexture(angel_borde_yellow_texture, 1923, 770, 2, SDL_FLIP_NONE, &rect_5);


		rect_6 = currentAnimation6->GetCurrentFrame();
		app->render->DrawTexture(angel_borde_blue_texture, 2273, 770, 2, SDL_FLIP_NONE, &rect_6);
	}
	else {
		app->scene->GetBoss()->inBossBattle = false;
	}







	return true;
}

bool Angel::CleanUp()
{
	SDL_DestroyTexture(angel_blue_texture);
	SDL_DestroyTexture(angel_red_texture);
	SDL_DestroyTexture(angel_yellow_texture);
	SDL_DestroyTexture(angel_borde_blue_texture);
	SDL_DestroyTexture(angel_borde_red_texture);
	SDL_DestroyTexture(angel_borde_yellow_texture);
	return true;
}

void Angel::GetPoint(int color)
{
	ballColor = color;
	bluebar = true;
	countBar = 0;
}

void Angel::CheckPoint()
{
	if (bluebar && getPoint == false) {
		countBar++;
		if (ballColor == 0 && blueball != 5) {
			currentAnimation6->Update();

		}
		else if (ballColor == 1 && redball != 5) {
			currentAnimation4->Update();

		}
		else if (ballColor == 2 && yelloweball != 5) {
			currentAnimation5->Update();
		}

		if (countBar == 11) {
			bluebar = false;
			getPoint = true;

			if (ballColor == 0 && blueball != 5) {
				blueball++;
			}
			else if (ballColor == 1 && redball != 5) {
				redball++;
			}
			else if (ballColor == 2 && yelloweball != 5) {
				yelloweball++;
			}

		}
	}
}



void Angel::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::PLAYER:
		break;
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}

void Angel::OnEndCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::PLAYER:
		break;


	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}