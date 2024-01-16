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
#include "Diamond.h"

#include <stdio.h>
#include <tuple>
#include <cmath>
#include <vector>
#include <string>

Diamond::Diamond() : Entity(EntityType::ITEM)
{
	name.Create("item");

}

Diamond::~Diamond() {}

bool Diamond::Awake() {

	DiamondPath = parameters.attribute("texturepath").as_string();
	TSprite = parameters.attribute("Tsprite").as_int();
	SpriteX = parameters.attribute("x").as_int();
	SpriteY = parameters.attribute("y").as_int();
	PhotoWeight = parameters.attribute("Pweight").as_int();
	pos_X = parameters.attribute("Posx").as_int();
	pos_Y = parameters.attribute("Posy").as_int();
	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);
	idle.LoadAnim("Diamond", "idle", spritePositions);

	return true;
}

bool Diamond::Start() {
	//initilize textures

	if (app->scene->changeScena) {
		Awake();
	}
	Diamondtexture = app->tex->Load(DiamondPath);

	if (pbody == nullptr) {
		pbody = app->physics->CreateCircleSensor(pos_X + 32, pos_Y + 32, 28, bodyType::STATIC);
		pbody->ctype = ColliderType::ITEM;
		pbody->body->SetFixedRotation(true);
		pbody->listener = this;
	}

	currentAnimation = &idle;


	return true;
}

bool Diamond::Update(float dt)
{
	if (!playerGetDiamante) {
		rect = currentAnimation->GetCurrentFrame();
		app->render->DrawTexture(Diamondtexture, pos_X, pos_Y, 2, SDL_FLIP_NONE, &rect);
		currentAnimation->Update();

	}
	else {
		DestroyDiamante();
	}
	
	return true;
}


bool Diamond::CleanUp()
{
	return true;
}

void Diamond::DestroyDiamante() {

 	if (pbody != nullptr) {
		printf("entra");
		pbody->body->GetWorld()->DestroyBody(pbody->body);
		pbody = nullptr;
	}
}

void Diamond::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::PLAYER:
		app->scene->GetItem()->playerIsGetDiamante();
		playerGetDiamante = true;
		break;
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}


