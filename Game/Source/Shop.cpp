#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "Shop.h"

Shop::Shop() : Entity(EntityType::ITEM)
{
	name.Create("shop");
}

Shop::~Shop() {}

bool Shop::Awake() {
	//ShopPath = parameters.attribute("texturepath").as_string();
	//position.x = parameters.attribute("Posx").as_int();
	//position.y = parameters.attribute("Posy").as_int();

	//TSprite = parameters.attribute("Tsprite").as_int();
	//SpriteX = parameters.attribute("x").as_int();
	//SpriteY = parameters.attribute("y").as_int();
	//PhotoWeight = parameters.attribute("Pweight").as_int();

	//spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);

	//idle.LoadAnim("Shop", "idle", spritePositions);

	return true;
}

bool Shop::Start() {

	////initilize textures

	//Shoptexture = app->tex->Load(ShopPath);
	//pbody = app->physics->CreateRectangleSensor(position.x + 110, position.y + 155, 162, 133, bodyType::STATIC);
	////pbody = app->physics->CreateCircle(position.x + 16, position.y + 16, 16, bodyType::STATIC);
	//pbody->ctype = ColliderType::SHOP;
	//pbody->body->SetFixedRotation(true);

	//currentAnimation = &idle;
	if (app->scene->changeScena) {
		Awake();
	}


	return true;
}

bool Shop::Update(float dt)
{

	
	


	//SDL_Rect rect = currentAnimation->GetCurrentFrame();

	//currentAnimation = &idle;

	//app->render->DrawTexture(Shoptexture, position.x, position.y, 1.8 , SDL_FLIP_NONE,&rect);
	//currentAnimation->Update();
	return true;
}

bool Shop::CleanUp()
{
	return true;
}