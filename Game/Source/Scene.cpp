#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "Effect.h"
#include "Enemy_Goblin.h"
#include "Enemy_Flyeye.h"
#include "Boss.h"
#include "BossItem.h"
#include "PlayerLife.h"
#include "Angel.h"
#include "Diamond.h"
#include "Cura.h"
#include "Teleport.h"
#include "GuiControl.h"
#include "GuiManager.h"
#include "GuiControlButton.h"

#include "Defs.h"
#include "Log.h"
#include <map>

Scene::Scene(bool start_Enabled) : Module(start_Enabled)
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
	/*if (IsEnabled()) {*/
	if (app->map->LevelMap == 1) {
		for (pugi::xml_node itemNode = config.child("nivel_1"); itemNode; itemNode = itemNode.next_sibling("nivel_1")) {

			if (config.child("nivel_1").child("player")) {
				player = (Player*)app->entityManager->CreateEntity(EntityType::PLAYER);
				player->parameters = config.child("nivel_1").child("player");
			}

			PathfindingPath = config.child("nivel_1").child("Pathfinding").attribute("texturepath").as_string();

			for (pugi::xml_node itemNode = config.child("nivel_1").child("enemy").child("Enemy_Goblin"); itemNode; itemNode = itemNode.next_sibling("Enemy_Goblin"))
			{
				enemy_goblin = (Enemy_Goblin*)app->entityManager->CreateEntity(EntityType::ENEMY_GOBLIN);
				enemy_goblin->parameters = itemNode;
			}

			for (pugi::xml_node itemNode = config.child("nivel_1").child("enemy").child("Enemy_Flyeye"); itemNode; itemNode = itemNode.next_sibling("Enemy_Flyeye"))
			{
				Enemy_Flyeye* enemy_flyeye = (Enemy_Flyeye*)app->entityManager->CreateEntity(EntityType::ENEMY_FLYEYE);
				enemy_flyeye->parameters = itemNode;
			}



			for (pugi::xml_node itemNode = config.child("nivel_1").child("item"); itemNode; itemNode = itemNode.next_sibling("item"))
			{
				item = (Item*)app->entityManager->CreateEntity(EntityType::ITEM);
				item->parameters = itemNode;
			}

			for (pugi::xml_node itemNode = config.child("nivel_1").child("effect"); itemNode; itemNode = itemNode.next_sibling("effect"))
			{
				effect = (Effect*)app->entityManager->CreateEntity(EntityType::EFFECT);
				effect->parameters = itemNode;
			}

			for (pugi::xml_node itemNode = config.child("nivel_1").child("playerlife"); itemNode; itemNode = itemNode.next_sibling("playerlife"))
			{
				playerlife = (PlayerLife*)app->entityManager->CreateEntity(EntityType::PLAYERLIFE);
				playerlife->parameters = itemNode;
			}
			for (pugi::xml_node itemNode = config.child("nivel_1").child("Cura").child("Cura"); itemNode; itemNode = itemNode.next_sibling("Cura"))
			{
				cura = (Cura*)app->entityManager->CreateEntity(EntityType::CURA);
				cura->parameters = itemNode;
			}
			for (pugi::xml_node itemNode = config.child("nivel_1").child("Diamond").child("Diamond"); itemNode; itemNode = itemNode.next_sibling("Diamond"))
			{
				diamond = (Diamond*)app->entityManager->CreateEntity(EntityType::DIAMOND);
				diamond->parameters = itemNode;
			}
			for (pugi::xml_node itemNode = config.child("nivel_1").child("Teleport").child("Teleport"); itemNode; itemNode = itemNode.next_sibling("Teleport"))
			{
				teleport = (Teleport*)app->entityManager->CreateEntity(EntityType::TELEPORT);
				teleport->parameters = itemNode;
			}
		}
	}


	if (app->map->LevelMap == 2) {
		for (pugi::xml_node itemNode = config.child("nivel_2"); itemNode; itemNode = itemNode.next_sibling("nivel_2")) {


			if (config.child("nivel_2").child("player")) {
				player = (Player*)app->entityManager->CreateEntity(EntityType::PLAYER);
				player->parameters = config.child("nivel_2").child("player");
			}

			PathfindingPath = config.child("nivel_2").child("Pathfinding").attribute("texturepath").as_string();

			for (pugi::xml_node itemNode = config.child("nivel_2").child("Diamond").child("Diamond"); itemNode; itemNode = itemNode.next_sibling("Diamond"))
			{
				diamond = (Diamond*)app->entityManager->CreateEntity(EntityType::DIAMOND);
				diamond->parameters = itemNode;
			}


			for (pugi::xml_node itemNode = config.child("nivel_2").child("effect"); itemNode; itemNode = itemNode.next_sibling("effect"))
			{
				effect = (Effect*)app->entityManager->CreateEntity(EntityType::EFFECT);
				effect->parameters = itemNode;
			}

			for (pugi::xml_node itemNode = config.child("nivel_2").child("item"); itemNode; itemNode = itemNode.next_sibling("item"))
			{
				item = (Item*)app->entityManager->CreateEntity(EntityType::ITEM);
				item->parameters = itemNode;
			}

			for (pugi::xml_node itemNode = config.child("nivel_2").child("angel"); itemNode; itemNode = itemNode.next_sibling("angel"))
			{
				angel = (Angel*)app->entityManager->CreateEntity(EntityType::ANGEL);
				angel->parameters = itemNode;
			}

			for (pugi::xml_node itemNode = config.child("nivel_2").child("boss"); itemNode; itemNode = itemNode.next_sibling("boss"))
			{
				boss = (Boss*)app->entityManager->CreateEntity(EntityType::BOSS);
				boss->parameters = itemNode;
			}



			for (pugi::xml_node itemNode = config.child("nivel_2").child("bossitem"); itemNode; itemNode = itemNode.next_sibling("bossitem"))
			{
				bossitem = (BossItem*)app->entityManager->CreateEntity(EntityType::BOSSITEM);
				bossitem->parameters = itemNode;
			}



			for (pugi::xml_node itemNode = config.child("nivel_2").child("playerlife"); itemNode; itemNode = itemNode.next_sibling("playerlife"))
			{
				playerlife = (PlayerLife*)app->entityManager->CreateEntity(EntityType::PLAYERLIFE);
				playerlife->parameters = itemNode;
			}

			for (pugi::xml_node itemNode = config.child("nivel_2").child("Cura").child("Cura"); itemNode; itemNode = itemNode.next_sibling("Cura"))
			{
				cura = (Cura*)app->entityManager->CreateEntity(EntityType::CURA);
				cura->parameters = itemNode;
			}

			for (pugi::xml_node itemNode = config.child("nivel_2").child("Teleport").child("Teleport"); itemNode; itemNode = itemNode.next_sibling("Teleport"))
			{
				teleport = (Teleport*)app->entityManager->CreateEntity(EntityType::TELEPORT);
				teleport->parameters = itemNode;
			}
		}
	}

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	// NOTE: We have to avoid the use of paths in the code, we will move it later to a config file
	//img = app->tex->Load("Assets/Textures/test.png");

	//Music is commented so that you can add your own music
	app->audio->PlayMusic("Assets/Audio/Music/musica.ogg");

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


	}

	if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) {
		printf("Save");
		app->SaveRequest();
	}
	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) {
		printf("Load");
		playerlife->newmap = false;
		app->LoadRequest();
		playerlife->newmap = true;
	}

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
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
PlayerLife* Scene::GetPlayerLife()
{
	return playerlife;
}

Angel* Scene::GetAngel()
{
	return angel;
}

Item* Scene::GetItem()
{
	return item;
}

BossItem* Scene::GetBossItem()
{
	return bossitem;
}

Diamond* Scene::GetDiamond()
{
	return diamond;
}

Cura* Scene::GetCura()
{
	return cura;
}

bool Scene::LoadState(pugi::xml_node node) {

	LOG("Antes: x: %d y: %d", player->position.x, player->position.y);


	if (playerlife->newmap == false) {
		playerlife->life = node.child("player").attribute("life").as_int();
		item->playerGetDiamante = node.child("player").attribute("Diamond").as_int();
		player->position.x = node.child("player").attribute("x").as_int();
		player->position.y = node.child("player").attribute("y").as_int();
		player->dieCount = node.child("player").attribute("dieCount").as_int();
	}
	else {

		
		player->position.x = node.child("player").attribute("x").as_int();
		player->position.y = node.child("player").attribute("y").as_int();
		player->dieCount = node.child("player").attribute("dieCount").as_int();
		playerlife->life = node.child("player").attribute("life").as_int();
		item->playerGetDiamante = node.child("player").attribute("Diamond").as_int();
		if (player->pbody != nullptr) {
			player->pbody->body->SetTransform(b2Vec2(PIXEL_TO_METERS(player->position.x), PIXEL_TO_METERS(player->position.y)), 0);
		}
		LOG("Despues: x: %d y: %d", player->position.x, player->position.y);
		LOG("aaaaaaaaaaaaa %d", node.child("player").attribute("x").as_int());
		for (pugi::xml_node itemNode = node.child("enemies").child("enemy"); itemNode; itemNode = itemNode.next_sibling("enemy"))
		{
			if (!itemNode.attribute("active").as_bool()) {
				app->entityManager->enemys_destroy.Add(iPoint(itemNode.attribute("x").as_int(), itemNode.attribute("y").as_int()));

			}
		}
		app->entityManager->DestroyAllEnemis();
	}

	return true;

}

bool Scene::SaveState(pugi::xml_node node) {
	pugi::xml_node playerNode = node.append_child("player");


	if (app->scenemenu->GetGuiControlButton()->newgame) {

		playerNode.append_attribute("x").set_value(player->position.x);
		playerNode.append_attribute("y").set_value(player->position.y);
		playerNode.append_attribute("life").set_value(10);
		playerNode.append_attribute("Diamond").set_value(0);
		if (!player->hasDie) {
			playerNode.append_attribute("dieCount").set_value(player->dieCount);
		}
		else {
			player->hasDie = false;
		}
		//playerNode.append_attribute("sceneLevel").set_value(app->sceneLevel);

		pugi::xml_node enemyListNode = node.append_child("enemies");
		for (int i = 0; i < app->entityManager->enemys.Count(); i++) {

			pugi::xml_node enemyNode = enemyListNode.append_child("enemy");


			enemyNode.append_attribute("x").set_value(app->entityManager->enemys.At(i)->data->originalposition.x);
			enemyNode.append_attribute("y").set_value(app->entityManager->enemys.At(i)->data->originalposition.y);
			enemyNode.append_attribute("active").set_value(app->entityManager->enemys.At(i)->data->active);

		}
		app->scenemenu->GetGuiControlButton()->newgame = false;
	}
	else {

		playerNode.append_attribute("x").set_value(player->position.x);
		playerNode.append_attribute("y").set_value(player->position.y);
		playerNode.append_attribute("life").set_value(playerlife->life);
		playerNode.append_attribute("Diamond").set_value(item->playerGetDiamante);
		printf("dddddd");
		if (!player->hasDie) {
			playerNode.append_attribute("dieCount").set_value(player->dieCount);
		}
		else {
			player->hasDie = false;
		}
		

		//playerNode.append_attribute("sceneLevel").set_value(app->sceneLevel);

		pugi::xml_node enemyListNode = node.append_child("enemies");
		for (int i = 0; i < app->entityManager->enemys.Count(); i++) {

			pugi::xml_node enemyNode = enemyListNode.append_child("enemy");


			enemyNode.append_attribute("x").set_value(app->entityManager->enemys.At(i)->data->originalposition.x);
			enemyNode.append_attribute("y").set_value(app->entityManager->enemys.At(i)->data->originalposition.y);
			enemyNode.append_attribute("active").set_value(app->entityManager->enemys.At(i)->data->active);

		}
	}
	/*}*/
	//playerlife->newmap = true;
	return true;

}
