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

#include <random>

Enemy_Flyeye::Enemy_Flyeye() : Entity(EntityType::ENEMY_FLYEYE)
{
	name.Create("enemy");
}

Enemy_Flyeye::~Enemy_Flyeye() {}

bool Enemy_Flyeye::Awake() {

	EnemyPath = parameters.attribute("texturepath").as_string();
	TSprite = parameters.attribute("Tsprite").as_int();
	SpriteX = parameters.attribute("x").as_int();
	SpriteY = parameters.attribute("y").as_int();
	PhotoWeight = parameters.attribute("Pweight").as_int();
	enemyAreaLimitR = parameters.attribute("Area_Limit_R").as_int();
	enemyAreaLimitL = parameters.attribute("Area_Limit_L").as_int();
	life = parameters.attribute("life").as_int();
	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);

	PathfindingPath = parameters.attribute("texturepath").as_string();

	position.x = parameters.attribute("Posx").as_int();
	position.y = parameters.attribute("Posy").as_int();
	speed = parameters.attribute("speed").as_float();

	idle.LoadAnim("Enemy_Flyeye", "idle", spritePositions);
	/*run.LoadAnim("Enemy_Flyeye", "run", spritePositions);*/
	take_hit.LoadAnim("Enemy_Flyeye", "take_hit", spritePositions);
	die.LoadAnim("Enemy_Flyeye", "die", spritePositions);
	atack.LoadAnim("Enemy_Flyeye", "atk", spritePositions);

	return true;
}

bool Enemy_Flyeye::Start() {
	if (app->scene->changeScena) {
		reLoadXML(app->scene->nodeinfo(EntityType::ENEMY_FLYEYE));
	}

	Enemytexture = app->tex->Load(EnemyPath);
	pbody = app->physics->CreateCircle(position.x - 10, position.y, 28, bodyType::DYNAMIC);

	//pbody = app->physics->CreateCircle(position.x + 16, position.y + 16, 16, bodyType::STATIC);
	pbody->ctype = ColliderType::ENEMY;
	pbody->body->SetFixedRotation(true);
	pbody->body->GetFixtureList()[0].SetFriction(0.03);
	pbody->listener = this;
	//pbody->body->SetGravityScale(0);
	deadenemy = app->audio->LoadFx(parameters.child("deadenemy").attribute("texturepath").as_string());

	currentAnimation = &idle;
	originalposition = iPoint(position.x, position.y);

	b2Filter enemyFilter;
	enemyFilter.categoryBits = static_cast<uint16_t>(ColliderType::PLATFORM);
	enemyFilter.maskBits = 0xFFFF & ~static_cast<uint16_t>(ColliderType::PLATFORM);  //
	pbody->body->GetFixtureList()[0].SetFilterData(enemyFilter);

	player = app->scene->GetPlayer();


	return true;
}

bool Enemy_Flyeye::Update(float dt)
{

	if (player->position.x >= leftTopX && player->position.x <= rightBottomX &&
		player->position.y >= leftTopY && player->position.y <= rightBottomY) {


		if (player->position.x >= atk_leftTopX && player->position.x <= atk_rightBottomX &&
			player->position.y >= atk_leftTopY && player->position.y <= atk_rightBottomY) {
			AtackPlayer = true;

		}
		else {
			//printf("\nOutArea");
			AtackPlayer = false;
			atk_leftTopX = position.x - atk_rangeSize * 8;
			atk_leftTopY = position.y - atk_rangeSize;
			atk_rightBottomX = position.x + atk_rangeSize;
			atk_rightBottomY = position.y + atk_rangeSize * 2;
		}


		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		if (life <= 0) {
			active = false;

			isDead = true;
			app->audio->PlayFx(deadenemy);

		}

		if (!isDead) {
			currentAnimation = &idle;

			position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) + 15;
			position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 22;


			pbody->body->SetLinearVelocity(b2Vec2(0, 0));

			iPoint origPos = app->map->WorldToMap(position.x + 16, position.y + 16);
			iPoint playerPos = app->scene->GetPlayer()->position;
			playerPos = app->map->WorldToMap(playerPos.x, playerPos.y);
			playerPos.y += 1;
			/*if (isFacingLeft)playerPos.x += 4;*/
			playerPos.x += 2;


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
							if (!isFacingLeft)attackParticle = app->par->CloseAtake(position.x + 30, position.y + 20, 40, 60, ColliderType::CLOSEATK_ENEMY);
							else attackParticle = app->par->CloseAtake(position.x - 50, position.y + 20, 40, 60, ColliderType::CLOSEATK_ENEMY);
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
							//pbody->body->SetLinearVelocity(b2Vec2(0, pbody->body->GetLinearVelocity().y - GRAVITY_Y));

							if (position.x > newPositionPoint.x) {
								isFacingLeft = true;
								pbody->body->SetLinearVelocity(b2Vec2(-speed * dt, pbody->body->GetLinearVelocity().y - GRAVITY_Y));
							}
							else if (position.x < newPositionPoint.x) {
								isFacingLeft = false;
								pbody->body->SetLinearVelocity(b2Vec2(speed * dt, pbody->body->GetLinearVelocity().y - GRAVITY_Y));

							}
							/*else {
								if (position.y == lastY) {
									if (position.x > newPositionPoint.x) {
										printf("×ó");
										pbody->body->SetLinearVelocity(b2Vec2(speed * dt,0));
									}
									else {
										printf("ÓÒ");
										pbody->body->SetLinearVelocity(b2Vec2(-speed * dt, 0));
									}
								}
							}*/



							if (position.y > newPositionPoint.y) {
								pbody->body->SetLinearVelocity(b2Vec2(pbody->body->GetLinearVelocity().x, -speed * dt));

							}
							else if (position.y < newPositionPoint.y) {
								pbody->body->SetLinearVelocity(b2Vec2(pbody->body->GetLinearVelocity().x, speed * dt));

							}
							//else {
							//	if (position.x == lastX) {
							//		if (position.y > newPositionPoint.y) {
							//			//printf("×ó");
							//			pbody->body->SetLinearVelocity(b2Vec2(-speed * dt, pbody->body->GetLinearVelocity().y - GRAVITY_Y));
							//		}
							//		else {
							//			//printf("ÓÒ");
							//			pbody->body->SetLinearVelocity(b2Vec2(speed * dt, pbody->body->GetLinearVelocity().y - GRAVITY_Y));
							//		}

							//	}
							//}
							lastX = position.x;
							lastY = position.y;
						}
					}
				}
			}
			else {
				EnemyMove(dt, enemyAreaLimitL, enemyAreaLimitR);
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

			if (app->debug) {
				for (uint i = 0; i < app->map->pathfinding->GetLastPath()->Count(); ++i)
				{
					//printf("%d", countFrame);
					iPoint pos = app->map->MapToWorld(app->map->pathfinding->GetLastPath()->At(i)->x, app->map->pathfinding->GetLastPath()->At(i)->y);
					app->render->DrawTexture(app->scene->Pathfindingtexture, pos.x, pos.y);
				}
			}
		}





		if (isFacingLeft) {
			app->render->DrawTexture(Enemytexture, position.x - 150, position.y - 120, 1.8, SDL_FLIP_HORIZONTAL, &rect);//-6
		}
		else
		{
			app->render->DrawTexture(Enemytexture, position.x - 150, position.y - 120, 1.8, SDL_FLIP_NONE, &rect);//-6
		}


	}
	else {
		//printf("\nOutArea");
		leftTopX = position.x - rangeSize;
		leftTopY = position.y - rangeSize / 2;
		rightBottomX = position.x + rangeSize;
		rightBottomY = position.y + rangeSize / 2;
	}

	if (isDead) {
		currentAnimation = &die;
		if (pbody != nullptr) {
			pbody->body->GetWorld()->DestroyBody(pbody->body);
			pbody = nullptr;
		}
		//pbody->body->SetActive(false);


	}

	if (attackParticle != nullptr) {
		if (timerAtaque.ReadMSec() > 300) { //1s == 1000ms 
			//printf("0");
			//app->par->DestroyParticle();
			timerAtaque.Start();
			//isDestroyPar = false;
			attackParticle->body->GetWorld()->DestroyBody(attackParticle->body);
			attackParticle = nullptr;

		}
	}


	currentAnimation->Update();
	return true;
}

bool Enemy_Flyeye::CleanUp()
{
	if (pbody != nullptr) {
		app->physics->GetWorld()->DestroyBody(pbody->body);
	}

	if (Enemytexture) {
		SDL_DestroyTexture(Enemytexture);
	}
	return true;
}


void Enemy_Flyeye::EnemyMove(float dt, int enemyAreaLimitL, int enemyAreaLimitR)
{
	if (!enemyidle) {
		if (!walkrdinWork)rddirection = Rd();
		timeidle = 0;
		walkrdinWork = true;
		//currentAnimation = &idle;
		if (position.x < enemyAreaLimitL) {
			rddirection = true;
		}
		if (position.x > enemyAreaLimitR) {
			rddirection = false;
		}

		if (rddirection) {
			pbody->body->SetLinearVelocity(b2Vec2(speed * dt, pbody->body->GetLinearVelocity().y - GRAVITY_Y));
			isFacingLeft = false;
			walkFrameCount++;
			if (walkFrameCount > 50)enemyidle = true;
		}

		if (!rddirection) {
			pbody->body->SetLinearVelocity(b2Vec2(-speed * dt, pbody->body->GetLinearVelocity().y - GRAVITY_Y));
			isFacingLeft = true;
			walkFrameCount++;
			if (walkFrameCount > 50)enemyidle = true;
		}
	}
	else {
		if (!rdinWork)rddirection = Rd();
		rdinWork = true;
		currentAnimation = &idle;
		timeidle++;
		if (rddirection) {
			if (timeidle >= 50)enemyidle = false, rdinWork = false, walkFrameCount = 0, walkrdinWork = false;
		}
		else {
			if (timeidle >= 200)enemyidle = false, rdinWork = false, walkFrameCount = 0, walkrdinWork = false;
		}
	}
}

bool Enemy_Flyeye::Rd()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> distribution(0, 1);
	bool rddirection = distribution(mt);

	return rddirection;
}

void Enemy_Flyeye::reLoadXML(pugi::xml_node& parameters)
{
	pugi::xml_document configFile;

	EnemyPath = parameters.attribute("texturepath").as_string();
	TSprite = parameters.attribute("Tsprite").as_int();
	SpriteX = parameters.attribute("x").as_int();
	SpriteY = parameters.attribute("y").as_int();
	PhotoWeight = parameters.attribute("Pweight").as_int();
	enemyAreaLimitR = parameters.attribute("Area_Limit_R").as_int();
	enemyAreaLimitL = parameters.attribute("Area_Limit_L").as_int();
	life = parameters.attribute("life").as_int();
	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);

	PathfindingPath = parameters.attribute("texturepath").as_string();

	position.x = parameters.attribute("Posx").as_int();
	position.y = parameters.attribute("Posy").as_int();
	speed = parameters.attribute("speed").as_float();

	idle.LoadAnim("Enemy_Flyeye", "idle", spritePositions);
	/*run.LoadAnim("Enemy_Flyeye", "run", spritePositions);*/
	take_hit.LoadAnim("Enemy_Flyeye", "take_hit", spritePositions);
	die.LoadAnim("Enemy_Flyeye", "die", spritePositions);
	atack.LoadAnim("Enemy_Flyeye", "atk", spritePositions);

}


void Enemy_Flyeye::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::PLAYER:
		AtackPlayer = true;
		break;

	case ColliderType::ENEMYAREA:
		inEenemyArea = true;
		break;

	case ColliderType::CLOSEATK_PLAYER:
		isTakehit = true;
		life--;
		break;
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}

void Enemy_Flyeye::OnEndCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::PLAYER:
		AtackPlayer = false;
		break;

	case ColliderType::ENEMYAREA:
		inEenemyArea = false;
		break;
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}