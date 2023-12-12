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
#include "Map.h"

Enemy_Goblin::Enemy_Goblin() : Entity(EntityType::ENEMY_GOBLIN)
{
	name.Create("enemy");
}

Enemy_Goblin::~Enemy_Goblin() {}

bool Enemy_Goblin::Awake() {

	EnemyPath = parameters.child("Enemy_Goblin").attribute("texturepath").as_string();
	TSprite = parameters.child("Enemy_Goblin").attribute("Tsprite").as_int();
	SpriteX = parameters.child("Enemy_Goblin").attribute("x").as_int();
	SpriteY = parameters.child("Enemy_Goblin").attribute("y").as_int();
	PhotoWeight = parameters.child("Enemy_Goblin").attribute("Pweight").as_int();
	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);

	idle.LoadAnim("Enemy_Goblin", "idle", spritePositions);
	run.LoadAnim("Enemy_Goblin", "run", spritePositions);
	take_hit.LoadAnim("Enemy_Goblin", "take_hit", spritePositions);
	die.LoadAnim("Enemy_Goblin", "die", spritePositions);
	atack.LoadAnim("Enemy_Goblin", "atake", spritePositions);

	position.x = parameters.child("Enemy_Goblin").attribute("Posx").as_int();
	position.y = parameters.child("Enemy_Goblin").attribute("Posy").as_int();

	return true;
}

bool Enemy_Goblin::Start() {



	//initilize textures
	Enemytexture = app->tex->Load(EnemyPath);
	pbody = app->physics->CreateCircle(position.x - 10, position.y, 31, bodyType::DYNAMIC);
	//pbody = app->physics->CreateCircle(position.x + 16, position.y + 16, 16, bodyType::STATIC);
	pbody->ctype = ColliderType::SHOP;
	pbody->body->SetFixedRotation(true);

	currentAnimation = &idle;



	return true;
}

bool Enemy_Goblin::Update(float dt)
{

	//SDL_Rect rect = currentAnimation->GetCurrentFrame();

	//currentAnimation = &idle;

	//position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) + 10;
	//position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 15;


	//iPoint origPos = app->map->WorldToMap(position.x + 16, position.y + 16);
	//iPoint playerPos = app->scene->GetPlayer()->position;
	//playerPos = app->map->WorldToMap(playerPos.x, playerPos.y);
	//playerPos.y += 2;
	//playerPos.x += 1;
	//app->map->pathfinding->CreatePath(origPos, playerPos);

	//if (app->map->pathfinding->GetLastPath()->Count() > 1) {
	//	iPoint newPositionPoint = app->map->MapToWorld(app->map->pathfinding->GetLastPath()->At(1)->x, app->map->pathfinding->GetLastPath()->At(1)->y);
	//	b2Vec2 newPosition = b2Vec2(PIXEL_TO_METERS(newPositionPoint.x), PIXEL_TO_METERS(newPositionPoint.y));
	//	pbody->body->SetLinearVelocity(b2Vec2(0, 0));

	//	//printf("\nposx: %d, newpos:%d", position.x, newPositionPoint.x);
	//	if (position.x > newPositionPoint.x) {
	//		pbody->body->SetLinearVelocity(b2Vec2(-3, -GRAVITY_Y));

	//	}
	//	else {
	//		pbody->body->SetLinearVelocity(b2Vec2(3, -GRAVITY_Y));
	//	}


	//}

	//printf("\nPlayer:Posx%d, Posy%d", app->scene->GetPlayer()->position.x, app->scene->GetPlayer()->position.y);

	//if (countFrame >= 20) {
	//	currentAnimation = &run;
	//	if (app->map->pathfinding->GetLastPath()->Count() > 1) {

	//		//iPoint newPositionPoint = app->map->MapToWorld(app->map->pathfinding->GetLastPath()->At(app->map->pathfinding->GetLastPath()->Count() - 1)->x, app->map->pathfinding->GetLastPath()->At(app->map->pathfinding->GetLastPath()->Count() - 1)->y);
	//		/*iPoint newPositionPoint = app->map->MapToWorld(app->map->pathfinding->GetLastPath()->At(1)->x, app->map->pathfinding->GetLastPath()->At(1)->y);*/
	//		iPoint currentPositionPoint = app->map->MapToWorld(app->map->pathfinding->GetLastPath()->At(1)->x, app->map->pathfinding->GetLastPath()->At(1)->y);
	//		iPoint newPositionPoint(currentPositionPoint.x + 1, currentPositionPoint.y);

	//		currentAnimation = &run;


	//		b2Vec2 newPosition = b2Vec2(PIXEL_TO_METERS(newPositionPoint.x), PIXEL_TO_METERS(newPositionPoint.y));
	//		pbody->body->SetLinearVelocity(b2Vec2(0, 0));
	//		
	//		pbody->body->SetTransform(newPosition, 0);

	//	}
	//	countFrame = 0;
	//}




	//currentAnimation = &run;

	//app->render->DrawTexture(Enemytexture, position.x - 150, position.y - 120, 1.8, SDL_FLIP_NONE, &rect);
	//app->render->DrawTexture(Enemytexture, position.x, position.y-100);
	for (uint i = 0; i < app->map->pathfinding->GetLastPath()->Count(); ++i)
	{
		iPoint pos = app->map->MapToWorld(app->map->pathfinding->GetLastPath()->At(i)->x, app->map->pathfinding->GetLastPath()->At(i)->y);
		app->render->DrawTexture(Pathfindingtexture, pos.x - 1, pos.y - 1);
	}
	countFrame++;
	currentAnimation->Update();
	return true;
}

bool Enemy_Goblin::CleanUp()
{
	return true;
}