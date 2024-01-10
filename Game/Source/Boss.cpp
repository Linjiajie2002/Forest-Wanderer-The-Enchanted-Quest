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
#include "Timer.h"

#include "List.h"
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
	for (int i = 0; i < numeroAtack; i++)
	{
		atack_2.Add(inicializaAnimation);

		atack_2[i].LoadAnim("Boss", "atack_2", spritePositions);
	}
	

	boss_atack_3_texture_Path = parameters.child("boss_atack").child("atack3").attribute("texturepath").as_string();
	TSprite = parameters.child("boss_atack").child("atack3").attribute("Tsprite").as_int();
	SpriteX = parameters.child("boss_atack").child("atack3").attribute("x").as_int();
	SpriteY = parameters.child("boss_atack").child("atack3").attribute("y").as_int();
	PhotoWeight = parameters.child("boss_atack").child("atack3").attribute("Pweight").as_int();
	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);
	atack_3.LoadAnim("Boss", "atack_3", spritePositions);


	boss_atack_4_texture_Path = parameters.child("boss_atack").child("atack4").attribute("texturepath").as_string();
	TSprite = parameters.child("boss_atack").child("atack4").attribute("Tsprite").as_int();
	SpriteX = parameters.child("boss_atack").child("atack4").attribute("x").as_int();
	SpriteY = parameters.child("boss_atack").child("atack4").attribute("y").as_int();
	PhotoWeight = parameters.child("boss_atack").child("atack4").attribute("Pweight").as_int();
	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);
	atack_4_start.LoadAnim("Boss", "atack_4_start", spritePositions);
	atack_4_running.LoadAnim("Boss", "atack_4_running", spritePositions);
	atack_4_end.LoadAnim("Boss", "atack_4_end", spritePositions);

	return true;
}

bool Boss::Start() {
	
	boss_atack_1_texture = app->tex->Load(boss_atack_1_texture_Path);
	boss_atack_2_texture = app->tex->Load(boss_atack_2_texture_Path);
	boss_atack_3_texture = app->tex->Load(boss_atack_3_texture_Path);
	boss_atack_4_texture = app->tex->Load(boss_atack_4_texture_Path);


	
	
	currentAnimation1 = &atack_1;

	for (int i = 0; i < numeroAtack; i++)
	{

		currentAnimation2.Add(&atack_2[i]);
		rect_2.Add(currentAnimation2[i]->GetCurrentFrame());

	}

	currentAnimation3 = &atack_3;

	currentAnimation4 = &atack_4_start;

	return true;
}

bool Boss::Update(float dt)
{

	if (app->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN) {

		inBossBattle = true;
		tpToinBossBattle = true;
	}

	if (app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN) {
		getPlayerPosition = true;
		attackMethod = 1;
	}


	if (inBossBattle && attackMethod == 1) {
		if (getPlayerPosition) {
			player_x = app->scene->GetPlayer()->position.x;
			getPlayerPosition = false;
		}
		boss_atack_1(player_x);
	}

	if (currentAnimation1->HasFinished()) {
		getPlayerPosition = true;
		atack_1.Reset();
		attackMethod = 2;
	}


	if (inBossBattle && attackMethod == 2) {

		if (getPlayerPosition) {
			player_x = app->scene->GetPlayer()->position.x;
			getPlayerPosition = false;
		}

		if (player_x > 1899) {
			direction_Atack = true;
		}
		else {
			direction_Atack = false;
		}
		
		if (atack2_generAtack.ReadMSec() > 200) {
			if (maxNumAtack < numeroAtack) {
				maxNumAtack++;
				atack2_generAtack.Start();
			}
			else {
				allPrint = true;
			}
		}

		for (int i = 0; i < maxNumAtack; i++)
		{
			boss_atack_2(direction_Atack, i);
		}

	}


	if (currentAnimation2[numeroAtack-1]->HasFinished() && allPrint) {
		for (int i = 0; i < numeroAtack; i++)
		{
			atack_2[i].Reset();
		}
		maxNumAtack = 0;
		attackMethod = 3;
	}


	if (inBossBattle && attackMethod == 3) {
		boss_atack_3(direction_Atack);
	}


	if (currentAnimation3->HasFinished()) {
		atack_3.Reset();
		attackMethod = 4;
		currentAnimation4 = &atack_4_start;
	}


	if (inBossBattle && attackMethod == 4) {
		boss_atack_4(direction_Atack);
	}

	if (currentAnimation4->HasFinished()) {

		if (currentAnimation4->getNameAnimation() == "atack_4_start") {
			currentAnimation4 = &atack_4_running;
		}
		if (currentAnimation4->getNameAnimation() == "atack_4_end") {
			atack_4_start.Reset();
			atack_4_end.Reset();
			atack_4_running.Reset();
			getPlayerPosition = true;
			attackMethod = 1;
			velocitat = 0;
		}
	}

	return true;
}

bool Boss::CleanUp()
{
	return true;
}

void Boss::boss_atack_1(int player_x)
{


	if (player_x != 0 && player_x > 1300) {
		//printf("\n%d ", player_x);
		rect_1 = currentAnimation1->GetCurrentFrame();
		app->render->DrawTexture(boss_atack_1_texture, player_x - 200, 590, 1, SDL_FLIP_NONE, &rect_1);
		currentAnimation1->Update();
	}
}

void Boss::boss_atack_2(bool inversaAtack, int numberAtack)
{

	distancia = 200 * numberAtack;

	rect_2[numberAtack] = currentAnimation2[numberAtack]->GetCurrentFrame();
	if (inversaAtack) {
		app->render->DrawTexture(boss_atack_2_texture, 2150 - distancia, 400, 1.5, SDL_FLIP_NONE, &rect_2[numberAtack]);
	}
	else {
		app->render->DrawTexture(boss_atack_2_texture, 1250 + distancia, 400, 1.5, SDL_FLIP_NONE, &rect_2[numberAtack]);
	}
	currentAnimation2[numberAtack]->Update();
}

void Boss::boss_atack_3(bool inversaAtack)
{
	rect_3 = currentAnimation3->GetCurrentFrame();
	if (inversaAtack) {
		app->render->DrawTexture(boss_atack_3_texture, 1350, 660, 2, SDL_FLIP_NONE, &rect_3);
	}
	else {
		app->render->DrawTexture(boss_atack_3_texture, 1750, 660, 2, SDL_FLIP_HORIZONTAL, &rect_3);

	}
	currentAnimation3->Update();
}

void Boss::boss_atack_4(bool inversaAtack)
{
	rect_4 = currentAnimation4->GetCurrentFrame();
	
	if (currentAnimation4->getNameAnimation() == "atack_4_running") {
		velocitat += 10.0;	
	}

	if (inversaAtack) {
		atack4_posX = atack4_posX_R + velocitat;
		app->render->DrawTexture(boss_atack_4_texture, atack4_posX, 1010, 0.7, SDL_FLIP_NONE, &rect_4);

		if (atack4_posX >= atack4_posX_L) {
			currentAnimation4 = &atack_4_end;
		}
	}
	else {
		atack4_posX = atack4_posX_L - velocitat;
		app->render->DrawTexture(boss_atack_4_texture, atack4_posX, 1010, 0.7, SDL_FLIP_NONE, &rect_4);
		if (atack4_posX <= atack4_posX_R) {
			currentAnimation4 = &atack_4_end;
		}
	}

	currentAnimation4->Update();

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