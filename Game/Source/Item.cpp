#include "Item.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "Timer.h"
#include "Map.h"

#include <stdio.h>
#include <tuple>
#include <cmath>
#include <vector>
#include <string>

Item::Item() : Entity(EntityType::ITEM)
{
	name.Create("item");

}

Item::~Item() {}

bool Item::Awake() {

	//DiamondPath = parameters.child("Diamond").attribute("texturepath").as_string();
	//TSprite = parameters.child("Diamond").attribute("Tsprite").as_int();
	//SpriteX = parameters.child("Diamond").attribute("x").as_int();
	//SpriteY = parameters.child("Diamond").attribute("y").as_int();
	//PhotoWeight = parameters.child("Diamond").attribute("Pweight").as_int();

	//spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);
	//idle.LoadAnim("Diamond", "idle", spritePositions);

	////position.x = parameters.attribute("Posx").as_int();
	////position.y = parameters.attribute("Posy").as_int();

	//Diamond_Counter_texture_Path = parameters.child("Diamond_Counter").attribute("texturepath").as_string();
	//TSprite = parameters.child("Diamond_Counter").attribute("Tsprite").as_int();
	//SpriteX = parameters.child("Diamond_Counter").attribute("x").as_int();
	//SpriteY = parameters.child("Diamond_Counter").attribute("y").as_int();
	//PhotoWeight = parameters.child("Diamond_Counter").attribute("Pweight").as_int();
	//spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);

	///*std::string counterString = "Diamond_Counter_" + std::to_string(1);
	//Diamond_Counter[1].LoadAnim("Diamond", counterString.c_str(), spritePositions);*/

	//for (int i = 0; i < 9; i++)
	//{
	//	std::string counterString = "Diamond_Counter_" + std::to_string(i);
	//	Diamond_Counter.Add(inicializaAnimation);
	//	Diamond_Counter[i].LoadAnim("Diamond", counterString.c_str(), spritePositions);
	//}


	return true;
}

bool Item::Start() {
	//initilize textures


	reLoadXML();
	Diamondtexture = app->tex->Load(DiamondPath);
	Diamond_Counter_texture = app->tex->Load(Diamond_Counter_texture_Path);



	/*pbody = app->physics->CreateCircle(position.x + 16, position.y + 16, 16, bodyType::DYNAMIC);
	pbody->ctype = ColliderType::ITEM;*/

	currentAnimation = &idle;
	currentAnimation2 = &idle;
	for (int i = 0; i < 9; i++)
	{
		currentAnimation1.Add(&Diamond_Counter[i]);
		rect_1.Add(currentAnimation1[i]->GetCurrentFrame());

	}




	for (int i = 0; i < NumeroDiamante; i++)
	{
		itemX[i] = circleCenterX - 150;
		itemY[i] = circleCenterY;
	}
	maxDiamante = 0;

	return true;
}

bool Item::Update(float dt)
{

	if (playerGetDiamante == 7) {
		victoria = true;
	}

	if (victoria) {
		GoCenterTime_determination = true;
		app->scene->GetAngel()->Enter = true;
		app->scene->GetBoss()->inBossBattle = false;
		diamanteVictoria();
	}



	for (int i = 0; i < playerGetDiamante + 2; i++)
	{
		rect_1[i] = currentAnimation1[i]->GetCurrentFrame();
		app->render->DrawTexture(Diamond_Counter_texture, 416, app->scene->GetPlayerLife()->lifePos_Y - 44, 2, SDL_FLIP_NONE, &rect_1[i], 0, 0);
		currentAnimation1[i]->Update();
	}



	if (app->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN) {

		if (playerGetDiamante != 7)playerGetDiamante++;
		//DiamanteToCenter = true;
	}

	rect = currentAnimation->GetCurrentFrame();
	currentAnimation->Update();

	


	//printf("PosX: %d ", position.x);
	//printf("\nPosY: %d ", position.y);

	return true;
}


bool Item::CleanUp()
{
	if (pbody != nullptr) {
		app->physics->GetWorld()->DestroyBody(pbody->body);
	}
	if (Diamondtexture) {
		SDL_DestroyTexture(Diamondtexture);
		Diamondtexture = nullptr;
	}

	if (Diamond_Counter_texture) {
		SDL_DestroyTexture(Diamond_Counter_texture);
		Diamond_Counter_texture = nullptr;
	}
	return true;
}

void Item::diamanteVictoria()
{

	if (GoCenter.ReadMSec() > 15000) {
		DiamanteToCenter = true;
	}


	if (TimeCrear.ReadMSec() > 850) {
		if (maxDiamante < NumeroDiamante) {
			maxDiamante++;
			TimeCrear.Start();
		}
	}

	if (DiamanteToCenter == true) {
		for (int i = 0; i < maxDiamante; i++)
		{


			diamanteToCenter(itemX[i], itemY[i]);
		}

	}
	else {
		for (int i = 0; i < maxDiamante; i++)
		{
			rotateAroundCircle(itemX[i], itemY[i], circleCenterX, circleCenterY, angleIncrement);
		}
	}
}

void Item::rotateAroundCircle(double& x, double& y, double circleCenterX, double circleCenterY, double angleIncrement)
{

	double angleInRadians = angleIncrement * M_PI / 180.0;

	double newX = circleCenterX + (x - circleCenterX) * cos(angleInRadians) - (y - circleCenterY) * sin(angleInRadians);
	double newY = circleCenterY + (x - circleCenterX) * sin(angleInRadians) + (y - circleCenterY) * cos(angleInRadians);


	x = newX;
	y = newY;

	//printf("PosX: %f ", circleRadius);

	app->render->DrawTexture(Diamondtexture, newX, newY, 2, SDL_FLIP_NONE, &rect);

	//return std::make_tuple(newX, newY);
}

void Item::DestroyedDiamante()
{
	GoCenter.Start();
	playerTakeDiamante = true;
}

void Item::diamanteToCenter(double& x, double& y)
{

	float timeLerp = 0.1f;

	x = x * (1 - timeLerp) + circleCenterX * timeLerp;
	y = y * (1 - timeLerp) + circleCenterY * timeLerp;

	if ((int)x == circleCenterX && (int)y == circleCenterY) {
		allDiamanteInCenter = true;
	}


	if (allDiamanteInCenter) {
		app->render->DrawTexture(Diamondtexture, x - 32, y - 32, 4, SDL_FLIP_NONE, &rect);
	}
	else {
		app->render->DrawTexture(Diamondtexture, x, y, 2, SDL_FLIP_NONE, &rect);
	}



}

void Item::LastDiamante()
{
	app->scene->GetEffect()->LastEffect();
	if (app->scene->GetEffect()->currentAnimation3->HasFinished() && lastDiamenteIsCreat) {
		rect_2 = currentAnimation2->GetCurrentFrame();

		currentAnimation2->Update();

		pbody = app->physics->CreateCircle(1915 + 32, 765 + 32, 28, bodyType::DYNAMIC);
		pbody->ctype = ColliderType::ITEM;
		pbody->body->SetFixedRotation(true);
		pbody->listener = this;
		lastDiamenteIsCreat = false;
	}


	if (pbody != nullptr && playerTakeDiamante == false) {
		pbody->body->SetLinearVelocity(b2Vec2(0, pbody->body->GetLinearVelocity().y - GRAVITY_Y));
		position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 30;
		position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 30;
	}

	if (!playerTakeDiamante) {
		app->render->DrawTexture(Diamondtexture, position.x, position.y, 2, SDL_FLIP_NONE, &rect_2);
	}
	else {
		if (pbody != nullptr) {

			pbody->body->GetWorld()->DestroyBody(pbody->body);
			pbody = nullptr;
		}

	}

}

void Item::playerIsGetDiamante()
{
	if (playerGetDiamante != 7)playerGetDiamante++;
}



void Item::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::PLAYER:
		DestroyedDiamante();
		playerIsGetDiamante();
		break;
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}

void Item::reLoadXML()
{
	pugi::xml_document configFile;

	DiamondPath = parameters.child("Diamond").attribute("texturepath").as_string();
	TSprite = parameters.child("Diamond").attribute("Tsprite").as_int();
	SpriteX = parameters.child("Diamond").attribute("x").as_int();
	SpriteY = parameters.child("Diamond").attribute("y").as_int();
	PhotoWeight = parameters.child("Diamond").attribute("Pweight").as_int();

	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);
	idle.LoadAnim("Diamond", "idle", spritePositions);

	//position.x = parameters.attribute("Posx").as_int();
	//position.y = parameters.attribute("Posy").as_int();

	Diamond_Counter_texture_Path = parameters.child("Diamond_Counter").attribute("texturepath").as_string();
	TSprite = parameters.child("Diamond_Counter").attribute("Tsprite").as_int();
	SpriteX = parameters.child("Diamond_Counter").attribute("x").as_int();
	SpriteY = parameters.child("Diamond_Counter").attribute("y").as_int();
	PhotoWeight = parameters.child("Diamond_Counter").attribute("Pweight").as_int();
	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);

	/*std::string counterString = "Diamond_Counter_" + std::to_string(1);
	Diamond_Counter[1].LoadAnim("Diamond", counterString.c_str(), spritePositions);*/

	for (int i = 0; i < 9; i++)
	{
		std::string counterString = "Diamond_Counter_" + std::to_string(i);
		Diamond_Counter.Add(inicializaAnimation);
		Diamond_Counter[i].LoadAnim("Diamond", counterString.c_str(), spritePositions);
	}
}
