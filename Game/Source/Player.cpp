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
	die.LoadAnim("Player", "die", spritePositions);
	run.LoadAnim("Player", "run", spritePositions);
	defend_on.LoadAnim("Player", "defend_on", spritePositions);
	defend_off.LoadAnim("Player", "defend_off", spritePositions);
	takehit.LoadAnim("Player", "take_hit", spritePositions);
	onground.LoadAnim("Player", "on_ground", spritePositions);

	close_atk.LoadAnim("Player", "close_atk", spritePositions);
	arrow_atk.LoadAnim("Player", "arrow_atk", spritePositions);
	air_atk.LoadAnim("Player", "air_atk", spritePositions);
	scope_atk.LoadAnim("Player", "scope_atk", spritePositions);
	sp_atk.LoadAnim("Player", "sp_atk", spritePositions);


	roll.LoadAnim("Player", "roll", spritePositions);
	slide.LoadAnim("Player", "slide", spritePositions);


	Jump_UP.LoadAnim("Player", "Jump_UP", spritePositions);
	Jump_DOWN.LoadAnim("Player", "Jump_DOWN", spritePositions);
	Jump_DOWN_LOOP.LoadAnim("Player", "Jump_DOWN_LOOP", spritePositions);

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

	//printf("%d", vel.y);

	app->win->GetWindowSize(width, height);

	if (isDead) {
		NoControl = false;
	}
	else {
		NoControl = true;
	}



	if (NoControl) {

		if (!app->godMode) {

			pbody->body->GetFixtureList()[0].SetSensor(false);
			vel = b2Vec2(0, pbody->body->GetLinearVelocity().y);

			//Keyboard Input
			keyInput(dt);


			//Set the velocity of the pbody of the player
			vel.y -= GRAVITY_Y;
			pbody->body->SetLinearVelocity(vel);

			//printf("%d\n", vel.y);
			printf("PosY> %d \n", position.y);





			//Jump
			if (jumpCount > 0) {

				
				currentAnimation = &Jump_UP;


				if (AniplayerOnPlatform) {
					currentAnimation = &slide;
				}

			}else{
				Jump_UP.Reset();

			}

			if (playerOnPlatform) {
				canJump = true;
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


			if (starFram) {
				frameCount++;
			}

			if (frameCount >= 1000) {
				frameCount = 0;
				starFram = false;
			}

			//if (canAtack) {
			//	if (app->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN) {
			//		//if (atackTypeCount > 3) {
			//		//	atackTypeCount = 1;
			//		//}
			//		//else
			//		//{
			//		//	atackTypeCount++;
			//		//}
			//		////printf("yes");
			//		//isAtack = true;
			//		
			//		//printf("%d", atackTypeCount);
			//		canAtack = true;
			//	}
			//	currentAnimation = &atack;
			//

			//}
			//checkAtack();

			Camera();
			//if (false) {

			//	if (shakeDuration > 0) {
			//		xOffset = (rand() % (2 * shakeMagnitude + 1)) - shakeMagnitude;
			//		yOffset = (rand() % (2 * shakeMagnitude + 1)) - shakeMagnitude;
			//		ShakeCamera(xOffset, yOffset);
			//		shakeDuration--;
			//	}
			//	firstTouchPlantform = 1;
			//}
			//else {
			//	/*Camera();*/
			//}
			

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

		app->render->DrawTexture(texture, position.x- 135, position.y - 97, 1.3, SDL_FLIP_HORIZONTAL, &rect);//-6
	}
	else
	{
		app->render->DrawTexture(texture, position.x-135, position.y - 97, 1.3, SDL_FLIP_NONE, &rect);//-6
	
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


	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
		currentAnimation = &defend_on;
		defend_off.Reset();
		In_defend = true;
	}

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_UP) {
		In_defend = false;
		defend_on.Reset();
	}

	if (!In_defend) {
		currentAnimation = &defend_off;
	}



	if (app->input->GetKey(SDL_SCANCODE_I) == KEY_REPEAT) {
		currentAnimation = &defend_on;
		defend_off.Reset();
		In_defend = true;
	}

}


void Player::Jump() {

}

//void Player::checkAtack() {
//
//	if (isAtack) {
//		if (frameCount >= 200) {
//			//printf("1");
//			atackTypeCount = 1;
//			frameCount = 0;
//		}
//		if (atackTypeCount == 1) {
//
//			currentAnimation = &atack;
//			canAtack = false;
//
//		}
//
//		if (atackTypeCount == 2) {
//			currentAnimation = &atack2;
//			canAtack = false;
//		}
//
//		if (atackTypeCount == 3) {
//			//printf("3");
//			currentAnimation = &atack3;
//			canAtack = false;
//		}
//
//
//		if (atack.HasFinished()) {
//			atack.Reset();
//			isAtack = false;
//			canAtack = true;
//			frameCount = 0;
//			starFram = true;
//		}
//
//		if (atack2.HasFinished()) {
//			atack2.Reset();
//			isAtack = false;
//			canAtack = true;
//			frameCount = 0;
//			starFram = true;
//		}
//		if (atack3.HasFinished()) {
//			atack3.Reset();
//			atackTypeCount = 0;
//			starFram = false;
//			frameCount = 0;
//			canAtack = true;
//			isAtack = false;
//		}
//
//	}
//
//}


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
		playerCheckAir = !playerCheckAir;

		/*shake = true;*/
		shakeDuration = 10;

		break;
	case ColliderType::DEADPLATFORM:
		LOG("Collision DEADPLATFORM");
		app->scene->GetPlayer()->isDead = true;
		break;

	case ColliderType::WALL:
		onWall = !onWall;
		//position.x = -1;

		break;

	case ColliderType::SHOP:

		break;
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}
