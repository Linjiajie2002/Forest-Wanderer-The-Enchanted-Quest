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


	Diamond_Counter.Add(inicializaAnimation);
	Diamond_Counter[0].LoadAnim("Diamond", "Diamond_Counter_1", spritePositions);
	Diamond_Counter.Add(inicializaAnimation);
	Diamond_Counter[1].LoadAnim("Diamond", "Diamond_Counter_2", spritePositions);
	Diamond_Counter.Add(inicializaAnimation);
	Diamond_Counter[2].LoadAnim("Diamond", "Diamond_Counter_3", spritePositions);
	Diamond_Counter.Add(inicializaAnimation);
	Diamond_Counter[3].LoadAnim("Diamond", "Diamond_Counter_4", spritePositions);
	Diamond_Counter.Add(inicializaAnimation);
	Diamond_Counter[4].LoadAnim("Diamond", "Diamond_Counter_5", spritePositions);
	Diamond_Counter.Add(inicializaAnimation);
	Diamond_Counter[5].LoadAnim("Diamond", "Diamond_Counter_6", spritePositions);
	Diamond_Counter.Add(inicializaAnimation);
	Diamond_Counter[6].LoadAnim("Diamond", "Diamond_Counter_7", spritePositions);
	Diamond_Counter.Add(inicializaAnimation);
	Diamond_Counter[7].LoadAnim("Diamond", "Diamond_Counter_8", spritePositions);

	return true;
}

bool Item::Start() {
	//initilize textures
	Diamondtexture = app->tex->Load(DiamondPath);
	Diamond_Counter_texture = app->tex->Load(Diamond_Counter_texture_Path);

	pbody = app->physics->CreateCircle(position.x + 16, position.y + 16, 16, bodyType::DYNAMIC);
	pbody->ctype = ColliderType::ITEM;

	currentAnimation = &idle;

	for (int i = 0; i < 8; i++)
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
		
		diamanteVictoria();
	}

	

	for (int i = 0; i < playerGetDiamante + 1; i++)
	{
		rect_1[i] = currentAnimation1[i]->GetCurrentFrame();
		app->render->DrawTexture(Diamond_Counter_texture, 416, app->scene->GetPlayerLife()->lifePos_Y - 44, 2, SDL_FLIP_NONE, &rect_1[i], 0, 0);
		currentAnimation1[i]->Update();
	}



	if (app->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN) {
		playerGetDiamante++;
	}

	rect = currentAnimation->GetCurrentFrame();
	currentAnimation->Update();
	

	//printf("PosX: %d ", position.x);
	//printf("\nPosY: %d ", position.y);

	return true;
}


bool Item::CleanUp()
{
	return true;
}

void Item::diamanteVictoria()
{
	
	

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
			DiamanteToCenter = true;
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
