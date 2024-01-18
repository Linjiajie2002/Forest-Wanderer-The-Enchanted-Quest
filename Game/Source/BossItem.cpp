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

	/*ball_blue_texture_Path = parameters.child("boss_ball").child("ball_blue").attribute("texturepath").as_string();
	TSprite = parameters.child("boss_ball").child("ball_blue").attribute("Tsprite").as_int();
	SpriteX = parameters.child("boss_ball").child("ball_blue").attribute("x").as_int();
	SpriteY = parameters.child("boss_ball").child("ball_blue").attribute("y").as_int();
	PhotoWeight = parameters.child("boss_ball").child("ball_blue").attribute("Pweight").as_int();
	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);

	ball_blue_start.LoadAnim("BossItem", "ball_blue_start", spritePositions);
	ball_blue_running.LoadAnim("BossItem", "ball_blue_running", spritePositions);
	ball_blue_end.LoadAnim("BossItem", "ball_blue_end", spritePositions);

	ball_red_start.LoadAnim("BossItem", "ball_red_start", spritePositions);
	ball_red_running.LoadAnim("BossItem", "ball_red_running", spritePositions);
	ball_red_end.LoadAnim("BossItem", "ball_red_end", spritePositions);

	ball_yellow_start.LoadAnim("BossItem", "ball_yellow_start", spritePositions);
	ball_yellow_running.LoadAnim("BossItem", "ball_yellow_running", spritePositions);
	ball_yellow_end.LoadAnim("BossItem", "ball_yellow_end", spritePositions);*/

	return true;
}

bool BossItem::Start() {


	reLoadXML();




	ball_blue_texture = app->tex->Load(ball_blue_texture_Path);
	cura_texture = app->tex->Load(cura_texture_Path);

	currentAnimation1 = &ball_blue_start;

	currentAnimation2 = &start;
	ballColor = 0;



	return true;
}

bool BossItem::Update(float dt)
{
	/*currentAnimation1 = &ball_blue_running;*/
	if (app->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN) {
		currentAnimation1->Reset();
		currentAnimation1 = &ball_blue_end;
	}

	if (crearBall && app->scene->GetBoss()->inBossBattle) {
		ballPosition = randPosition();
		ballType = randBall();
		crearBall = false;
		crearBallrd = true;
	}

	if (crearCura && app->scene->GetBoss()->inBossBattle) {
		curaPosition = randPosition();
		crearCura = false;
		crearCurard = true;
	}


	if (!app->scene->GetBoss()->inBossBattle && app->scene->GetBoss()->oneTimeInBossBattle) {
		if (pbody != nullptr) {
			pbody->body->GetWorld()->DestroyBody(pbody->body);
			pbody = nullptr;
		}

		if (pbody1 != nullptr) {
			pbody1->body->GetWorld()->DestroyBody(pbody1->body);
			pbody1 = nullptr;
		}
	}

	if (ballPosition.x > 0 && ballPosition.y > 0 && timeWait.ReadMSec() > 2000 && app->scene->GetBoss()->inBossBattle) {
		randCreatEnergyBall(ballPosition);
	}

	if (curaPosition.x > 0 && curaPosition.y > 0 && curatimeWait.ReadMSec() > 15000 && app->scene->GetBoss()->inBossBattle) {
		randCreatCura(curaPosition);
	}
	//printf("\n%f", (float)deleteCura.ReadSec());

	if (deleteCura.ReadMSec() >= 3000 || playerTouchCura && oneTouch_cura) {
		deleteCura.Start();
		playerTouchCura = false;

		if (currentAnimation2->getNameAnimation() == "cura_idle") {
			currentAnimation2 = &die;
		}
		currentAnimation2->Reset();
	}

	if (deleteBall.ReadMSec() >= 5000 || playerTouchBall && oneTouch) {
		deleteBall.Start();
		playerTouchBall = false;
		oneTouch = false;
		if (firstBall == false) {
			if (currentAnimation1->getNameAnimation() == "ball_blue_running") {
				currentAnimation1 = &ball_blue_end;
			}
			else if (currentAnimation1->getNameAnimation() == "ball_red_running") {
				currentAnimation1 = &ball_red_end;
			}
			else if (currentAnimation1->getNameAnimation() == "ball_yellow_running") {
				currentAnimation1 = &ball_yellow_end;
			}
		}
		else {
			currentAnimation1 = &ball_blue_end;
		}

		currentAnimation1->Reset();
	}

	actualizarAnimacion();



	return true;
}

bool BossItem::CleanUp()
{
	if (ball_blue_texture) {
		SDL_DestroyTexture(ball_blue_texture);
	}
	return true;
}





void BossItem::randCreatEnergyBall(iPoint ballPosition)
{
	//printf("%d", ballType);
	rect_1 = currentAnimation1->GetCurrentFrame();
	if (crearBallrd) {
		pbody = app->physics->CreateCircleSensor(ballPosition.x + 52, ballPosition.y + 52, 28, bodyType::STATIC);
		pbody->ctype = ColliderType::ENERGYBALL;
		pbody->body->SetFixedRotation(true);
		pbody->listener = this;
		crearBallrd = false;
		app->scene->GetAngel()->getPoint = false;
	}

	app->render->DrawTexture(ball_blue_texture, ballPosition.x, ballPosition.y, 0.4, SDL_FLIP_NONE, &rect_1);
	currentAnimation1->Update();
}

void BossItem::randCreatCura(iPoint curaPosition)
{
	rect_2 = currentAnimation2->GetCurrentFrame();
	if (crearCurard) {
		pbody1 = app->physics->CreateCircleSensor(curaPosition.x + 54, curaPosition.y + 54, 28, bodyType::STATIC);
		pbody1->ctype = ColliderType::ITEM;
		pbody1->body->SetFixedRotation(true);
		pbody1->listener = this;
		crearCurard = false;
	}
	if (currentAnimation2->getNameAnimation() == "cura_die" && playerTouchCura) {
		app->render->DrawTexture(cura_texture, app->scene->GetPlayer()->position.x, app->scene->GetPlayer()->position.y - 30, 1, SDL_FLIP_NONE, &rect_2);
	}
	else {
		app->render->DrawTexture(cura_texture, curaPosition.x, curaPosition.y, 1, SDL_FLIP_NONE, &rect_2);
	}
	currentAnimation2->Update();
}

void BossItem::CheckBallStarT(int tipo)
{


	if (firstBall == false) {

		if (tipo == 0) {
			currentAnimation1 = &ball_blue_start;
			ballColor = 0;
		}
		else if (tipo == 1) {
			currentAnimation1 = &ball_red_start;
			ballColor = 1;
		}
		else {
			currentAnimation1 = &ball_yellow_start;
			ballColor = 2;
		}
	}
}

iPoint BossItem::randPosition()
{

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis_X(1440, 2300);
	std::uniform_int_distribution<> dis_Y(896, 1070);

	iPoint Result;

	Result.x = dis_X(gen);
	Result.y = dis_Y(gen);

	return Result;
}

int BossItem::randBall()
{

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 2);
	int Result;

	Result = dis(gen);
	return Result;
}

void BossItem::actualizarAnimacion()
{
	if (currentAnimation2->HasFinished()) {
		if (currentAnimation2->getNameAnimation() == "cura_start") {
			currentAnimation2->Reset();

			currentAnimation2 = &idle;
			oneTouch_cura = true;
		}

		if (currentAnimation2->getNameAnimation() == "cura_die") {
			currentAnimation2->Reset();
			crearCura = true;
			curatimeWait.Start();
			if (pbody1 != nullptr) {
				pbody1->body->GetWorld()->DestroyBody(pbody1->body);
				pbody1 = nullptr;
			}
			playerTakeCura = false;
			currentAnimation2 = &start;
			oneTouch_cura = false;
			playerTouchBall = false;
		}
	}
	if (currentAnimation1->HasFinished())
	{
		if (currentAnimation1->getNameAnimation() == "ball_yellow_start") {
			currentAnimation1->Reset();
			currentAnimation1 = &ball_yellow_running;
			oneTouch = true;
		}

		if (currentAnimation1->getNameAnimation() == "ball_red_start") {
			ball_red_start.Reset();
			currentAnimation1 = &ball_red_running;
			oneTouch = true;
		}

		if (currentAnimation1->getNameAnimation() == "ball_blue_start") {
			currentAnimation1->Reset();
			currentAnimation1 = &ball_blue_running;
			oneTouch = true;
		}


		if (currentAnimation1->getNameAnimation() == "ball_yellow_end") {
			currentAnimation1->Reset();
			crearBall = true;
			CheckBallStarT(ballType);
			timeWait.Start();
			if (pbody != nullptr) {
				pbody->body->GetWorld()->DestroyBody(pbody->body);
				pbody = nullptr;
			}
			oneTouch = false;
			playerTouchBall = false;
		}

		if (currentAnimation1->getNameAnimation() == "ball_red_end") {
			currentAnimation1->Reset();
			crearBall = true;
			CheckBallStarT(ballType);
			timeWait.Start();
			if (pbody != nullptr) {
				pbody->body->GetWorld()->DestroyBody(pbody->body);
				pbody = nullptr;
			}
			oneTouch = false;
			playerTouchBall = false;
		}

		if (currentAnimation1->getNameAnimation() == "ball_blue_end") {
			currentAnimation1->Reset();
			crearBall = true;
			firstBall = false;
			CheckBallStarT(ballType);
			timeWait.Start();
			if (pbody != nullptr) {
				pbody->body->GetWorld()->DestroyBody(pbody->body);
				pbody = nullptr;
			}
			oneTouch = false;
			playerTouchBall = false;
		}


	}

}

void BossItem::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::PLAYER:
		if (physA->ctype == ColliderType::ENERGYBALL) {
			playerTouchBall = true;
			app->scene->GetAngel()->GetPoint(ballColor);
		}
		if (physA->ctype == ColliderType::ITEM) {
			if (playerTakeCura == false) {
				app->scene->GetPlayerLife()->playerGetHeal();
				playerTouchCura = true;
			}
			playerTakeCura = true;
		}
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

void BossItem::reLoadXML()
{
	pugi::xml_document configFile;
	ball_blue_texture_Path = parameters.child("boss_ball").child("ball_blue").attribute("texturepath").as_string();
	TSprite = parameters.child("boss_ball").child("ball_blue").attribute("Tsprite").as_int();
	SpriteX = parameters.child("boss_ball").child("ball_blue").attribute("x").as_int();
	SpriteY = parameters.child("boss_ball").child("ball_blue").attribute("y").as_int();
	PhotoWeight = parameters.child("boss_ball").child("ball_blue").attribute("Pweight").as_int();
	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);

	ball_blue_start.LoadAnim("BossItem", "ball_blue_start", spritePositions);
	ball_blue_running.LoadAnim("BossItem", "ball_blue_running", spritePositions);
	ball_blue_end.LoadAnim("BossItem", "ball_blue_end", spritePositions);

	ball_red_start.LoadAnim("BossItem", "ball_red_start", spritePositions);
	ball_red_running.LoadAnim("BossItem", "ball_red_running", spritePositions);
	ball_red_end.LoadAnim("BossItem", "ball_red_end", spritePositions);

	ball_yellow_start.LoadAnim("BossItem", "ball_yellow_start", spritePositions);
	ball_yellow_running.LoadAnim("BossItem", "ball_yellow_running", spritePositions);
	ball_yellow_end.LoadAnim("BossItem", "ball_yellow_end", spritePositions);

	cura_texture_Path = parameters.child("Cura").attribute("texturepath").as_string();
	TSprite = parameters.child("Cura").attribute("Tsprite").as_int();
	SpriteX = parameters.child("Cura").attribute("x").as_int();
	SpriteY = parameters.child("Cura").attribute("y").as_int();
	PhotoWeight = parameters.child("Cura").attribute("Pweight").as_int();
	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);
	idle.LoadAnim("cura", "cura_idle", spritePositions);
	die.LoadAnim("cura", "cura_die", spritePositions);
	start.LoadAnim("cura", "cura_start", spritePositions);
}
