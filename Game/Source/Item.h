#ifndef __ITEM_H__
#define __ITEM_H__

#include "Entity.h"
#include "Point.h"
#include "Animation.h"
#include <cmath>
#include <tuple>
#include "SDL/include/SDL.h"
#include "Timer.h"

#include "List.h"

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

	void diamanteVictoria();
	void rotateAroundCircle(double& x, double& y, double circleCenterX, double circleCenterY, double angleIncrement);
	void DestroyedDiamante();
	void diamanteToCenter(double& x, double& y);
	void LastDiamante();
	void playerIsGetDiamante();
	void OnCollision(PhysBody* physA, PhysBody* physB);
	void reLoadXML();

public:

	bool isPicked = false;
	Animation* currentAnimation = nullptr;
	Animation* currentAnimation2 = nullptr;

	List<Animation*> currentAnimation1;
	 
	Animation idle;
	List<Animation> Diamond_Counter;

	Animation inicializaAnimation;
	Animation SPosition;
	SDL_Rect* spritePositions;

	int TSprite;
	int SpriteX;
	int SpriteY;
	int PhotoWeight;


	double itemX[8];      
	double itemY[8];
	double circleCenterX = 1920.0;  
	double circleCenterY = 900.0;  
	double angleIncrement = 1.0;  


	int NumeroDiamante = 7;
	int maxDiamante = 0;

	double angleInRadians;
	double newX;
	double newY;

	double newCX;
	double newCY;

	bool DiamanteToCenter = false;
	bool allDiamanteInCenter = false;
	bool outCamera = false;
	bool victoria = false;
	bool lastDiamenteIsCreat = true;
	bool playerTakeDiamante = false;
	

	Timer TimeCrear;
	Timer diamanteToBig;
	Timer GoCenter;
	bool hecreado7diamante = false;

	bool GoCenterTime_determination;
	int playerGetDiamante = 0;

	SDL_Rect rect;
	SDL_Rect rect_2;
	List<SDL_Rect> rect_1;

private:

	SDL_Texture* Diamondtexture;
	const char* DiamondPath;

	SDL_Texture* Diamond_Counter_texture;
	const char* Diamond_Counter_texture_Path;
	PhysBody* pbody;
};
#endif // __ITEM_H__