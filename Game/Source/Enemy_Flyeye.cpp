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
	speed = parameters.child("Enemy_Flyeye").attribute("speed").as_float();

	idle.LoadAnim("Enemy_Flyeye", "idle", spritePositions);
	/*run.LoadAnim("Enemy_Flyeye", "run", spritePositions);*/
	take_hit.LoadAnim("Enemy_Flyeye", "take_hit", spritePositions);
	die.LoadAnim("Enemy_Flyeye", "die", spritePositions);
	atack.LoadAnim("Enemy_Flyeye", "atk", spritePositions);
	return true;
}

bool Enemy_Flyeye::Start() {

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

bool Enemy_Flyeye::Update(float dt)
{

	
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	if (life <= 0) {
		isDead = true;
	}

	if (!isDead) {
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
		if (app->scene->GetPlayer()->inEnemyArear) {
			attackTimer.Start();
			if (isTakehit) {
				currentAnimation = &take_hit;
			}
			if (AtackPlayer) {
				if (isTakehit) {
					currentAnimation = &take_hit;
				}
				else {

					if (timerAtaque.ReadSec() > 1) {
						printf("1");
						attackParticle = app->par->CloseAtake(position.x + 20, position.y, 30, 30, ColliderType::CLOSEATK_ENEMY);
						//else app->par->CloseAtake(position.x, position.y, 30, 30, ColliderType::CLOSEATK_ENEMY); if (!isFacingLeft)
						LOG("ATACA");
						canatake = true;
						timerAtaque.Start();
						//isDestroyPar = true;
					}
					if (canatake)currentAnimation = &atack;
				}

			}
			else {

				if (app->scene->GetPlayer()->inEnemyArear == true) {

					app->map->pathfinding->CreatePath(origPos, playerPos);
					currentAnimation = &idle;
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


						if (position.y > newPositionPoint.y) {
							isFacingLeft = true;
							pbody->body->SetLinearVelocity(b2Vec2(0, -speed * dt));
						}
						else {
							isFacingLeft = false;
							pbody->body->SetLinearVelocity(b2Vec2(0, speed * dt));

						}

					}
				}
			}
		}
		else {
			//EnemyMove(dt, enemyAreaLimitL, enemyAreaLimitR);
		}

		if (atack.HasFinished()) {
			//app->par->DestroyParticle();
			canatake = false;
		}

		if (currentAnimation->HasFinished()) {
			atack.Reset();
			take_hit.Reset();

			if (isTakehit)isTakehit = false;

		}

		/*if (!inEenemyArea) {
			enemyOutAreaTime++;
			if (enemyOutAreaTime >= 400) {

			}

		}*/
		for (uint i = 0; i < app->map->pathfinding->GetLastPath()->Count(); ++i)
		{
			//printf("%d", countFrame);
			iPoint pos = app->map->MapToWorld(app->map->pathfinding->GetLastPath()->At(i)->x, app->map->pathfinding->GetLastPath()->At(i)->y);
			app->render->DrawTexture(app->scene->Pathfindingtexture, pos.x, pos.y);
		}
	}

	if (isDead) {
		currentAnimation = &die;
		//pbody->body->GetWorld()->DestroyBody(pbody->body);
		pbody->body->SetActive(false);
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

bool Enemy_Flyeye::CleanUp()
{
	return true;
}