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

	if (app->scene->changeScena) {
		reLoadXML(app->scene->nodeinfo(EntityType::BOSS));
	}
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

	if (atackTouch && app->scene->GetPlayerLife()->playerTakeBossDmg == false) {
		app->scene->GetPlayerLife()->playerGetHit();
		atackTouch = false;
	}

	if (app->scene->GetItem()->playerGetDiamante == 6 && inBossBattle == false && !app->scene->GetPlayer()->isDead && !app->scene->GetItem()->victoria) {
		printf("1111");
		goBossBattle();
	}


	if (app->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN) {
		app->scene->GetAngel()->Enter = true;
		inBossBattle = true;
		tpToinBossBattle = true;
		app->scene->GetItem()->victoria = false;
	}

	if (app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN) {
		getPlayerPosition = true;
		attackMethod = 1;
	}

	if (app->input->GetKey(SDL_SCANCODE_V) == KEY_DOWN) {
		inBossBattle = false;
		app->scene->GetItem()->victoria = true;

	}


	if (inBossBattle && attackMethod == 1) {
		if (getPlayerPosition) {
			player_x = app->scene->GetPlayer()->position.x;
			getPlayerPosition = false;
			atack1_Collision.Start();
		}
		crearCollision = true;
		boss_atack_1(player_x);
	}

	if (currentAnimation1->HasFinished()) {
		getPlayerPosition = true;
		atack_1.Reset();
		attackMethod = 2;
		if (pbody != nullptr) {
			pbody->body->GetWorld()->DestroyBody(pbody->body);
			pbody = nullptr;
		}
		app->scene->GetPlayerLife()->playerTakeBossDmg = false;

	}


	if (inBossBattle && attackMethod == 2) {

		if (getPlayerPosition) {
			player_x = app->scene->GetPlayer()->position.x;
			getPlayerPosition = false;
			atack1_Collision.Start();
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
				crearCollision = true;
				aumentaDistanciaColison = aumentaDistanciaColison_suport * 195;
				aumentaDistanciaColison_suport++;

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


	if (currentAnimation2[numeroAtack - 1]->HasFinished() && allPrint) {
		getPlayerPosition = true;
		for (int i = 0; i < numeroAtack; i++)
		{
			atack_2[i].Reset();


		}

		for (auto& body : physBodies) {
			if (body != nullptr) {
				body->body->GetWorld()->DestroyBody(body->body);
				delete body;
				body = nullptr;

			}
		}

		physBodies.clear();

		app->scene->GetPlayerLife()->playerTakeBossDmg = false;
		aumentaDistanciaColison = 0;
		aumentaDistanciaColison_suport = 0;
		maxNumAtack = 0;
		attackMethod = 3;


	}


	if (inBossBattle && attackMethod == 3) {
		if (getPlayerPosition) {
			player_x = app->scene->GetPlayer()->position.x;
			getPlayerPosition = false;
			atack1_Collision.Start();
		}
		crearCollision = true;
		boss_atack_3(direction_Atack);
		

	}


	if (currentAnimation3->HasFinished()) {
		atack_3.Reset();
		attackMethod = 4;
		currentAnimation4 = &atack_4_start;

		if (pbody != nullptr) {
			pbody->body->GetWorld()->DestroyBody(pbody->body);
			pbody = nullptr;
		}
		app->scene->GetPlayerLife()->playerTakeBossDmg = false;
	}


	if (inBossBattle && attackMethod == 4) {

		crearCollision = true;
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
			atack4_posX_R = 1420;
			atack4_posX_L = 2290;
			if (pbody != nullptr) {
				pbody->body->GetWorld()->DestroyBody(pbody->body);
				pbody = nullptr;
			}
			app->scene->GetPlayerLife()->playerTakeBossDmg = false;
		}
	}

	return true;
}

bool Boss::CleanUp()
{
	SDL_DestroyTexture(boss_atack_1_texture);
	SDL_DestroyTexture(boss_atack_2_texture);
	SDL_DestroyTexture(boss_atack_3_texture);
	SDL_DestroyTexture(boss_atack_4_texture);

	return true;
}

void Boss::boss_atack_1(int player_x)
{

	if (player_x != 0 && player_x > 1300) {
		//printf("\n%d ", player_x);
		rect_1 = currentAnimation1->GetCurrentFrame();
		app->render->DrawTexture(boss_atack_1_texture, player_x - 200, 590, 1, SDL_FLIP_NONE, &rect_1);
		currentAnimation1->Update();
		if (atack1_Collision.ReadMSec() >= 1000) {
			if (pbody == nullptr && crearCollision) {
				pbody = app->physics->CreateRectangleSensor(player_x + 50, 1080, 300, 150, bodyType::STATIC);
				pbody->ctype = ColliderType::BOSSATACK;
				pbody->body->SetFixedRotation(true);
				pbody->listener = this;
				crearCollision = false;
			}
		}
	}

}

void Boss::boss_atack_2(bool inversaAtack, int numberAtack)
{

	distancia = 200 * numberAtack;

	rect_2[numberAtack] = currentAnimation2[numberAtack]->GetCurrentFrame();
	if (inversaAtack) {
		app->render->DrawTexture(boss_atack_2_texture, 2150 - distancia, 400, 1.5, SDL_FLIP_NONE, &rect_2[numberAtack]);


		if (crearCollision) {
			pbody2 = app->physics->CreateRectangleSensor(2380 - aumentaDistanciaColison, 900 - atack2_posY, 150, 200, bodyType::DYNAMIC);
			pbody2->ctype = ColliderType::BOSSATACK;
			pbody2->body->SetFixedRotation(true);
			pbody2->listener = this;
			crearCollision = false;
			physBodies.push_back(pbody2);
		
			
			physBodiesWithTimers.emplace_back(pbody2);
		}

		for (auto& physBodyWithTimer : physBodiesWithTimers) {
			if (physBodyWithTimer.pbody2 != nullptr) {
				// Verifica si ha pasado suficiente tiempo desde la creaci¨®n
				if (physBodyWithTimer.timer.ReadMSec() >= 850) {
					physBodyWithTimer.pbody2->body->SetLinearVelocity(b2Vec2(0, 50));
				}
			}
		}


	}
	else {
		app->render->DrawTexture(boss_atack_2_texture, 1250 + distancia, 400, 1.5, SDL_FLIP_NONE, &rect_2[numberAtack]);

		if (crearCollision) {
			pbody2 = app->physics->CreateRectangleSensor(1500 + aumentaDistanciaColison, 900 - atack2_posY, 150, 200, bodyType::DYNAMIC);
			pbody2->ctype = ColliderType::BOSSATACK;
			pbody2->body->SetFixedRotation(true);
			pbody2->listener = this;
			crearCollision = false;
			physBodies.push_back(pbody2);

			physBodiesWithTimers.emplace_back(pbody2);
		}

		for (auto& physBodyWithTimer : physBodiesWithTimers) {
			if (physBodyWithTimer.pbody2 != nullptr) {
				// Verifica si ha pasado suficiente tiempo desde la creaci¨®n
				if (physBodyWithTimer.timer.ReadMSec() >= 850) {
					physBodyWithTimer.pbody2->body->SetLinearVelocity(b2Vec2(0, 50));
				}
			}
		}

	}
	currentAnimation2[numberAtack]->Update();
}

void Boss::boss_atack_3(bool inversaAtack)
{
	rect_3 = currentAnimation3->GetCurrentFrame();
	if (inversaAtack) {
		app->render->DrawTexture(boss_atack_3_texture, 1350, 660, 2, SDL_FLIP_NONE, &rect_3);
		
		if (atack1_Collision.ReadMSec() >= 1200) {
		
			if (pbody == nullptr && crearCollision) {
				pbody = app->physics->CreateRectangleSensor(1870, 1000, 150, 300, bodyType::STATIC);
				pbody->ctype = ColliderType::BOSSATACK;
				pbody->body->SetFixedRotation(true);
				pbody->listener = this;
				crearCollision = false;

			}
		}
	}
	else {

		if (atack1_Collision.ReadMSec() >= 1200) {
			if (pbody == nullptr && crearCollision) {
				pbody = app->physics->CreateRectangleSensor(2000, 1000, 150, 300, bodyType::STATIC);
				pbody->ctype = ColliderType::BOSSATACK;
				pbody->body->SetFixedRotation(true);
				pbody->listener = this;
				crearCollision = false;
			}
		}
		app->render->DrawTexture(boss_atack_3_texture, 1750, 660, 2, SDL_FLIP_HORIZONTAL, &rect_3);

	}
	currentAnimation3->Update();
}

void Boss::boss_atack_4(bool inversaAtack)
{
	rect_4 = currentAnimation4->GetCurrentFrame();



	if (inversaAtack) {


		if (currentAnimation4->getNameAnimation() == "atack_4_running") {
			if (pbody != nullptr) {
				pbody->body->SetLinearVelocity(b2Vec2(8, 0));
				atack4_posX_R = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 90;

			}
		}

		if (pbody == nullptr && crearCollision) {
			pbody = app->physics->CreateTriangleSensor(atack4_posX_R + 100, 1010, 150, bodyType::DYNAMIC);
			pbody->ctype = ColliderType::BOSSATACK;
			pbody->body->SetFixedRotation(true);
			pbody->listener = this;
			crearCollision = false;
		}

		app->render->DrawTexture(boss_atack_4_texture, atack4_posX_R, 1010, 0.7, SDL_FLIP_NONE, &rect_4);

		if (atack4_posX_R >= atack4_posX_L) {
			currentAnimation4 = &atack_4_end;
		}

	}
	else {
		/*atack4_posX = atack4_posX_L - velocitat;
		app->render->DrawTexture(boss_atack_4_texture, atack4_posX, 1010, 0.7, SDL_FLIP_NONE, &rect_4);
		if (atack4_posX <= atack4_posX_R) {
			currentAnimation4 = &atack_4_end;
		}

		if (atack1_Collision.ReadMSec() >= 1200) {
			if (pbody == nullptr && crearCollision) {
				pbody = app->physics->CreateTriangleSensor(atack4_posX, 1025, 150, bodyType::DYNAMIC);
				pbody->ctype = ColliderType::BOSSATACK;
				pbody->body->SetFixedRotation(true);
				pbody->listener = this;
				crearCollision = false;
			}
		}*/
		if (currentAnimation4->getNameAnimation() == "atack_4_running") {
			if (pbody != nullptr) {
				pbody->body->SetLinearVelocity(b2Vec2(-8, 0));
				atack4_posX_L = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 90;

			}
		}

		if (pbody == nullptr && crearCollision) {
			pbody = app->physics->CreateTriangleSensor(atack4_posX_L + 100, 1010, 150, bodyType::DYNAMIC);
			pbody->ctype = ColliderType::BOSSATACK;
			pbody->body->SetFixedRotation(true);
			pbody->listener = this;
			crearCollision = false;
		}

		app->render->DrawTexture(boss_atack_4_texture, atack4_posX_L, 1010, 0.7, SDL_FLIP_NONE, &rect_4);

		if (atack4_posX_L <= atack4_posX_R) {
			currentAnimation4 = &atack_4_end;
		}


	}

	currentAnimation4->Update();

}

void Boss::goBossBattle()
{
	app->scene->GetAngel()->Enter = true;
	inBossBattle = true;
	tpToinBossBattle = true;
	app->scene->GetItem()->victoria = false;
}



void Boss::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::PLAYER:
		atackTouch = true;
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
		atackTouch = false;
		break;


	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}

void Boss::reLoadXML(pugi::xml_node& parameters)
{
	pugi::xml_document configFile;

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
}
