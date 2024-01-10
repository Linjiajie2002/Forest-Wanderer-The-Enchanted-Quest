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

#include <tuple>
#include <cmath>

Item::Item() : Entity(EntityType::ITEM)
{
	name.Create("item");

}

Item::~Item() {}

bool Item::Awake() {

	DiamondPath = parameters.attribute("texturepath").as_string();
	TSprite = parameters.attribute("Tsprite").as_int();
	SpriteX = parameters.attribute("x").as_int();
	SpriteY = parameters.attribute("y").as_int();
	PhotoWeight = parameters.attribute("Pweight").as_int();


	position.x = parameters.attribute("Posx").as_int();
	position.y = parameters.attribute("Posy").as_int();

	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);
	idle.LoadAnim("Diamond", "idle", spritePositions);

	return true;
}

bool Item::Start() {
	//initilize textures
	Diamondtexture = app->tex->Load(DiamondPath);

	pbody = app->physics->CreateCircle(position.x + 16, position.y + 16, 16, bodyType::DYNAMIC);
	pbody->ctype = ColliderType::ITEM;

	currentAnimation = &idle;

	/*itemX[0] = 200.0;
	itemY[0] = 950.0;

	itemX[1] = 250.0;
	itemY[1] = 1050.0;

	itemX[2] = 350.0;
	itemY[2] = 1100.0;

	itemX[3] = 450.0;
	itemY[3] = 1050.0;

	itemX[4] = 500.0;
	itemY[4] = 950.0;

	itemX[5] = 450.0;
	itemY[5] = 850.0;

	itemX[6] = 350.0;
	itemY[6] = 800.0;

	itemX[7] = 250.0;
	itemY[7] = 850.0;*/



	for (int i = 0; i < NumeroDiamante; i++)
	{
		itemX[i] = circleCenterX-150;
		itemY[i] = circleCenterY;
	}
	maxDiamante = 0;

	return true;
}

bool Item::Update(float dt)
{
	rect = currentAnimation->GetCurrentFrame();
	currentAnimation = &idle;

	if (TimeCrear.ReadMSec() > 850) {
		if (maxDiamante < NumeroDiamante) {
			maxDiamante++;
			TimeCrear.Start();
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN) {
		DMT = true;
	}



	if (DMT == true) {
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




	currentAnimation->Update();



	//printf("PosX: %d ", position.x);
	//printf("\nPosY: %d ", position.y);

	return true;
}


bool Item::CleanUp()
{
	return true;
}

void Item::rotateAroundCircle(double& x, double& y, double circleCenterX, double circleCenterY,  double angleIncrement)
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
		app->render->DrawTexture(Diamondtexture, x-32, y-32, 4, SDL_FLIP_NONE, &rect);
	}
	else {
		app->render->DrawTexture(Diamondtexture, x, y, 2, SDL_FLIP_NONE, &rect);
	}

}
