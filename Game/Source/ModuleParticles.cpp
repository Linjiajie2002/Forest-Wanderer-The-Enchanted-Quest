#include "ModuleParticles.h"

#include "App.h"

#include "Textures.h"
#include "Render.h"
#include "ModuleParticles.h"
#include "Physics.h"

#include "SDL/include/SDL_timer.h"
#include "PugiXml/src/pugiconfig.hpp"

#include <iostream>;

using namespace std;

ModuleParticles::ModuleParticles() : Module()
{
	name.Create("particles");
}

ModuleParticles::~ModuleParticles()
{

}


bool ModuleParticles::Awake(pugi::xml_node& config)
{
	bool ret = true;


	return ret;

}

bool ModuleParticles::Start()
{
	

	return true;
}

bool ModuleParticles::CleanUp()
{



	return true;
}

void ModuleParticles::CloseAtake(int posX, int posY, int Weight, int Height, ColliderType CLtype)
{
	pbody = app->physics->CreateRectangleSensor(posX, posY, Weight, Height, bodyType::STATIC);
	pbody->ctype = CLtype;
	pbody->body->SetFixedRotation(true);
}

void ModuleParticles::DestroyParticle(){
	printf("ddddd");
	pbody->body->GetWorld()->DestroyBody(pbody->body);
}

bool ModuleParticles::Update(float dt)
{

	bool ret = true;

	return ret;
}

bool ModuleParticles::PostUpdate()
{

	bool ret = true;
	return ret;
}

