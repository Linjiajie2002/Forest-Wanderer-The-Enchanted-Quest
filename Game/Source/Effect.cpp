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


	/*position.x = app->scene->GetPlayer()->position.x;
	position.y = app->scene->GetPlayer()->position.y;*/


	position.x = app->scene->GetPlayer()->position.x + 32;
	position.y = app->scene->GetPlayer()->position.y + 32;
	EffectPath = parameters.attribute("texturepath").as_string();

	TSprite = parameters.child("animations").attribute("Tsprite").as_int();
	SpriteX = parameters.child("animations").attribute("x").as_int();
	SpriteY = parameters.child("animations").attribute("y").as_int();
	PhotoWeight = parameters.child("animations").attribute("Pweight").as_int();


	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);

	dieEffect.LoadAnim("Effect", "DieEffect", spritePositions);


	return true;
}

bool Effect::Start() {

	Effecttexture = app->tex->Load(EffectPath);
	/*pbody = app->physics->CreateCircle(position.x + 16, position.y + 16, 16, bodyType::DYNAMIC);
	pbody->ctype = ColliderType::EFFECT;
	pbody->body->SetFixedRotation(true);*/

	currentAnimation = &dieEffect;
	return true;
}

bool Effect::Update(float dt)
{

	if (app->scene->GetPlayer()->isDead == true) {
		position.x = app->scene->GetPlayer()->position.x + 26;
		position.y = app->scene->GetPlayer()->position.y + 18;

		SDL_Rect rect = currentAnimation->GetCurrentFrame();

		currentAnimation = &dieEffect;

		app->render->DrawTexture(Effecttexture, position.x, position.y, SDL_FLIP_NONE, &rect);


		//app->render->DrawTexture(Boxtexture, position.x, position.y);
		currentAnimation->Update();
	}
	else
	{
		dieEffect.Reset();
	}

	return true;
}

bool Effect::CleanUp()
{
	return true;
}