#include "ItemBox.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "Effect.h"
#include "Entity.h"
#include "Animation.h"



Effect::Effect() : Entity(EntityType::EFFECT)
{
	name.Create("effect");
}

Effect::~Effect() {}

bool Effect::Awake() {


	/*position.x = app->scene->GetPlayer()->position.x;
	position.y = app->scene->GetPlayer()->position.y;*/

	EffectPath = parameters.attribute("texturepath").as_string();


	TSprite = parameters.child("animations").attribute("Tsprite").as_int();
	SpriteX = parameters.child("animations").attribute("x").as_int();
	SpriteY = parameters.child("animations").attribute("y").as_int();
	PhotoWeight = parameters.child("animations").attribute("Pweight").as_int();

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();

	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);

	dieEffect.LoadAnim("ItemBox", "DieEffect", spritePositions);

	return true;
}

bool Effect::Start() {

	Effecttexture = app->tex->Load(EffectPath);
	pbody = app->physics->CreateCircle(position.x + 16, position.y + 16, 16, bodyType::DYNAMIC);
	pbody->ctype = ColliderType::EFFECT;
	pbody->body->SetFixedRotation(true);

	currentAnimation = &dieEffect;
	return true;
}

bool Effect::Update(float dt)
{

	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 50;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 35;

	app->render->DrawTexture(Effecttexture, position.x, position.y);


	currentAnimation = &dieEffect;
	//app->render->DrawTexture(Boxtexture, position.x, position.y);

	currentAnimation->Update();

	return true;
}

bool Effect::CleanUp()
{
	return true;
}