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
#include "Teleport.h"

#include <stdio.h>
#include <tuple>
#include <cmath>
#include <vector>
#include <string>

Teleport::Teleport() : Entity(EntityType::TELEPORT)
{
	name.Create("teleport");

}

Teleport::~Teleport() {}

bool Teleport::Awake() {

	

	return true;
}

bool Teleport::Start() {
	//initilize textures

	reLoadXML();

	TeleportTexture = app->tex->Load(TeleportTexturePath);

	if (pbody == nullptr) {
		pbody = app->physics->CreateRectangleSensor(pos_X + 64, pos_Y + 90, 40,120, bodyType::STATIC);
		pbody->ctype = ColliderType::ITEM;
		pbody->body->SetFixedRotation(true);
		pbody->listener = this;
	}

	currentAnimation = &idle;


	return true;
}

bool Teleport::Update(float dt)
{

	rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(TeleportTexture, pos_X, pos_Y, 0.5, SDL_FLIP_NONE, &rect);
	currentAnimation->Update();

	return true;
}


bool Teleport::CleanUp()
{
	if (pbody != nullptr) {
		app->physics->GetWorld()->DestroyBody(pbody->body);
	}

	return true;
}


void Teleport::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::PLAYER:
		currentAnimation = &save;
		app->SaveRequest();
		break;
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}

void Teleport::reLoadXML()
{
	pugi::xml_document configFile;
	TeleportTexturePath = parameters.attribute("texturepath").as_string();
	TSprite = parameters.attribute("Tsprite").as_int();
	SpriteX = parameters.attribute("x").as_int();
	SpriteY = parameters.attribute("y").as_int();
	PhotoWeight = parameters.attribute("Pweight").as_int();
	pos_X = parameters.attribute("Posx").as_int();
	pos_Y = parameters.attribute("Posy").as_int();
	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);
	idle.LoadAnim("Teleport", "idle", spritePositions);
	save.LoadAnim("Teleport", "save", spritePositions);
}


