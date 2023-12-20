#include "App.h"
#include "Render.h"
#include "Scene.h"
#include "Point.h"
#include "Physics.h"
#include "Effect.h"
#include "Entity.h"
#include "Log.h"
#include "Animation.h"
#include "Textures.h"
#include "Audio.h"

Effect::Effect() : Entity(EntityType::EFFECT)
{
	name.Create("effect");
}

Effect::~Effect() {}

bool Effect::Awake() {


	EffectPath = parameters.child("animations1").attribute("texturepath").as_string();
	TSprite = parameters.child("animations1").attribute("Tsprite").as_int();
	SpriteX = parameters.child("animations1").attribute("x").as_int();
	SpriteY = parameters.child("animations1").attribute("y").as_int();
	PhotoWeight = parameters.child("animations1").attribute("Pweight").as_int();
	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);
	OroEffect.LoadAnim("Effect", "OroEffect", spritePositions);


	/*EffectPath2 = parameters.child("animations2").attribute("texturepath").as_string();
	TSprite2 = parameters.child("animations2").attribute("Tsprite").as_int();
	SpriteX2 = parameters.child("animations2").attribute("x").as_int();
	SpriteY2 = parameters.child("animations2").attribute("y").as_int();
	PhotoWeight2 = parameters.child("animations2").attribute("Pweight").as_int();
	spritePositions2 = SPosition2.SpritesPos(TSprite2, SpriteX2, SpriteY2, PhotoWeight2);
	GhostEffect.LoadAnim("Effect", "GhostEffect", spritePositions2);*/

	EffectPath2 = parameters.child("animations3").attribute("texturepath").as_string();
	TSprite2 = parameters.child("animations3").attribute("Tsprite").as_int();
	SpriteX2 = parameters.child("animations3").attribute("x").as_int();
	SpriteY2 = parameters.child("animations3").attribute("y").as_int();
	PhotoWeight2 = parameters.child("animations3").attribute("Pweight").as_int();
	spritePositions2 = SPosition2.SpritesPos(TSprite2, SpriteX2, SpriteY2, PhotoWeight2);
	GhostEffect.LoadAnim("Effect", "Die4", spritePositions2);


	EffectPath3 = parameters.child("animations5").attribute("texturepath").as_string();
	TSprite3 = parameters.child("animations5").attribute("Tsprite").as_int();
	SpriteX3 = parameters.child("animations5").attribute("x").as_int();
	SpriteY3 = parameters.child("animations5").attribute("y").as_int();
	PhotoWeight3 = parameters.child("animations5").attribute("Pweight").as_int();
	spritePositions3 = Gravity_Void.SpritesPos(TSprite3, SpriteX3, SpriteY3, PhotoWeight3);
	Gravity_Void.LoadAnim("Effect", "Gravity_Void_idle", spritePositions3);

	/*EffectPath2 = parameters.child("animations4").attribute("texturepath").as_string();
	TSprite2 = parameters.child("animations4").attribute("Tsprite").as_int();
	SpriteX2 = parameters.child("animations4").attribute("x").as_int();
	SpriteY2 = parameters.child("animations4").attribute("y").as_int();
	PhotoWeight2 = parameters.child("animations4").attribute("Pweight").as_int();
	spritePositions2 = SPosition2.SpritesPos(TSprite2, SpriteX2, SpriteY2, PhotoWeight2);
	GhostEffect.LoadAnim("Effect", "HealEffect", spritePositions2);*/

	return true;
}

bool Effect::Start() {

	Effecttexture = app->tex->Load(EffectPath);

	Effecttexture2 = app->tex->Load(EffectPath2);


	Effecttexture3 = app->tex->Load(EffectPath3);
	/*pbody = app->physics->CreateCircle(position.x + 16, position.y + 16, 16, bodyType::DYNAMIC);
	pbody->ctype = ColliderType::EFFECT;
	pbody->body->SetFixedRotation(true);*/
	currentAnimation = &OroEffect;
	currentAnimation2 = &GhostEffect;
	currentAnimation3 = &Gravity_Void;
	return true;


	//pbody->body->SetFixedRotation(true);
}

bool Effect::Update(float dt)
{
	pbody = app->physics->CreateRectangleSensor(6344, 1340, 70, 70, bodyType::STATIC);
	pbody->ctype = ColliderType::VICTORYCOLLISION;
	if (app->scene->GetPlayer()->isDead == true) {

		EffectFuncion();
		OroEffect.Reset();

	}
	else {

		ReviveEffectFuncion();
		GhostEffect.Reset();
	}

	if (!app->scene->GetPlayer()->isVictoria) {
		printf("yes");

		sonid_vic = true;

		position.x = 6304;//+ 30
		position.y = 1312;//+ 18
		SDL_Rect rect3 = currentAnimation3->GetCurrentFrame();
		currentAnimation3 = &Gravity_Void;
		app->render->DrawTexture(Effecttexture3, position.x, position.y, 0.8, SDL_FLIP_NONE, &rect3);//0.8 , 2 
		currentAnimation3->Update();
	}
	else {

		pbody->body->SetActive(false);

	}
	return true;
}


bool Effect::CleanUp()
{
	return true;
}

void Effect::EffectFuncion()
{

	//position.x = app->scene->GetPlayer()->position.x + 6;//+ 30
	//position.y = app->scene->GetPlayer()->position.y - 16;//+ 18

	position.x = app->scene->GetPlayer()->position.x + 20;//+ 30
	position.y = app->scene->GetPlayer()->position.y - 25;//+ 18

	SDL_Rect rect2 = currentAnimation2->GetCurrentFrame();


	currentAnimation2 = &GhostEffect;
	app->render->DrawTexture(Effecttexture2, position.x, position.y, 0.8, SDL_FLIP_NONE, &rect2);//0.8 , 2 
	currentAnimation2->Update();

}

void Effect::ReviveEffectFuncion()
{
	position.x = app->scene->GetPlayer()->position.x + 6;//+ 30
	position.y = app->scene->GetPlayer()->position.y - 16;//+ 18

	SDL_Rect rect = currentAnimation->GetCurrentFrame();


	currentAnimation = &OroEffect;
	app->render->DrawTexture(Effecttexture, position.x, position.y, 2, SDL_FLIP_NONE, &rect);
	currentAnimation->Update();

}
