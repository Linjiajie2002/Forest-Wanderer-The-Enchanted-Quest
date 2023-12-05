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
#include "Map.h"

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

	PathfindingPath = parameters.child("Pathfinding").attribute("texturepath").as_string();

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
	Pathfindingtexture = app->tex->Load(PathfindingPath);


	pbody = app->physics->CreateCircle(position.x - 10, position.y, 31, bodyType::DYNAMIC);
	pbody1 = app->physics->CreateRectangle(position.x - 10, position.y, 31, 10, bodyType::DYNAMIC);
	//pbody = app->physics->CreateCircle(position.x + 16, position.y + 16, 16, bodyType::STATIC);
	/*pbody->ctype = ColliderType::SHOP;*/
	pbody->body->SetFixedRotation(true);
	pbody1->body->SetFixedRotation(true);
	currentAnimation = &idle;



	return true;
}

bool Enemy_Flyeye::Update(float dt)
{

	SDL_Rect rect = currentAnimation->GetCurrentFrame();

	currentAnimation = &idle;

	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) + 10;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 15;


	//if (app->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN) {

	iPoint origPos = app->map->WorldToMap(position.x + 16, position.y + 16);
	iPoint playerPos = app->scene->GetPlayer()->position;
	playerPos = app->map->WorldToMap(playerPos.x, playerPos.y);
	app->map->pathfinding->CreatePath(origPos, playerPos);
	//printf("\nPlayer:Posx%d, Posy%d", app->scene->GetPlayer()->position.x, app->scene->GetPlayer()->position.y);

	if (countFrame >= 30) {
		if (app->map->pathfinding->GetLastPath()->Count() > 1) {

			//iPoint newPositionPoint = app->map->MapToWorld(app->map->pathfinding->GetLastPath()->At(app->map->pathfinding->GetLastPath()->Count() - 1)->x, app->map->pathfinding->GetLastPath()->At(app->map->pathfinding->GetLastPath()->Count() - 1)->y);
			iPoint newPositionPoint = app->map->MapToWorld(app->map->pathfinding->GetLastPath()->At(1)->x, app->map->pathfinding->GetLastPath()->At(1)->y);

			b2Vec2 newPosition = b2Vec2(PIXEL_TO_METERS(newPositionPoint.x), PIXEL_TO_METERS(newPositionPoint.y));

			pbody->body->SetLinearVelocity(b2Vec2(0, 0));
			pbody->body->SetTransform(newPosition, 0);

		}
		countFrame = 0;
	}
	//}

	app->render->DrawTexture(Enemytexture, position.x - 150, position.y - 120, 1.8, SDL_FLIP_NONE, &rect);
	//app->render->DrawTexture(Enemytexture, position.x, position.y-100);
	for (uint i = 0; i < app->map->pathfinding->GetLastPath()->Count(); ++i)
	{
		iPoint pos = app->map->MapToWorld(app->map->pathfinding->GetLastPath()->At(i)->x, app->map->pathfinding->GetLastPath()->At(i)->y);
		app->render->DrawTexture(Pathfindingtexture, pos.x + 1, pos.y + 1);
	}

	currentAnimation->Update();

	countFrame++;

	//printf("%d ", countFrame);
	return true;
}

bool Enemy_Flyeye::CleanUp()
{
	return true;
}