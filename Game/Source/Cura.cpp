#include "Item.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "Timer.h"
#include "Map.h"
#include "Cura.h"

#include <stdio.h>
#include <tuple>
#include <cmath>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>


Cura::Cura() : Entity(EntityType::CURA)
{
	name.Create("cura");
}

Cura::~Cura() {}

bool Cura::Awake() {

	/*CuraPath = parameters.attribute("texturepath").as_string();
	TSprite = parameters.attribute("Tsprite").as_int();
	SpriteX = parameters.attribute("x").as_int();
	SpriteY = parameters.attribute("y").as_int();
	PhotoWeight = parameters.attribute("Pweight").as_int();
	pos_X = parameters.attribute("Posx").as_int();
	pos_Y = parameters.attribute("Posy").as_int();
	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);
	idle.LoadAnim("cura", "cura_idle", spritePositions);
	die.LoadAnim("cura", "cura_die", spritePositions);
	start.LoadAnim("cura", "cura_start", spritePositions);*/

	return true;
}

bool Cura::Start() {
	//initilize textures


	reLoadXML();

	Curatexture= app->tex->Load(CuraPath);

	if (pbody == nullptr) {
		pbody = app->physics->CreateCircleSensor(pos_X + 55, pos_Y + 55, 28, bodyType::STATIC);
		pbody->ctype = ColliderType::ITEM;
		pbody->body->SetFixedRotation(true);
		pbody->listener = this;
	}

	currentAnimation = &idle;

	
	
	return true;
}

bool Cura::Update(float dt)
{
	secondsSinceStartup = startupTime.CountDown(59);
	startupTime.displayTime((int)secondsSinceStartup);



	if (!playerGetCura) {
		rect = currentAnimation->GetCurrentFrame();
		app->render->DrawTexture(Curatexture, pos_X, pos_Y, 1, SDL_FLIP_NONE, &rect);
		currentAnimation->Update();
		

	}
	else {
		currentAnimation = &die;
		DestroyCura();
		playerCuraDie = true;
		
	}

	if (playerCuraDie) {
		rect = currentAnimation->GetCurrentFrame();
		app->render->DrawTexture(Curatexture, app->scene->GetPlayer()->position.x, app->scene->GetPlayer()->position.y-30, 1, SDL_FLIP_NONE, &rect);
		currentAnimation->Update();
	}

	if (currentAnimation->HasFinished() && currentAnimation->getNameAnimation() == "die") {
		playerCuraDie = false;
		die.Reset();
	}



	

	return true;
}


bool Cura::CleanUp()
{
	if (pbody != nullptr) {
		app->physics->GetWorld()->DestroyBody(pbody->body);
	}

	if (Curatexture) {
		SDL_DestroyTexture(Curatexture);
	}
	return true;
}

void Cura::DestroyCura() {

	if (pbody != nullptr) {
		pbody->body->GetWorld()->DestroyBody(pbody->body);
		pbody = nullptr;
	}
}

void Cura::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::PLAYER:
		if (app->scene->GetPlayerLife()->life != app->scene->GetPlayerLife()->lifebar + 2) {
			app->scene->GetPlayerLife()->playerGetHeal();
			playerGetCura = true;
		}
		
		break;
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}

void Cura::reLoadXML()
{
	pugi::xml_document configFile;

	CuraPath = parameters.attribute("texturepath").as_string();
	TSprite = parameters.attribute("Tsprite").as_int();
	SpriteX = parameters.attribute("x").as_int();
	SpriteY = parameters.attribute("y").as_int();
	PhotoWeight = parameters.attribute("Pweight").as_int();
	pos_X = parameters.attribute("Posx").as_int();
	pos_Y = parameters.attribute("Posy").as_int();
	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);
	idle.LoadAnim("cura", "cura_idle", spritePositions);
	die.LoadAnim("cura", "cura_die", spritePositions);
	start.LoadAnim("cura", "cura_start", spritePositions);
}

