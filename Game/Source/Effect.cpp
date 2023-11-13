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

	return true;
}

bool Effect::Start() {

	Effecttexture = app->tex->Load(EffectPath);

	Effecttexture2 = app->tex->Load(EffectPath2);
	/*pbody = app->physics->CreateCircle(position.x + 16, position.y + 16, 16, bodyType::DYNAMIC);
	pbody->ctype = ColliderType::EFFECT;
	pbody->body->SetFixedRotation(true);*/

	currentAnimation = &OroEffect;
	currentAnimation2 = &GhostEffect;
	return true;
}

bool Effect::Update(float dt)
{



	if (app->scene->GetPlayer()->isDead == true) {
		
		EffectFuncion();
		OroEffect.Reset();

	}else{

		ReviveEffectFuncion();
		GhostEffect.Reset();
	}


	return true;
}


bool Effect::CleanUp()
{

	currentAnimation->HasFinished();
	currentAnimation2->HasFinished();
	return true;
}

void Effect::EffectFuncion()
{

	//position.x = app->scene->GetPlayer()->position.x + 6;//+ 30
	//position.y = app->scene->GetPlayer()->position.y - 16;//+ 18

	position.x = app->scene->GetPlayer()->position.x + 20;//+ 30
	position.y = app->scene->GetPlayer()->position.y -25;//+ 18

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