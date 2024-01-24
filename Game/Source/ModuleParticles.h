#ifndef __MODULE_PARTICLES_H__
#define __MODULE_PARTICLES_H__

#include "Module.h"

//#include "Globals.h"
//#include "Collider.h"
#include "Physics.h"


#define MAX_ACTIVE_PARTICLES 1000

struct SDL_Texture;
struct Collider;

class ModuleParticles : public Module
{
public:
	// Constructor
	// Initializes all the particles in the array to nullptr
	ModuleParticles();

	//Destructor
	~ModuleParticles();

	// Called when the module is activated
	// Loads the necessary textures for the particles

	bool Awake(pugi::xml_node& conf);

	// Called after Awake
	bool Start();

	// Called every frame
	bool Update(float dt);

	bool PostUpdate();

	// Called before quitting
	bool CleanUp();



	//void SetSpeedParticle(int position, fPoint speed);
	//fPoint GetPositionParticle(int position);
	//fPoint GetPositionSpeed(int position);
	//void DestroyCollision(int position);

	PhysBody* CloseAtake(int posX, int posY, int Weight, int Height,ColliderType CLtype);
	void DestroyParticle();


private:
	// Particles spritesheet loaded into an SDL Texture
	SDL_Texture* texture = nullptr;

	// An array to store and handle all the particles

	// An index to the last added particle
	uint lastParticle = 0;

public:

	const pugi::char_t* texturePath;

	PhysBody* pbody;


};

#endif // !__MODULEPARTICLES_H__