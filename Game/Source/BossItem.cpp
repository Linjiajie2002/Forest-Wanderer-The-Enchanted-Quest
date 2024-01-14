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
#include "BossItem.h"
#include "Map.h"
#include "Timer.h"

#include "List.h"
#include <random>
#include <cstdlib>


BossItem::BossItem() : Entity(EntityType::BOSSITEM)
{
	name.Create("bossitem");
}

BossItem::~BossItem() {}

bool BossItem::Awake() {

	ball_blue_texture_Path = parameters.child("boss_ball").child("ball_blue").attribute("texturepath").as_string();
	TSprite = parameters.child("boss_ball").child("ball_blue").attribute("Tsprite").as_int();
	SpriteX = parameters.child("boss_ball").child("ball_blue").attribute("x").as_int();
	SpriteY = parameters.child("boss_ball").child("ball_blue").attribute("y").as_int();
	PhotoWeight = parameters.child("boss_ball").child("ball_blue").attribute("Pweight").as_int();
	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);
	ball_blue_start.LoadAnim("BossItem", "ball_blue_start", spritePositions);
	ball_blue_running.LoadAnim("BossItem", "ball_blue_running", spritePositions);
	ball_blue_end.LoadAnim("BossItem", "ball_blue_end", spritePositions);

	return true;
}

bool BossItem::Start() {
	ball_blue_texture = app->tex->Load(ball_blue_texture_Path);
	currentAnimation1 = &ball_blue_start;

	pbody = app->physics->CreateCircle(energyPos_X + 52, energyPos_Y + 52, 28, bodyType::STATIC);
	pbody->ctype = ColliderType::ENERGYBALL;
	pbody->body->SetFixedRotation(true);
	pbody->listener = this;


	return true;
}

bool BossItem::Update(float dt)
{
	/*currentAnimation1 = &ball_blue_running;*/


	if (crearBall)ballPosition = randPosition(), crearBall = false, deleteBall.Start();


	if (ballPosition.x > 0 && ballPosition.y > 0 && timeWait.ReadMSec() > 2000) {
		randCreatEnergyBall(ballPosition);
	}



	if (app->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN) {
		currentAnimation1->Reset();
		currentAnimation1 = &ball_blue_end;
	}

	if (deleteBall.ReadMSec() >= 7000) {
		deleteBall.Start();
		currentAnimation1->Reset();
		currentAnimation1 = &ball_blue_end;
	}



	if (currentAnimation1->HasFinished())
	{

		if (currentAnimation1->getNameAnimation() == "ball_blue_start") {
			currentAnimation1->Reset();
			currentAnimation1 = &ball_blue_running;

		}
		if (currentAnimation1->getNameAnimation() == "ball_blue_end") {
			currentAnimation1->Reset();
			currentAnimation1 = &ball_blue_start;
			crearBall = true;
			timeWait.Start();
		}
	}

	return true;
}

bool BossItem::CleanUp()
{
	return true;
}





void BossItem::randCreatEnergyBall(iPoint ballPosition, int tipo)
{

	rect_1 = currentAnimation1->GetCurrentFrame();

	if (tipo == 0) {
		app->render->DrawTexture(ball_blue_texture, ballPosition.x, ballPosition.y, 0.4, SDL_FLIP_NONE, &rect_1);
	}
	//else if (tipo == 1) {
	//	app->render->DrawTexture(ball_red_texture, ballPosition.x, ballPosition.y, 0.4, SDL_FLIP_NONE, &rect_1);
	//}
	//else {
	//	app->render->DrawTexture(ball_yello_texture, ballPosition.x, ballPosition.y, 0.4, SDL_FLIP_NONE, &rect_1);
	//}


	currentAnimation1->Update();



}

iPoint BossItem::randPosition()
{

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis_X(1440, 2400);
	std::uniform_int_distribution<> dis_Y(896, 1088);

	iPoint Result;

	Result.x = dis_X(gen);
	Result.y = dis_Y(gen);

	return Result;
}

void BossItem::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::PLAYER:
		break;
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}

void BossItem::OnEndCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::PLAYER:
		break;


	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}