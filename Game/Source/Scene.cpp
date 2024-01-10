#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "ItemBox.h"
#include "Effect.h"
#include "Shop.h"
#include "Enemy_Goblin.h"
#include "Enemy_Flyeye.h"
#include "Boss.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	// iterate all objects in the scene
	// Check https://pugixml.org/docs/quickstart.html#access
	for (pugi::xml_node itemNode = config.child("item"); itemNode; itemNode = itemNode.next_sibling("item"))
	{
		Item* item = (Item*)app->entityManager->CreateEntity(EntityType::ITEM);
		item->parameters = itemNode;
	}

	//Add itembox
	for (pugi::xml_node itemNode = config.child("itembox"); itemNode; itemNode = itemNode.next_sibling("itembox"))
	{
		ItemBox* itembox = (ItemBox*)app->entityManager->CreateEntity(EntityType::ITEMBOX);
		itembox->parameters = itemNode;
	}

	for (pugi::xml_node itemNode = config.child("shop"); itemNode; itemNode = itemNode.next_sibling("shop"))
	{
		Shop* shop = (Shop*)app->entityManager->CreateEntity(EntityType::SHOP);
		shop->parameters = itemNode;
	}

	for (pugi::xml_node itemNode = config.child("enemy").child("Enemy_Goblin"); itemNode; itemNode = itemNode.next_sibling("Enemy_Goblin"))
	{
		enemy_goblin = (Enemy_Goblin*)app->entityManager->CreateEntity(EntityType::ENEMY_GOBLIN);
		enemy_goblin->parameters = itemNode;
	}

	for (pugi::xml_node itemNode = config.child("enemy").child("Enemy_Flyeye"); itemNode; itemNode = itemNode.next_sibling("Enemy_Flyeye"))
	{
		Enemy_Flyeye* enemy_flyeye = (Enemy_Flyeye*)app->entityManager->CreateEntity(EntityType::ENEMY_FLYEYE);
		enemy_flyeye->parameters = itemNode;
	}


	



	PathfindingPath = config.child("enemy").child("Pathfinding").attribute("texturepath").as_string();
	
	

	if (config.child("player")) {
		player = (Player*)app->entityManager->CreateEntity(EntityType::PLAYER);
		player->parameters = config.child("player");
	}


	for (pugi::xml_node itemNode = config.child("boss"); itemNode; itemNode = itemNode.next_sibling("boss"))
	{
		boss = (Boss*)app->entityManager->CreateEntity(EntityType::BOSS);
		boss->parameters = itemNode;
	}

	//Add effect
	for (pugi::xml_node itemNode = config.child("effect"); itemNode; itemNode = itemNode.next_sibling("effect"))
	{
		effect = (Effect*)app->entityManager->CreateEntity(EntityType::EFFECT);
		effect->parameters = itemNode;
	}
	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	// NOTE: We have to avoid the use of paths in the code, we will move it later to a config file
	//img = app->tex->Load("Assets/Textures/test.png");
	
	//Music is commented so that you can add your own music
	//app->audio->PlayMusic("Assets/Audio/Music/music_spy.ogg");

	//Get the size of the window
	app->win->GetWindowSize(windowW, windowH);

	//Get the size of the texture
	app->tex->GetSize(img, texW, texH);

	textPosX = (float)windowW / 2 - (float)texW / 2;
	textPosY = (float)windowH / 2 - (float)texH / 2;

	app->map->Load();

	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
		app->map->mapData.width,
		app->map->mapData.height,
		app->map->mapData.tileWidth,
		app->map->mapData.tileHeight,
		app->map->mapData.tilesets.Count());


	Pathfindingtexture = app->tex->Load(PathfindingPath);
	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{


	if (app->godMode && app->scene->player->MoveCamere == true) {
		float camSpeed = 1;

		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
			app->render->camera.y += (int)ceil(camSpeed * dt);

		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
			app->render->camera.y -= (int)ceil(camSpeed * dt);

		if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
			app->render->camera.x += (int)ceil(camSpeed * dt);

		if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
			app->render->camera.x -= (int)ceil(camSpeed * dt);

		// Renders the image in the center of the screen 
		//app->render->DrawTexture(img, (int)textPosX, (int)textPosY);

	}

	if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) {
		printf("Save");
		app->SaveRequest();
	}
	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) {
		printf("Load");
		app->LoadRequest();
	}


	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{

	LOG("Freeing scene");

	return true;
}

Player* Scene::GetPlayer() {

	return player;
}

Effect* Scene::GetEffect() {

	return effect;
}

Enemy_Goblin* Scene::GetGoblin() {

	return enemy_goblin;
}



Boss* Scene::GetBoss() {

	return boss;
}
bool Scene::LoadState(pugi::xml_node node) {

	/*if (app->sceneLevel != node.child("player").attribute("sceneLevel").as_int()) {
		app->sceneLevel = node.child("player").attribute("sceneLevel").as_int();
		app->fadetoBlack->FadetoBlackTransition(app->screne, app->scene);

	}
	else {
		player->position.x = node.child("player").attribute("x").as_int();
		player->position.y = node.child("player").attribute("y").as_int();
		player->SetPosition(node.child("player").attribute("x").as_int(), node.child("player").attribute("y").as_int());
		app->scenelevel = node.child("player").attribute("sceneLevel").as_int();
	}*/

	LOG("Antes: x: %d y: %d", player->position.x, player->position.y);
	

	player->position.x = node.child("player").attribute("x").as_int();
	player->position.y = node.child("player").attribute("y").as_int();
	player->pbody->body->SetTransform(b2Vec2(PIXEL_TO_METERS(node.child("player").attribute("x").as_int()), PIXEL_TO_METERS(node.child("player").attribute("y").as_int())), 0);
	
	LOG("Despues: x: %d y: %d", player->position.x, player->position.y);
	LOG("aaaaaaaaaaaaa %d", node.child("player").attribute("x").as_int());
	for (pugi::xml_node itemNode = node.child("enemies").child("enemy"); itemNode; itemNode = itemNode.next_sibling("enemy"))
	{
		if (!itemNode.attribute("active").as_bool()) {
			app->entityManager->enemys_destroy.Add(iPoint(itemNode.attribute("x").as_int(), itemNode.attribute("y").as_int()));

		}
	}
	app->entityManager->DestroyAllEnemis();
	return true;

}

bool Scene::SaveState(pugi::xml_node node) {

	
	pugi::xml_node playerNode = node.append_child("player");
	playerNode.append_attribute("x").set_value(player->position.x);
	playerNode.append_attribute("y").set_value(player->position.y);
	//playerNode.append_attribute("sceneLevel").set_value(app->sceneLevel);

	pugi::xml_node enemyListNode = node.append_child("enemies");
	for (int i = 0; i < app->entityManager->enemys.Count(); i++) {
		
		pugi::xml_node enemyNode = enemyListNode.append_child("enemy");


		enemyNode.append_attribute("x").set_value(app->entityManager->enemys.At(i)->data->originalposition.x);
		enemyNode.append_attribute("y").set_value(app->entityManager->enemys.At(i)->data->originalposition.y);
		enemyNode.append_attribute("active").set_value(app->entityManager->enemys.At(i)->data->active);

	}

	return true;

}
