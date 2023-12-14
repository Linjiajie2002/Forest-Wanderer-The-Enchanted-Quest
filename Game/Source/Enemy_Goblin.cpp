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

	EnemyPath = parameters.attribute("texturepath").as_string();
	TSprite = parameters.attribute("Tsprite").as_int();
	SpriteX = parameters.attribute("x").as_int();
	SpriteY = parameters.attribute("y").as_int();
	PhotoWeight = parameters.attribute("Pweight").as_int();
	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);


	speed = parameters.attribute("speed").as_float();
	idle.LoadAnim("Enemy_Goblin", "idle", spritePositions);
	run.LoadAnim("Enemy_Goblin", "run", spritePositions);
	take_hit.LoadAnim("Enemy_Goblin", "take_hit", spritePositions);
	die.LoadAnim("Enemy_Goblin", "die", spritePositions);
	atack.LoadAnim("Enemy_Goblin", "atake", spritePositions);

	position.x = parameters.attribute("Posx").as_int();
	position.y = parameters.attribute("Posy").as_int();

	return true;
}

bool Enemy_Goblin::Start() {



	//initilize textures
	Enemytexture = app->tex->Load(EnemyPath);
	pbody = app->physics->CreateCircle(position.x - 10, position.y, 32, bodyType::DYNAMIC);

	//pbody = app->physics->CreateCircle(position.x + 16, position.y + 16, 16, bodyType::STATIC);
	pbody->ctype = ColliderType::ENEMY;
	pbody->body->SetFixedRotation(true);
	pbody->body->GetFixtureList()[0].SetFriction(0.03);
	pbody->listener = this;
	currentAnimation = &idle;

	b2Filter enemyFilter;
	enemyFilter.categoryBits = static_cast<uint16_t>(ColliderType::PLATFORM);
	enemyFilter.maskBits = 0xFFFF & ~static_cast<uint16_t>(ColliderType::PLATFORM);  // 与任何碰撞组别的物体都发生碰撞，但不与自己发生碰撞
	pbody->body->GetFixtureList()[0].SetFilterData(enemyFilter);


	return true;
}

bool Enemy_Goblin::Update(float dt)
{
	SDL_Rect rect = currentAnimation->GetCurrentFrame();

	currentAnimation = &idle;

	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) + 15;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 30;

	pbody->body->SetLinearVelocity(b2Vec2(0, pbody->body->GetLinearVelocity().y - GRAVITY_Y));

	iPoint origPos = app->map->WorldToMap(position.x + 16, position.y + 16);
	iPoint playerPos = app->scene->GetPlayer()->position;
	playerPos = app->map->WorldToMap(playerPos.x, playerPos.y);
	playerPos.y += 1;
	/*if (isFacingLeft)playerPos.x += 4;*/
	playerPos.x += 1.2;

	if (AtackPlayer) {
		currentAnimation = &atack;

	}
	else {
		if (app->scene->GetPlayer()->inEnemyArear == true) {

			app->map->pathfinding->CreatePath(origPos, playerPos);
			currentAnimation = &run;
			if (app->map->pathfinding->GetLastPath()->Count() > 1) {
				iPoint newPositionPoint = app->map->MapToWorld(app->map->pathfinding->GetLastPath()->At(1)->x, app->map->pathfinding->GetLastPath()->At(1)->y);
				b2Vec2 newPosition = b2Vec2(PIXEL_TO_METERS(newPositionPoint.x), PIXEL_TO_METERS(newPositionPoint.y));
				pbody->body->SetLinearVelocity(b2Vec2(0, pbody->body->GetLinearVelocity().y - GRAVITY_Y));

				//printf("\nposy: %d", position.y - newPositionPoint.y);
				if (position.x > newPositionPoint.x) {
					isFacingLeft = true;
					pbody->body->SetLinearVelocity(b2Vec2(-speed * dt, pbody->body->GetLinearVelocity().y - GRAVITY_Y));
				}
				else {
					isFacingLeft = false;
					pbody->body->SetLinearVelocity(b2Vec2(speed * dt, pbody->body->GetLinearVelocity().y - GRAVITY_Y));

				}
			}
		}
	}

	if (currentAnimation->HasFinished()) {
		atack.Reset();
	}

	//printf("\n%d", position.x - app->scene->GetPlayer()->position.x);

	for (uint i = 0; i < app->map->pathfinding->GetLastPath()->Count(); ++i)
	{
		//printf("%d", countFrame);
		iPoint pos = app->map->MapToWorld(app->map->pathfinding->GetLastPath()->At(i)->x, app->map->pathfinding->GetLastPath()->At(i)->y);
		app->render->DrawTexture(app->scene->Pathfindingtexture, pos.x, pos.y);
	}


	if (isFacingLeft) {
		app->render->DrawTexture(Enemytexture, position.x - 150, position.y - 120, 1.8, SDL_FLIP_HORIZONTAL, &rect);//-6
	}
	else
	{
		app->render->DrawTexture(Enemytexture, position.x - 150, position.y - 120, 1.8, SDL_FLIP_NONE, &rect);//-6
	}


	currentAnimation->Update();
	return true;
}

bool Enemy_Goblin::CleanUp()
{
	return true;
}


void Enemy_Goblin::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::PLAYER:
		AtackPlayer = true;

		break;

	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}

void Enemy_Goblin::OnEndCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::PLAYER:
		AtackPlayer = false;
		break;

	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}
