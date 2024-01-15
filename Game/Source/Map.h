#ifndef __MAP_H__
#define __MAP_H__

#include "Module.h"
#include "List.h"
#include "Point.h"
#include "Pathfinding.h"

#include "PugiXml\src\pugixml.hpp"

// Ignore Terrain Types and Tile Types for now, but we want the image!
struct TileSet
{
	SString	name;
	int	firstgid;
	int margin;
	int	spacing;
	int	tileWidth;
	int	tileHeight;
	int columns;
	int tilecount;

	SDL_Texture* texture;
	SDL_Rect GetTileRect(int gid) const;
};

//  We create an enum for map type, just for convenience,
// NOTE: Platformer game will be of type ORTHOGONAL
enum MapTypes
{
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};

struct Properties
{
	struct Property
	{
		SString name;
		bool value;
	};

	~Properties()
	{
		//...
		ListItem<Property*>* item;
		item = list.start;

		while (item != NULL)
		{
			RELEASE(item->data);
			item = item->next;
		}

		list.Clear();
	}

	Property* GetProperty(const char* name);

	List<Property*> list;
};

struct MapLayer
{
	SString	name;
	int id; 
	int width;
	int height;
	uint* data;

	uint8 opacity;

	Properties properties;

	MapLayer() : data(NULL)
	{}

	~MapLayer()
	{
		RELEASE(data);
	}

	inline uint Get(int x, int y) const
	{
		return data[(y * width) + x];
	}
};

struct MapObject {

	uint id;
	uint x;
	uint y;
	uint width;
	uint height;
	List<uint> points;
};

struct MapObjects
{
	SString	name;
	int id;
	int x;
	int y;
	int width;
	int height;
	List<MapObject*> objects;

	Properties properties;

};

struct MapData
{
	int width;
	int	height;
	int	tileWidth;
	int	tileHeight;
	List<TileSet*> tilesets;
	MapTypes type;

	List<MapLayer*> maplayers;
	List<MapObjects*> mapObjects;
	

};







class Map : public Module
{
public:

    Map();

    // Destructor
    virtual ~Map();

    // Called before render is available
    bool Awake(pugi::xml_node& conf);

	bool Start();

	// Called each loop iteration
	bool Update(float dt);
	bool UpdateDelante();
	

    // Called before quitting
    bool CleanUp();

    // Load new map
    bool Load();

	void CreateNavigationMap(int& width, int& height, uchar** buffer) const;


	iPoint MapToWorld(int x, int y) const;
	iPoint Map::WorldToMap(int x, int y);

private:

	bool LoadMap(pugi::xml_node mapFile);
	bool LoadTileSet(pugi::xml_node mapFile);
	bool LoadLayer(pugi::xml_node& node, MapLayer* layer);//
	bool LoadAllLayers(pugi::xml_node mapNode);//
	TileSet* GetTilesetFromTileId(int gid) const;
	bool LoadProperties(pugi::xml_node& node, Properties& properties);
	bool LoadCollision(std::string layerName);
	bool LoadEntity(std::string layerName);

public: 



	MapData mapData;
	int fondox;
	int fondoy;


	int LevelMap = 1;

	

	iPoint startPointcolisions = iPoint(-1, -1);
	iPoint colisionsPointsSize = iPoint(-1, -1);
	iPoint colisionsLastCords = iPoint(-1, -1);

	PathFinding* pathfinding;


	int bossRenderArea_R =32;
	int bossRenderArea_L = 18;

	bool deleteWallInbossFight = false;  

private:

    SString mapFileName;
    SString mapFileNameMapa1;
    SString mapFileNameMapa2;
	SString mapFolder;
    bool mapLoaded;
	MapLayer* navigationLayer;
	int blockedGid = 635;
	int blockedGid2 = 627;
	List<PhysBody*> collisionsList;
	List<PhysBody*> traspasedPlatformList;

};

#endif // __MAP_H__