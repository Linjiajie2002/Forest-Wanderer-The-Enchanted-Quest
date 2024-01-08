#ifndef __ITEM_H__
#define __ITEM_H__

#include "Entity.h"
#include "Point.h"
#include "Animation.h"
#include <cmath>
#include <tuple>
#include "SDL/include/SDL.h"
#include "Timer.h"

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

	void rotateAroundCircle(double& x, double& y, double circleCenterX, double circleCenterY, double circleRadius, double angleIncrement);
	void diamanteToCenter(double& x, double& y);

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


	//double itemX = 150.0;  // 物品初始X坐标
	//double itemY = 950.0;  // 物品初始Y坐标
	double circleCenterX = 350.0;  // 圆心X坐标
	double circleCenterY = 950.0;  // 圆心Y坐标
	double circleRadius = 20.0;  // 圆半径
	double angleIncrement = 1.0;  // 每次旋转的角度增量
	double scaleFactor = 10.0;

	double itemX[8];      // 物品初始X坐标
	double itemY[8];

	int NumeroDiamante = 7;
	int maxDiamante = 0;
	double angleInRadians;
	double newX;
	double newY;

	double newCX;
	double newCY;

	bool DMT = false;

	bool allDiamanteInCenter = false;

	Timer TimeCrear;
	Timer diamanteToBig;
	bool hecreado7diamante = false;

	SDL_Rect rect;

private:

	SDL_Texture* Diamondtexture;
	const char* DiamondPath;
	PhysBody* pbody;
};
#endif // __ITEM_H__