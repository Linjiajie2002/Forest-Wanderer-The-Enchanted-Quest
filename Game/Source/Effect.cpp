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
	dieEffect.LoadAnim("Effect", "DieEffect", spritePositions);


	EffectPath2 = parameters.child("animations2").attribute("texturepath").as_string();
	TSprite2 = parameters.child("animations2").attribute("Tsprite").as_int();
	SpriteX2 = parameters.child("animations2").attribute("x").as_int();
	SpriteY2 = parameters.child("animations2").attribute("y").as_int();
	PhotoWeight2 = parameters.child("animations2").attribute("Pweight").as_int();
	spritePositions2 = SPosition2.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);
	reviveEffect.LoadAnim("Effect", "ReviveEffect", spritePositions);

	return true;
}

bool Effect::Start() {

	Effecttexture = app->tex->Load(EffectPath);

	Effecttexture2 = app->tex->Load(EffectPath2);
	/*pbody = app->physics->CreateCircle(position.x + 16, position.y + 16, 16, bodyType::DYNAMIC);
	pbody->ctype = ColliderType::EFFECT;
	pbody->body->SetFixedRotation(true);*/

	currentAnimation = &reviveEffect;
	return true;
}

bool Effect::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN) {
		check =!check;
	}

	if (check == true) {
	
		ReviveEffectFuncion();
	}

	if (check == false) {

		dieEffect.Reset();
	}

	if (app->scene->GetPlayer()->isDead == true) {
		//ReviveEffect();
		DeadEffectFuncion();
	}
	else
	{
		
		reviveEffect.Reset();
	}


	/*reviveEffect.Reset();
	dieEffect.Reset();*/
	return true;
}


bool Effect::CleanUp()
{
	return true;
}

void Effect::DeadEffectFuncion()
{

	position.x = app->scene->GetPlayer()->position.x + 6;//+ 30
	position.y = app->scene->GetPlayer()->position.y - 16;//+ 18

	SDL_Rect rect = currentAnimation->GetCurrentFrame();

	currentAnimation = &reviveEffect;

	app->render->DrawTexture(Effecttexture2, position.x, position.y, 2, SDL_FLIP_NONE, &rect);




	//app->render->DrawTexture(Boxtexture, position.x, position.y);
	currentAnimation->Update();

}

void Effect::ReviveEffectFuncion()
{

	position.x = app->scene->GetPlayer()->position.x + 6;//+ 30
	position.y = app->scene->GetPlayer()->position.y - 16;//+ 18

	SDL_Rect rect = currentAnimation->GetCurrentFrame();

	currentAnimation = &dieEffect;

	app->render->DrawTexture(Effecttexture, position.x, position.y, 2, SDL_FLIP_NONE, &rect);




	//app->render->DrawTexture(Boxtexture, position.x, position.y);
	currentAnimation->Update();

}
