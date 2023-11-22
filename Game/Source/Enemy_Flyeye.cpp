#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "Enemy_Flyeye.h"

Enemy_Flyeye::Enemy_Flyeye() : Entity(EntityType::ENEMY_FLYEYE)
{
	name.Create("enemy");
}

Enemy_Flyeye::~Enemy_Flyeye() {}

bool Enemy_Flyeye::Awake() {

	//EnemyPath = parameters.child("Enemy_Goblin").attribute("texturepath").as_string();
	//TSprite = parameters.child("Enemy_Goblin").attribute("Tsprite").as_int();
	//SpriteX = parameters.child("Enemy_Goblin").attribute("x").as_int();
	//SpriteY = parameters.child("Enemy_Goblin").attribute("y").as_int();
	//PhotoWeight = parameters.child("Enemy_Goblin").attribute("Pweight").as_int();
	//spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);

	//idle.LoadAnim("Enemy_Goblin", "idle", spritePositions);
	//run.LoadAnim("Enemy_Goblin", "run", spritePositions);
	//take_hit.LoadAnim("Enemy_Goblin", "take_hit", spritePositions);
	//die.LoadAnim("Enemy_Goblin", "die", spritePositions);
	//atack.LoadAnim("Enemy_Goblin", "atake", spritePositions);


	return true;
}

bool Enemy_Flyeye::Start() {

	////initilize textures
	//Shoptexture = app->tex->Load(ShopPath);
	//pbody = app->physics->CreateRectangleSensor(position.x + 110, position.y + 155, 162, 133, bodyType::STATIC);
	////pbody = app->physics->CreateCircle(position.x + 16, position.y + 16, 16, bodyType::STATIC);
	//pbody->ctype = ColliderType::SHOP;
	//pbody->body->SetFixedRotation(true);

	//currentAnimation = &idle;



	return true;
}

bool Enemy_Flyeye::Update(float dt)
{
	//SDL_Rect rect = currentAnimation->GetCurrentFrame();

	//currentAnimation = &idle;

	//app->render->DrawTexture(Shoptexture, position.x, position.y, 1.8, SDL_FLIP_NONE, &rect);
	//currentAnimation->Update();
	return true;
}

bool Enemy_Flyeye::CleanUp()
{
	return true;
}