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


ItemBox::ItemBox() : Entity(EntityType::ITEM)
{
	name.Create("itembox");
}

ItemBox::~ItemBox() {}

bool ItemBox::Awake() {

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();

	BoxPath = parameters.attribute("texturepath").as_string();


	TSprite = parameters.child("animations").attribute("Tsprite").as_int();
	SpriteX = parameters.child("animations").attribute("x").as_int();
	SpriteY = parameters.child("animations").attribute("y").as_int();
	PhotoWeight = parameters.child("animations").attribute("Pweight").as_int();

	spritePositions = SPosition.SpritesPos(TSprite, SpriteX, SpriteY, PhotoWeight);

	idle.LoadAnim("ItemBox", "idle", spritePositions);
	openBox.LoadAnim("ItemBox", "openBox1", spritePositions);
	closeBox.LoadAnim("ItemBox", "closeBox1", spritePositions);

	return true;
}

bool ItemBox::Start() {

	////initilize textures
	//Boxtexture = app->tex->Load(BoxPath);
	//pbody = app->physics->CreateCircle(position.x + 16, position.y + 16, 16, bodyType::STATIC);
	//pbody->ctype = ColliderType::ITEM;
	//pbody->body->SetFixedRotation(true);

	//currentAnimation = &idle;


	//
	return true;
}

bool ItemBox::Update(float dt)
{
	//
	///*printf("posx%d", position.x);
	//printf("posy%d", position.y);
	//printf("\n");*/
	////printf("hola");
	//// L07 DONE 4: Add a physics to an item - update the position of the object from the physics.  
	//position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	//position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;

	//
	//SDL_Rect rect = currentAnimation->GetCurrentFrame();
	//
	//if (app->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN) {
	//	openBox.Reset();
	//	currentAnimation = &openBox;
	//}
	//if (app->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN) {
	//	closeBox.Reset();
	//	currentAnimation = &closeBox;
	//}
	//
	//app->render->DrawTexture(Boxtexture, position.x, position.y, SDL_FLIP_NONE,&rect);
	////app->render->DrawTexture(Boxtexture, position.x, position.y);
	//currentAnimation->Update();
	//

	return true;
}

bool ItemBox::CleanUp()
{
	return true;
}