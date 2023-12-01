#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "Enemy_Goblin.h"

Enemy_Goblin::Enemy_Goblin() : Entity(EntityType::ENEMY_GOBLIN)
{
	name.Create("enemy");
}

Enemy_Goblin::~Enemy_Goblin() {}

bool Enemy_Goblin::Awake() {

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

bool Enemy_Goblin::Start() {



	////initilize textures
	//Shoptexture = app->tex->Load(ShopPath);
	//pbody = app->physics->CreateRectangleSensor(position.x + 110, position.y + 155, 162, 133, bodyType::STATIC);
	////pbody = app->physics->CreateCircle(position.x + 16, position.y + 16, 16, bodyType::STATIC);
	//pbody->ctype = ColliderType::SHOP;
	//pbody->body->SetFixedRotation(true);

	//currentAnimation = &idle;



	return true;
}

bool Enemy_Goblin::Update(float dt)
{

	//printf("holla");
	//SDL_Rect rect = currentAnimation->GetCurrentFrame();

	//currentAnimation = &idle;

	//app->render->DrawTexture(Shoptexture, position.x, position.y, 1.8, SDL_FLIP_NONE, &rect);
	//currentAnimation->Update();
	return true;
}

bool Enemy_Goblin::CleanUp()
{
	return true;
}