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

Player::Player() : Entity(EntityType::PLAYER)
{
	name.Create("Player");
	//({最左边，最上面，最右边减去最左边，最下面-最上面})

	//idle1
	idle.PushBack({ 14, 6, 19, 30 });//Prime Linea
	idle.PushBack({ 66, 6, 19, 30 });
	idle.PushBack({ 115,6, 19, 30 });
	idle.PushBack({ 163,6, 19, 30 });


	idle.speed = 0.06f;
	idle.loop = true;

	//crouch;
	crouch.PushBack({ 216,6, 19, 30 });
	crouch.PushBack({ 265,6, 19, 30 });
	crouch.PushBack({ 315, 6, 19, 30 });
	crouch.PushBack({ 17, 45, 19, 30 });////Segundo Linea24,28

	crouch.speed = 0.04f;
	crouch.loop = true;

	//run;
	run.PushBack({ 67, 45, 24, 28 });
	run.PushBack({ 116,45, 24, 28 });
	run.PushBack({ 166,45, 24, 28 });
	run.PushBack({ 217,45, 24, 28 });
	run.PushBack({ 266,45, 24, 28 });
	run.PushBack({ 316,45, 24, 28 });
	

	run.speed = 0.08f;
	run.loop = true;
	
	//highjump;
	highjump.PushBack({ 15, 79, 24,31 });//Terce Linea
	highjump.PushBack({ 65, 79, 24,31 });
	highjump.PushBack({ 117, 79, 24,31 });
	highjump.PushBack({ 164, 79, 24,31 });
	highjump.PushBack({ 218, 79, 24,31 });
	highjump.PushBack({ 264, 79, 24,31 });
	highjump.PushBack({ 320, 79, 24,31 });
	highjump.PushBack({ 14, 112, 35, 35 });	//Quarta Linea
	highjump.PushBack({ 68, 112, 35, 35 });

	highjump.speed = 0.2f;
	highjump.loop = true;
	highjump.aniFrameTotal = 9;
	
	//slide
	slide.PushBack({ 118, 112, 35, 35 });
	slide.PushBack({ 155, 112, 35, 35 });
	slide.PushBack({ 205, 112, 35, 35 });
	slide.PushBack({ 255, 112, 35, 35 });
	slide.PushBack({ 309, 112, 35, 35 });
	slide.PushBack({ 15, 151, 23,35  });//Quinta Linea
	slide.PushBack({ 72, 151, 23,35 });
	slide.PushBack({ 122, 151, 23,35 });
	slide.PushBack({ 170, 151, 23,35 });
	slide.PushBack({ 221, 151, 23,35 });
	slide.PushBack({ 271, 151, 23,35 });
	slide.PushBack({ 321, 151, 23,35 });
	slide.PushBack({ 20,190,24,31});//Sixta Linea
	slide.PushBack({ 71,190,24,31 });
	slide.PushBack({ 121,190,24,31 });

	slide.speed = 0.08f;
	slide.loop = true;

	//idle2
	idle2.PushBack({ 160,190,24,31 });
	idle2.PushBack({ 210,190,24,31 });
	idle2.PushBack({ 259,190,24,31 });
	idle2.PushBack({ 309,190,24,31 });

	idle2.speed = 0.08f;
	idle2.loop = true;

	//atack
	atack.PushBack({ 7,221,35,37});//7
	atack.PushBack({ 58,221,35,37 });
	atack.PushBack({ 115,221,35,37 });
	atack.PushBack({ 165,221,35,37 });
	atack.PushBack({ 215,221,35,37 });
	atack.PushBack({ 265,221,35,37 });

	atack.speed = 0.08f;
	atack.loop = true;


	//atack2
	atack2.PushBack({ 315,221,35,37 });//
	atack2.PushBack({ 13,265,33,37 });//8
	atack2.PushBack({ 60,265,39,37 });//30->35,37
	atack2.PushBack({ 102,265,33,37 });
	atack2.PushBack({ 152,265,33,37 });

	atack2.speed = 0.08f;
	atack2.loop = true;

	//atack3
	atack3.PushBack({ 219,265,33,30 });
	atack3.PushBack({ 270,265,33,30 });
	atack3.PushBack({ 302,265,48,30 });
	atack3.PushBack({ 3,307,35,30 });//9
	atack3.PushBack({ 50,307,35,30 });//25
	atack3.PushBack({ 100,307,35,30 });

	atack3.speed = 0.08f;
	atack3.loop = true;


	//idle3
	idle3.PushBack({ 166,307,35,30 });
	idle3.PushBack({ 217,307,35,30 });
	idle3.PushBack({ 265,307,35,30 });
	idle3.PushBack({ 316,307,35,30 });
	

	idle3.speed = 0.08f;
	idle3.loop = true;

	//die
	die.PushBack({ 17,339,24,30 });//10
	die.PushBack({ 65,339,24,30 });
	die.PushBack({ 116,339,24,30 });
	die.PushBack({ 168,339,24,30 });
	die.PushBack({ 221,339,24,30 });
	die.PushBack({ 268,339,24,30 });

	die.speed = 0.08f;
	die.loop = false;

	
	//lowjump
	lowjump.PushBack({ 317,339,24,30 });
	lowjump.PushBack({ 18,376,23,30});//11
	lowjump.PushBack({ 68,376,23,30 });

	lowjump.speed = 0.08f;
	lowjump.loop = true;
	

}

Player::~Player() {

}

bool Player::Awake() {

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();

	return true;
}

bool Player::Start() {

	//initilize textures
	texture = app->tex->Load(texturePath);

	pbody = app->physics->CreateRectangle(position.x + 16, position.y + 16, 32,32, bodyType::DYNAMIC);
	pbody->listener = this;
	pbody->ctype = ColliderType::PLAYER;

	pickCoinFxId = app->audio->LoadFx("Assets/Audio/Fx/retro-video-game-coin-pickup-38299.ogg");

	currentAnimation = &idle;
	pbody->body->SetFixedRotation(true);

	return true;
}

bool Player::Update(float dt)
{
		currentAnimation = &idle;
	

	b2Vec2 vel = b2Vec2(0, pbody->body->GetLinearVelocity().y);

	vel.y -= GRAVITY_Y;
	

	
	
	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
		currentAnimation = &crouch;
	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		
		
	
		isFacingLeft = true;
		vel = b2Vec2(-speed*dt, pbody->body->GetLinearVelocity().y);
		currentAnimation = &run;
	}
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {

		isFacingLeft = false;
		vel = b2Vec2(speed*dt, pbody->body->GetLinearVelocity().y);
		currentAnimation = &run;
		
	}

	//Set the velocity of the pbody of the player
	pbody->body->SetLinearVelocity(vel);


	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {

		vel.y = 0;
		pbody->body->SetLinearVelocity(vel);
		pbody->body->ApplyLinearImpulse(b2Vec2(0, GRAVITY_Y * jumpForce), pbody->body->GetWorldCenter(), true);
		currentAnimation = &highjump;

	}


	if (app->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN) {
		currentAnimation = &atack;
	}



	//Update player position in pixels
	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;

	

	

	//app->render->DrawTexture(texture, position.x, position.y);
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	
	if (isFacingLeft) {

		app->render->DrawTexture(texture, position.x, position.y, SDL_FLIP_HORIZONTAL, &rect);
	}
	else
	{
		app->render->DrawTexture(texture, position.x, position.y, SDL_FLIP_NONE, &rect);
	}

	currentAnimation->Update();
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
		break;
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}



//if (app->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT) {
//	//
//	currentAnimation = &idle3;
//	app->render->DrawTexture(texture, position.x, position.y, &rect);
//}
//if (app->input->GetKey(SDL_SCANCODE_2) == KEY_REPEAT) {
//	//
//	currentAnimation = &die;
//	app->render->DrawTexture(texture, position.x, position.y, &rect);
//}
//if (app->input->GetKey(SDL_SCANCODE_3) == KEY_REPEAT) {
//	//
//	currentAnimation = &atack3;
//	app->render->DrawTexture(texture, position.x, position.y, &rect);
//}
//if (app->input->GetKey(SDL_SCANCODE_4) == KEY_REPEAT) {
//	//
//	currentAnimation = &highjump;
//	app->render->DrawTexture(texture, position.x, position.y, &rect);
//}
//if (app->input->GetKey(SDL_SCANCODE_5) == KEY_REPEAT) {
//	//
//	currentAnimation = &slide;
//	app->render->DrawTexture(texture, position.x, position.y, &rect);
//}
//if (app->input->GetKey(SDL_SCANCODE_6) == KEY_REPEAT) {
//	//
//	currentAnimation = &idle2;
//	app->render->DrawTexture(texture, position.x, position.y, &rect);
//}
//if (app->input->GetKey(SDL_SCANCODE_7) == KEY_REPEAT) {
//	//
//	currentAnimation = &atack;
//	app->render->DrawTexture(texture, position.x, position.y, &rect);
//}
//if (app->input->GetKey(SDL_SCANCODE_8) == KEY_REPEAT) {
//	//
//	currentAnimation = &atack2;
//	app->render->DrawTexture(texture, position.x, position.y, &rect);
//}
//if (app->input->GetKey(SDL_SCANCODE_9) == KEY_REPEAT) {
//	//
//	currentAnimation = &atack3;
//	app->render->DrawTexture(texture, position.x, position.y, &rect);
//}