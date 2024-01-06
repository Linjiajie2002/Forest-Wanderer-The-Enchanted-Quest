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

	for (int i = 0; i < ND; i++)
	{
		itemX[i] = 150.0;
		itemY[i] = 950.0;
	}

	return true;
}

bool Item::Update(float dt)
{
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	currentAnimation = &idle;


	/*if (TimeCrear.ReadSec() > 2) {
		TimeCrear.Start();

	}*/

	/*auto newPosition = rotateAroundCircle(itemX, itemY, circleCenterX, circleCenterY, circleRadius--, angleIncrement);
	double newX = std::get<0>(newPosition);
	double newY = std::get<1>(newPosition);
	app->render->DrawTexture(Diamondtexture, newX, newY, 2, SDL_FLIP_NONE, &rect);*/


	for (int i = 0; i < ND; )
	{
		auto newPosition = rotateAroundCircle(itemX[i], itemY[i], circleCenterX, circleCenterY, circleRadius, angleIncrement);
		newX = std::get<0>(newPosition);
		newY = std::get<1>(newPosition);
		app->render->DrawTexture(Diamondtexture, newX, newY, 2, SDL_FLIP_NONE, &rect);

		if (TimeCrear.ReadSec() > 1) {
			i++;
		}

	}

	/*
	if (TimeCrear.ReadSec() > 1) {
		auto newPosition1 = rotateAroundCircle(itemX2, itemY2, circleCenterX, circleCenterY, circleRadius, angleIncrement);
		newX = std::get<0>(newPosition1);
		newY = std::get<1>(newPosition1);
		app->render->DrawTexture(Diamondtexture, newX, newY, 2, SDL_FLIP_NONE, &rect);
	}*/


	//printf("%d", TimeCrear.ReadSec());



	currentAnimation->Update();

	/*printf("PosX: %f ", newX);
	printf("\nPosY: %f ", newY);*/

	//printf("PosX: %d ", position.x);
	//printf("\nPosY: %d ", position.y);

	return true;
}


bool Item::CleanUp()
{
	return true;
}

//std::tuple<double, double>  Item::rotateAroundCircle(double& x, double& y, double circleCenterX, double circleCenterY, double& circleRadius, double angleIncrement, double scaleFactor) 
//{
//	double angleInRadians = angleIncrement * M_PI / 180.0;
//
//	// 缩放到期望的圈大小
//	double scaledX = (x - circleCenterX) / circleRadius * scaleFactor + circleCenterX;
//	double scaledY = (y - circleCenterY) / circleRadius * scaleFactor + circleCenterY;
//
//	// 计算新的位置
//	double newX = circleCenterX + (scaledX - circleCenterX) * cos(angleInRadians) - (scaledY - circleCenterY) * sin(angleInRadians);
//	double newY = circleCenterY + (scaledX - circleCenterX) * sin(angleInRadians) + (scaledY - circleCenterY) * cos(angleInRadians);
//
//	// 更新物品的位置
//	x = newX;
//	y = newY;
//
//	// 逐渐减小圆的半径
//	circleRadius -= 0.1;
//
//	return std::make_tuple(newX, newY);
//}



std::tuple<double, double>  Item::rotateAroundCircle(double& x, double& y, double circleCenterX, double circleCenterY, double circleRadius, double angleIncrement)
{
	double angleInRadians = angleIncrement * M_PI / 180.0;


	// 计算新的位置
	double newX = circleCenterX + (x - circleCenterX) * cos(angleInRadians) - (y - circleCenterY) * sin(angleInRadians);
	double newY = circleCenterY + (x - circleCenterX) * sin(angleInRadians) + (y - circleCenterY) * cos(angleInRadians);

	// 更新物品的位置
	x = newX;
	y = newY;

	//printf("PosX: %f ", circleRadius);

	return std::make_tuple(newX, newY);
}
