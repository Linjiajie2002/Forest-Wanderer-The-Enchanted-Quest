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
#include "Effect.h"

Player::Player() : Entity(EntityType::PLAYER)
{
	name.Create("Player");
}

Player::~Player() {

}

bool Player::Awake() {

	texturePath = parameters.attribute("texturepath").as_string();
	TSprite = parameters.child("animations").attribute("Tsprite").as_int();
	SpriteX = parameters.child("animations").attribute("x").as_int();
	SpriteY = parameters.child("animations").attribute("y").as_int();
	PhotoWeight = parameters.child("animations").attribute("Pweight").as_int();
	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);


	//data player

	speed = parameters.attribute("speed").as_float();
	crouchspeed = parameters.attribute("crouchspeed").as_float();
	jumpForce = parameters.attribute("jumpforce").as_float();


	//printf("%d %d %d %d", TSprite, SpriteX, SpriteY, PhotoWeight);

	idle.LoadAnim("Player", "idle", spritePositions);
	crouch.LoadAnim("Player", "crouch", spritePositions);
	run.LoadAnim("Player", "run", spritePositions);
	highjump.LoadAnim("Player", "highjump", spritePositions);
	slide.LoadAnim("Player", "slide", spritePositions);
	atack.LoadAnim("Player", "atack", spritePositions);
	atack2.LoadAnim("Player", "atack2", spritePositions);
	atack3.LoadAnim("Player", "atack3", spritePositions);
	die.LoadAnim("Player", "die", spritePositions);
	arrowAtack1.LoadAnim("Player", "atackarrow1", spritePositions);
	arrowAtack2.LoadAnim("Player", "atackarrow2", spritePositions);


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
	pickCoinFxId = app->audio->LoadFx(parameters.child("audio").attribute("texturepath").as_string());

	currentAnimation = &idle;
	pbody->body->SetFixedRotation(true);


	return true;
}



bool Player::Update(float dt)
{

	currentAnimation = &idle;
	vel = b2Vec2(0, pbody->body->GetLinearVelocity().y);


	//printf("%d",frameCount);
	//onWall = false;

	app->win->GetWindowSize(width, height);


	if (!isDead) {

		if (!app->godMode) {

			pbody->body->GetFixtureList()[0].SetSensor(false);
			vel = b2Vec2(0, pbody->body->GetLinearVelocity().y);

			//Keyboard Input
			keyInput(dt);


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

				if (playerOnPlatform) {
					canJump = true;
				}



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

			checkAtack();

			if (shake == true) {

				if (shakeDuration > 0) {
					xOffset = (rand() % (2 * shakeMagnitude + 1)) - shakeMagnitude;
					yOffset = (rand() % (2 * shakeMagnitude + 1)) - shakeMagnitude;
					ShakeCamera(xOffset, yOffset);
					shakeDuration--;
				}
			}
			else {
				Camera();
			}




		}
		else
		{
			godMod(dt);

		}

	}//if is dead


	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {

		vel = b2Vec2(1, 23);
		app->scene->GetPlayer()->isDead = false;

		pbody->body->SetTransform(vel, pbody->body->GetAngle());
	}


	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) {

		vel = b2Vec2(1, 23);
		pbody->body->SetTransform(vel, pbody->body->GetAngle());

	}

	//Update player position in pixels
	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 50;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 35;

	//Die
	if (isDead) {
		SDL_Delay(20);
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

void Player::Camera() {


	//Camera

	//if (app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN) {
	//	cameraUP = 0;
	//}

	//if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
	//	//cameraUP = app->render->camera.y;

	//	if (cameraUP >= 100) {
	//		app->render->camera.y = app->render->camera.y;
	//	}
	//	else {
	//		app->render->camera.y += 4;
	//	}
	//	cameraUP += 4;

	//}
	//else {
	//Camera();
	//}

	if (app->render->camera.x >= 2 && position.x < 514) {
		app->render->camera.x = 2;
	}
	else if (app->render->camera.x <= -5370 && position.x > 5883) {
		app->render->camera.x = -5370;
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

void Player::ShakeCamera(int xOffset, int yOffset) {

	if (app->render->camera.x >= 2 && position.x < 514) {
		app->render->camera.x = 2;
	}
	else if (app->render->camera.x <= -5370 && position.x > 5883) {
		app->render->camera.x = -5370;
	}
	else {
		app->render->camera.x = -position.x + (width / 2);

		app->render->camera.x = (-position.x * app->win->GetScale() + (width / 2) + xOffset);

	}


	app->render->camera.y = (-position.y * app->win->GetScale() + (height / 2) + yOffset);


	if (app->render->camera.y <= -829) {
		app->render->camera.y = -829;
	}
	if (app->render->camera.y >= 0) {
		app->render->camera.y = 0;
	}
}

void Player::keyInput(float dt) {



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

		/*if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && onWall) {
			printf("%d", onWall);
			vel = b2Vec2(pbody->body->GetLinearVelocity().x, (-speed * 4) * dt);
			currentAnimation = &crouch;
		}*/

	}
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {

		isFacingLeft = false;
		vel = b2Vec2(speed * dt, pbody->body->GetLinearVelocity().y);
		currentAnimation = &run;

		/*if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
			vel = b2Vec2(crouchspeed * dt, pbody->body->GetLinearVelocity().y);
			currentAnimation = &crouch;
		}*/

		/*if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && onWall) {
			printf("%d", onWall);
			vel = b2Vec2(pbody->body->GetLinearVelocity().x, (-speed * 4) * dt);
			currentAnimation = &crouch;
		}*/

	}



}


void Player::Jump() {

}

void Player::checkAtack() {

	if (isAtack) {
		if (frameCount >= 200) {
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

}


void Player::godMod(float dt) {

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
		Camera();
	}



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

		/*shake = true;
		shakeDuration = 10;*/

		break;
	case ColliderType::DEADPLATFORM:
		LOG("Collision DEADPLATFORM");
		app->scene->GetPlayer()->isDead = true;
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
