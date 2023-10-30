#include "Player.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "Animation.h"
#include "Window.h"
#include "Render.h"
#include "Map.h"

Player::Player() : Entity(EntityType::PLAYER)
{
	name.Create("Player");
	//({����ߣ������棬���ұ߼�ȥ����ߣ�������-������})


	//spritePositions = SPosition.SpritesPos(163, 100, 86, 500);
	//spritePositions = SPosition.SpritesPos(109, 50, 37, 350);




}

Player::~Player() {

}

bool Player::Awake() {

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();

	TSprite = parameters.child("animations").attribute("Tsprite").as_int();
	SpriteX = parameters.child("animations").attribute("x").as_int();
	SpriteY = parameters.child("animations").attribute("y").as_int();
	PhotoWeight = parameters.child("animations").attribute("Pweight").as_int();


	//printf("%d %d %d %d", TSprite, SpriteX, SpriteY, PhotoWeight);

	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);


	texturePath = parameters.attribute("texturepath").as_string();

	for (int i = 0; i < 4; i++)
	{
		idle.PushBack({ spritePositions[i] });
	}
	idle.speed = 0.15f;
	idle.loop = true;

	for (int i = 5; i < 8; i++)
	{
		crouch.PushBack({ spritePositions[i] });
	}
	crouch.speed = 0.08f;
	crouch.loop = true;


	for (int i = 9; i < 14; i++)
	{
		run.PushBack({ spritePositions[i] });
	}
	run.speed = 0.08f;
	run.loop = true;


	for (int i = 15; i < 24; i++)
	{
		highjump.PushBack({ spritePositions[i] });
	}

	highjump.speed = 0.4f;
	highjump.loop = false;

	for (int i = 25; i < 29; i++)
	{
		slide.PushBack({ spritePositions[i] });
	}

	slide.speed = 0.1f;
	slide.loop = true;


	for (int i = 43; i < 53; i++)
	{
		atack.PushBack({ spritePositions[i] });
	}

	atack.speed = 0.2f;
	atack.loop = false;


	for (int i = 54; i < 59; i++)
	{
		atack2.PushBack({ spritePositions[i] });
	}

	atack2.speed = 0.2f;
	atack2.loop = false;


	for (int i = 96; i < 100; i++)
	{
		atack3.PushBack({ spritePositions[i] });
	}

	atack3.speed = 0.2f;
	atack3.loop = false;


	for (int i = 64; i < 69; i++)
	{
		die.PushBack({ spritePositions[i] });
	}

	die.speed = 0.1f;
	die.loop = false;


	return true;
}

bool Player::Start() {

	//initilize textures
	texture = app->tex->Load(texturePath);

	//pbody = app->physics->CreateRectangle(position.x, position.y, 55,70, bodyType::DYNAMIC);
	pbody = app->physics->CreateCircle(position.x, position.y, 31, bodyType::DYNAMIC);
	pbody->listener = this;
	pbody->ctype = ColliderType::PLAYER;
	/*pbody->body->GetWorld()->DestroyBody();
	delete;*/
	pickCoinFxId = app->audio->LoadFx("Assets/Audio/Fx/retro-video-game-coin-pickup-38299.ogg");

	currentAnimation = &idle;
	pbody->body->SetFixedRotation(true);








	return true;
}

bool Player::Update(float dt)
{

	currentAnimation = &idle;


	b2Vec2 vel = b2Vec2(0, pbody->body->GetLinearVelocity().y);


	//printf("%d",frameCount);
	//onWall = false;

	app->win->GetWindowSize(width, height);



	if (!isDead) {

		if (!app->godMode) {

			pbody->body->GetFixtureList()[0].SetSensor(false);
			vel = b2Vec2(0, pbody->body->GetLinearVelocity().y);

			if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
				if (!isFacingLeft) {
					isFacingLeft = false;
				}
				currentAnimation = &crouch;
			}

			if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {

				isFacingLeft = true;
				vel = b2Vec2(-speed * dt, pbody->body->GetLinearVelocity().y);
				currentAnimation = &run;

				/*if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
					vel = b2Vec2(-crouchspeed * dt, pbody->body->GetLinearVelocity().y);
					currentAnimation = &crouch;
				}*/

				if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && onWall) {
					printf("%d", onWall);
					vel = b2Vec2(pbody->body->GetLinearVelocity().x, (-speed * 4));
					currentAnimation = &crouch;
				}

			}
			if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {

				isFacingLeft = false;
				vel = b2Vec2(speed * dt, pbody->body->GetLinearVelocity().y);
				currentAnimation = &run;

				/*if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
					vel = b2Vec2(crouchspeed * dt, pbody->body->GetLinearVelocity().y);
					currentAnimation = &crouch;
				}*/

				if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && onWall) {
					printf("%d", onWall);
					vel = b2Vec2(pbody->body->GetLinearVelocity().x, (-speed * 4));
					currentAnimation = &crouch;
				}

			}


			//Set the velocity of the pbody of the player
			vel.y -= GRAVITY_Y;
			pbody->body->SetLinearVelocity(vel);



			//Jump
			if (jumpCount > 0) {

				currentAnimation = &highjump;


				if (AniplayerOnPlatform) {
					currentAnimation = &slide;
				}

			}

			//LOG("JumpCount: %d ", jumpCount);
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {

				pbody->body->GetFixtureList()[0].SetSensor(true);


				if (canJump) {
					/*if (jumpCount == 1) {
						jumpForce = 30;
					}*/
					vel.y = 0;
					pbody->body->ApplyLinearImpulse(b2Vec2(0, GRAVITY_Y * jumpForce), pbody->body->GetWorldCenter(), true);
					jumpCount++;
					playerOnPlatform = false;
					//AniplayerOnPlatform = true;

					if (jumpCount == 2) {
						//jumpForce = 25;
						canJump = false;
					}
				}
			}
			else {

			}

			if (playerOnPlatform) {
				canJump = true;

			}



			if (starFram) {
				frameCount++;
			}

			if (frameCount >= 1000) {
				frameCount = 0;
				starFram = false;
			}

			if (canAtack) {
				if (app->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN) {
					if (atackTypeCount > 3) {
						atackTypeCount = 1;
					}
					else
					{
						atackTypeCount++;
					}
					//printf("yes");
					isAtack = true;

					//printf("%d", atackTypeCount);
				}
			}

			//printf("F%d ", frameCount);
			//Atack
			if (isAtack) {
				if (frameCount >= 400) {
					//printf("1");
					atackTypeCount = 1;
					frameCount = 0;
				}
				if (atackTypeCount == 1) {

					currentAnimation = &atack;
					canAtack = false;

				}

				if (atackTypeCount == 2) {
					currentAnimation = &atack2;
					canAtack = false;
				}

				if (atackTypeCount == 3) {
					//printf("3");
					currentAnimation = &atack3;
					canAtack = false;
				}


				if (atack.HasFinished()) {
					atack.Reset();
					isAtack = false;
					canAtack = true;
					frameCount = 0;
					starFram = true;
				}

				if (atack2.HasFinished()) {
					atack2.Reset();
					isAtack = false;
					canAtack = true;
					frameCount = 0;
					starFram = true;
				}
				if (atack3.HasFinished()) {
					atack3.Reset();
					atackTypeCount = 0;
					starFram = false;
					frameCount = 0;
					canAtack = true;
					isAtack = false;
				}
			}


			//Camera
			if (app->render->camera.x >= 2 && position.x < 514) {
				app->render->camera.x = 2;
			}

			else {
				app->render->camera.x = -position.x + (width / 2);

				app->render->camera.x = (-position.x * app->win->GetScale() + (width / 2));

			}
			app->render->camera.y = (-position.y * app->win->GetScale() + (height / 2));

			if (app->render->camera.y <= -829) {
				app->render->camera.y = -829;
			}
			if (app->render->camera.y >= 0) {
				app->render->camera.y = 0;
			}

		}
		else
		{

			vel = b2Vec2(0, 0);
			pbody->body->SetLinearVelocity(vel);
			pbody->body->GetFixtureList()[0].SetSensor(true);

			if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {

				isFacingLeft = true;
				vel = b2Vec2(-speed * dt, pbody->body->GetLinearVelocity().y);
				currentAnimation = &run;
				pbody->body->SetLinearVelocity(vel);

			}
			if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {

				isFacingLeft = false;
				vel = b2Vec2(speed * dt, pbody->body->GetLinearVelocity().y);
				currentAnimation = &run;
				pbody->body->SetLinearVelocity(vel);
			}

			if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {

				isFacingLeft = true;
				vel = b2Vec2(pbody->body->GetLinearVelocity().x, (-speed * 32));
				currentAnimation = &run;
				pbody->body->SetLinearVelocity(vel);
			}

			if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
				isFacingLeft = false;
				vel = b2Vec2(pbody->body->GetLinearVelocity().x, (speed * 32));
				currentAnimation = &run;
				pbody->body->SetLinearVelocity(vel);
			}


			if (app->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN) {

				if (MoveCamere == false) {
					MoveCamere = true;
				}
				else {
					MoveCamere = false;
				}

			}

			if (MoveCamere == false) {

				//Camera
				if (app->render->camera.x >= 2 && position.x < 514) {
					app->render->camera.x = 2;
				}

				else {
					app->render->camera.x = -position.x + (width / 2);

					app->render->camera.x = (-position.x * app->win->GetScale() + (width / 2));

				}
				app->render->camera.y = (-position.y * app->win->GetScale() + (height / 2));

				if (app->render->camera.y <= -829) {
					app->render->camera.y = -829;
				}
				if (app->render->camera.y >= 0) {
					app->render->camera.y = 0;
				}
			}

		}

	}//if is dead




	//Update player position in pixels
	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 50;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 35;


	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
		//position.y = parameters.attribute("y").as_int();

		vel = b2Vec2(1, 23);


		pbody->body->SetTransform(vel, pbody->body->GetAngle());

		printf("posX: %d ", position.x);
		printf("posY: %d ", position.y);
		//pbody->body->SetLinearVelocity(vel);
	}


	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) {
		//position.y = parameters.attribute("y").as_int();

		vel = b2Vec2(1, 23);


		pbody->body->SetTransform(vel, pbody->body->GetAngle());

		printf("posX: %d ", position.x);
		printf("posY: %d ", position.y);
		//pbody->body->SetLinearVelocity(vel);
	}




	//printf("PosY: %d ",position.y);//-989-957
	//printf("\n");
	//printf("CameraY: %d ", app->render->camera.y);//-989-957






	//Die
	if (isDead) {
		currentAnimation = &die;

	}

	if (app->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN) {
		isDead = !isDead;
		die.Reset();
	}




	//app->render->DrawTexture(texture, position.x, position.y);
	SDL_Rect rect = currentAnimation->GetCurrentFrame();

	if (isFacingLeft) {

		app->render->DrawTexture(texture, position.x, position.y - 6, 2, SDL_FLIP_HORIZONTAL, &rect);
	}
	else
	{
		app->render->DrawTexture(texture, position.x, position.y - 6, 2, SDL_FLIP_NONE, &rect);
	}



	currentAnimation->Update();

	//cargar siempre despues de dibujar al player
	app->map->UpdateDelante();



	return true;
}



bool Player::CleanUp()
{

	return true;
}

void Player::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::ITEM:
		LOG("Collision ITEM");
		app->audio->PlayFx(pickCoinFxId);
		break;
	case ColliderType::PLATFORM:
		LOG("Collision PLATFORM");
		//AniplayerOnPlatform = true;
		jumpCount = 0;
		highjump.Reset();
		playerOnPlatform = true;
		break;

	case ColliderType::WALL:
		onWall = !onWall;
		//position.x = -1;

		break;
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}
