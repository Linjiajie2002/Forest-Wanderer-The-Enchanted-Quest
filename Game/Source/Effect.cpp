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
#include "Map.h"

Effect::Effect() : Entity(EntityType::EFFECT)
{
	name.Create("effect");
}

Effect::~Effect() {}

bool Effect::Awake() {

	return true;
}

bool Effect::Start() {
	reLoadXML();



	Effecttexture = app->tex->Load(EffectPath);
	Effecttexture2 = app->tex->Load(EffectPath2);
	Effecttexture3 = app->tex->Load(EffectPath3);
	Effecttexture4 = app->tex->Load(EffectPath4);

	currentAnimation = &OroEffect;
	currentAnimation2 = &GhostEffect;
	currentAnimation3 = &DiamanteEffect;
	currentAnimation4 = &Gravity_Void;
	return true;

	pbody = app->physics->CreateRectangleSensor(6344, 1340, 70, 70, bodyType::STATIC);
	pbody->ctype = ColliderType::VICTORYCOLLISION;

	
}

bool Effect::Update(float dt)
{

	if (app->scene->GetPlayer()->isDead == true) {

		EffectFuncion();
		OroEffect.Reset();

	}
	else {

		ReviveEffectFuncion();
		GhostEffect.Reset();
	}
	
		goMap2();


	return true;
}


bool Effect::CleanUp()
{

	SDL_DestroyTexture(Effecttexture);
	Effecttexture = nullptr;
	SDL_DestroyTexture(Effecttexture2);
	Effecttexture2 = nullptr;
	SDL_DestroyTexture(Effecttexture3);
	Effecttexture3 = nullptr;
	SDL_DestroyTexture(Effecttexture4);
	Effecttexture4 = nullptr;
	return true;
}

void Effect::EffectFuncion()
{

	position.x = app->scene->GetPlayer()->position.x + 20;
	position.y = app->scene->GetPlayer()->position.y - 25;

	SDL_Rect rect2 = currentAnimation2->GetCurrentFrame();


	currentAnimation2 = &GhostEffect;
	app->render->DrawTexture(Effecttexture2, position.x, position.y, 0.8, SDL_FLIP_NONE, &rect2);//0.8 , 2 
	currentAnimation2->Update();

}

void Effect::ReviveEffectFuncion()
{
	position.x = app->scene->GetPlayer()->position.x + 6;
	position.y = app->scene->GetPlayer()->position.y - 16;

	SDL_Rect rect = currentAnimation->GetCurrentFrame();


	currentAnimation = &OroEffect;
	app->render->DrawTexture(Effecttexture, position.x, position.y, 2, SDL_FLIP_NONE, &rect);
	currentAnimation->Update();

}

void Effect::LastEffect()
{
	SDL_Rect rect3 = currentAnimation3->GetCurrentFrame();
	currentAnimation3 = &DiamanteEffect;
	app->render->DrawTexture(Effecttexture3, 1850, 700, 0.5, SDL_FLIP_NONE, &rect3);
	currentAnimation3->Update();
}

void Effect::goMap2()
{
	if (app->map->LevelMap == 1) {
		if (!app->scene->GetPlayer()->isVictoria) {
			//printf("yes");
			position.x = 6250;
			position.y = 1312;
			sonid_vic = true;
			if (pbody == nullptr) {
				pbody = app->physics->CreateRectangleSensor(position.x, position.y, 80, 80, bodyType::STATIC);
				pbody->ctype = ColliderType::VICTORYCOLLISION;
				pbody->body->SetFixedRotation(true);
				pbody->listener = this;
			}
			
			SDL_Rect rect4 = currentAnimation4->GetCurrentFrame();
			currentAnimation4 = &Gravity_Void;
			app->render->DrawTexture(Effecttexture4, position.x-55, position.y-50, 1.2, SDL_FLIP_NONE, &rect4);//0.8 , 2 
			currentAnimation4->Update();

		}
		else {
			if (pbody != nullptr) {
				app->physics->GetWorld()->DestroyBody(pbody->body);
				pbody = nullptr;
			}
			

		}
	}
}

void Effect::reLoadXML()
{
	pugi::xml_document configFile;

	EffectPath = parameters.child("animations1").attribute("texturepath").as_string();
	TSprite = parameters.child("animations1").attribute("Tsprite").as_int();
	SpriteX = parameters.child("animations1").attribute("x").as_int();
	SpriteY = parameters.child("animations1").attribute("y").as_int();
	PhotoWeight = parameters.child("animations1").attribute("Pweight").as_int();
	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);
	OroEffect.LoadAnim("Effect", "OroEffect", spritePositions);

	EffectPath2 = parameters.child("animations2").attribute("texturepath").as_string();
	TSprite = parameters.child("animations2").attribute("Tsprite").as_int();
	SpriteX = parameters.child("animations2").attribute("x").as_int();
	SpriteY = parameters.child("animations2").attribute("y").as_int();
	PhotoWeight = parameters.child("animations2").attribute("Pweight").as_int();
	spritePositions = SPosition2.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);
	GhostEffect.LoadAnim("Effect", "Die", spritePositions);

	EffectPath3 = parameters.child("animations3").attribute("texturepath").as_string();
	TSprite = parameters.child("animations3").attribute("Tsprite").as_int();
	SpriteX = parameters.child("animations3").attribute("x").as_int();
	SpriteY = parameters.child("animations3").attribute("y").as_int();
	PhotoWeight = parameters.child("animations3").attribute("Pweight").as_int();
	spritePositions = Gravity_Void.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);
	DiamanteEffect.LoadAnim("Effect", "DiamanteEffect", spritePositions);


	EffectPath4 = parameters.child("animations4").attribute("texturepath").as_string();
	TSprite = parameters.child("animations4").attribute("Tsprite").as_int();
	SpriteX = parameters.child("animations4").attribute("x").as_int();
	SpriteY = parameters.child("animations4").attribute("y").as_int();
	PhotoWeight = parameters.child("animations4").attribute("Pweight").as_int();
	spritePositions = Gravity_Void.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);
	Gravity_Void.LoadAnim("Effect", "Gravity_Void_idle", spritePositions);
}

