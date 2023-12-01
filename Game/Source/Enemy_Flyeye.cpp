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

	EnemyPath = parameters.child("Enemy_Flyeye").attribute("texturepath").as_string();
	TSprite = parameters.child("Enemy_Flyeye").attribute("Tsprite").as_int();
	SpriteX = parameters.child("Enemy_Flyeye").attribute("x").as_int();
	SpriteY = parameters.child("Enemy_Flyeye").attribute("y").as_int();
	PhotoWeight = parameters.child("Enemy_Flyeye").attribute("Pweight").as_int();
	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);

	position.x = parameters.child("Enemy_Flyeye").attribute("Posx").as_int();
	position.y = parameters.child("Enemy_Flyeye").attribute("Posy").as_int();

	idle.LoadAnim("Enemy_Flyeye", "idle", spritePositions);
	/*run.LoadAnim("Enemy_Flyeye", "run", spritePositions);*/
	take_hit.LoadAnim("Enemy_Flyeye", "take_hit", spritePositions);
	die.LoadAnim("Enemy_Flyeye", "die", spritePositions);
	atack.LoadAnim("Enemy_Flyeye", "atk", spritePositions);
	return true;
}

bool Enemy_Flyeye::Start() {

	//initilize textures
	Enemytexture = app->tex->Load(EnemyPath);
	pbody = app->physics->CreateCircle(position.x-10, position.y, 31, bodyType::DYNAMIC);
	//pbody = app->physics->CreateCircle(position.x + 16, position.y + 16, 16, bodyType::STATIC);
	/*pbody->ctype = ColliderType::SHOP;*/
	pbody->body->SetFixedRotation(true);

	currentAnimation = &idle;



	return true;
}

bool Enemy_Flyeye::Update(float dt)
{

	printf("PosX: %d", position.x);
	printf("\nPosy: %d", position.y);


	SDL_Rect rect = currentAnimation->GetCurrentFrame();

	currentAnimation = &idle;

	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x)+ 10;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y)-15;

	app->render->DrawTexture(Enemytexture, position.x-150, position.y-120, 1.8, SDL_FLIP_NONE, &rect);
	//app->render->DrawTexture(Enemytexture, position.x, position.y-100);
	currentAnimation->Update();


	return true;
}

bool Enemy_Flyeye::CleanUp()
{
	return true;
}