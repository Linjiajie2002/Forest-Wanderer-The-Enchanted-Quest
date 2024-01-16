#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Point.h"
#include "SString.h"
#include "Input.h"
#include "Render.h"

class PhysBody;



enum class EntityLifeBarState {
	IDLE,
	DIE,
	TAKEHIT,
	TREATMENT,
	UNKNOWN
};
enum class EntityType
{
	PLAYER,
	PLAYERLIFE,
	ENEMY_FLYEYE,
	ENEMY_GOBLIN,
	BOSS,
	BOSSITEM,
	ANGEL, 
	ITEM,
	DIAMOND,
	ITEMBOX,
	SHOP,
	EFFECT,
	UNKNOWN
};



class Entity
{
public:

	Entity(EntityType type) : type(type), active(true) {}

	virtual bool Awake()
	{
		return true;
	}

	virtual bool Start()
	{
		return true;
	}

	virtual bool Update(float dt)
	{
		return true;
	}

	virtual bool CleanUp()
	{
		return true;
	}

	virtual bool LoadState(pugi::xml_node&)
	{
		return true;
	}

	virtual bool SaveState(pugi::xml_node&)
	{
		return true;
	}

	void Entity::Enable()
	{
		if (!active)
		{
			active = true;
			Start();
		}
	}

	void Entity::Disable()
	{
		if (active)
		{
			active = false;
			CleanUp();
		}
	}

	virtual void OnCollision(PhysBody* physA, PhysBody* physB) {

	};

	virtual void OnEndCollision(PhysBody* physA, PhysBody* physB) {

	};

public:

	SString name;
	EntityType type;
	EntityLifeBarState lifebarState;
	bool active = true;
	pugi::xml_node parameters; 

	// Possible properties, it depends on how generic we
	// want our Entity class, maybe it's not renderable...
	iPoint position;    
	iPoint originalposition;    
	bool renderable = true;
};

#endif // __ENTITY_H__