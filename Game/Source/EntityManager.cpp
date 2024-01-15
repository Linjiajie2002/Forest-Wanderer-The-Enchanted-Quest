#include "EntityManager.h"
#include "Player.h"
#include "App.h"
#include "Textures.h"
#include "Scene.h"
#include "ItemBox.h"
#include "Effect.h"
#include "Shop.h"
#include "Enemy_Goblin.h"
#include "Enemy_Flyeye.h"
#include "Map.h"
#include "Boss.h"
#include "BossItem.h"
#include "Angel.h"

#include "Defs.h"
#include "Log.h"

EntityManager::EntityManager() : Module()
{
	name.Create("entitymanager");
}

// Destructor
EntityManager::~EntityManager()
{}

// Called before render is available
bool EntityManager::Awake(pugi::xml_node& config)
{
	LOG("Loading Entity Manager");
	bool ret = true;

	//Iterates over the entities and calls the Awake
	ListItem<Entity*>* item;
	Entity* pEntity = NULL;

	for (item = entities.start; item != NULL && ret == true; item = item->next)
	{
		pEntity = item->data;

		if (pEntity->active == false) continue;
		ret = item->data->Awake();
	}

	return ret;

}

bool EntityManager::Start() {

	bool ret = true; 

	//Iterates over the entities and calls Start
	ListItem<Entity*>* item;
	Entity* pEntity = NULL;

	for (item = entities.start; item != NULL && ret == true; item = item->next)
	{
		pEntity = item->data;

		if (pEntity->active == false) continue;
		ret = item->data->Start();
	}

	return ret;
}

// Called before quitting
bool EntityManager::CleanUp()
{
	bool ret = true;
	ListItem<Entity*>* item;
	item = entities.end;

	while (item != NULL && ret == true)
	{
		
		ret = item->data->CleanUp();
		item = item->prev;
	}

	entities.Clear();
	
	return ret;
}

Entity* EntityManager::CreateEntity(EntityType type)
{
	Entity* entity = nullptr; 

	switch (type)
	{
	case EntityType::PLAYER:
		entity = new Player(); 
		break;
	case EntityType::ENEMY_GOBLIN:
		entity = new Enemy_Goblin(); 
		enemys.Add(entity);
		break;
	case EntityType::ENEMY_FLYEYE:
		entity = new Enemy_Flyeye();
		enemys.Add(entity);
		break;
	case EntityType::ITEM:
		entity = new Item();
		break;
	case EntityType::ITEMBOX:
		entity = new ItemBox();
		break;
	case EntityType::SHOP:
		entity = new Shop();
		break;
	case EntityType::EFFECT:
		entity = new Effect();
		break;
	case EntityType::BOSS:
		entity = new Boss();
		break;
	case EntityType::ANGEL:
		entity = new Angel();
		break;
	case EntityType::BOSSITEM:
		entity = new BossItem();
		break;
	case EntityType::PLAYERLIFE:
		entity = new PlayerLife();
		break;
	default:
		break;
	}

	entities.Add(entity);
	return entity;
}

void EntityManager::DestroyEntity(Entity* entity)
{
	ListItem<Entity*>* item;

	for (item = entities.start; item != NULL; item = item->next)
	{
		if (item->data == entity) entities.Del(item);
	}
}

void EntityManager::DestroyAllEntities()
{
	ListItem<Entity*>* item;
	for (item = entities.start; item != NULL; item = item->next)
	{
		entities.Del(item);
	}

}

void EntityManager::AddEntity(Entity* entity)
{
	if ( entity != nullptr) entities.Add(entity);
}

void EntityManager::DestroyAllEnemis()
{
	ListItem<Entity*>* item;
	for (item = enemys.start; item != NULL; item = item->next) 
	{
		ListItem<iPoint>* destroyEnemy;
		for (destroyEnemy = enemys_destroy.start; destroyEnemy != NULL; destroyEnemy = destroyEnemy->next) 
		{
			if (app->map->WorldToMap(destroyEnemy->data.x, destroyEnemy->data.y) == app->map->WorldToMap(item->data->originalposition.x, item->data->originalposition.y))
			{
				item->data->active = false;
			}
		}
		
	}

}

bool EntityManager::Update(float dt)
{
	bool ret = true;
	ListItem<Entity*>* item;
	Entity* pEntity = NULL;

	/*for (item = entities.start; item != NULL && ret == true; item = item->next)
	{
		pEntity = item->data;

		if (pEntity->active == false) continue;
		ret = item->data->Update(dt);
	}*/


	for (item = entities.start; item != NULL && ret == true; item = item->next)
	{
		pEntity = item->data;

		if (pEntity->active == false) {


			item->data->Update(dt);
			continue;
		};
		ret = item->data->Update(dt);
	}

	return ret;
}