#ifndef __ITEM_H__
#define __ITEM_H__

#include "Entity.h"
#include "Point.h"
#include "Animation.h"
#include <cmath>
#include <tuple>
#include "SDL/include/SDL.h"

struct SDL_Texture;

class Item : public Entity
{
public:

	Item();
	virtual ~Item();

	bool Awake();

	bool Start();

	bool Update(float dt);

	bool CleanUp();

	std::tuple<double, double> rotateAroundCircle(double& x, double& y, double circleCenterX, double circleCenterY, double circleRadius, double angleIncrement);
	std::tuple<double, double> rotateAroundCircle(double& x, double& y, double circleCenterX, double circleCenterY, double& circleRadius, double angleIncrement, double scaleFactor);

public:

	bool isPicked = false;
	Animation* currentAnimation = nullptr;
	Animation idle;
	Animation SPosition;
	SDL_Rect* spritePositions;

	int TSprite;
	int SpriteX;
	int SpriteY;
	int PhotoWeight;


	double itemX = 150.0;  // 物品初始X坐标
	double itemY = 950.0;  // 物品初始Y坐标
	double circleCenterX = 350.0;  // 圆心X坐标
	double circleCenterY = 950.0;  // 圆心Y坐标
	double circleRadius = 20.1;  // 圆半径
	double angleIncrement =5.0;  // 每次旋转的角度增量
	double scaleFactor = 10.0;

	int grado =30;

private:

	SDL_Texture* Diamondtexture;
	const char* DiamondPath;
	PhysBody* pbody;
};
#endif // __ITEM_H__