#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "Sprite.h"
#include "Debug.h"
#include "Constants.h"
#include "GameObject.h"

using namespace std;

#define MAP_1_ID 0
#define MAP_BOSS_1_ID 1
#define MAP_2_ID 2
#define MAP_BOSS_2_ID 3

struct Tile2 {
	int tileId;
	ObjectType type;
	int x, y;
	int size = TILE_SIZE;
	Collider *colider;
	int SpawnObjectID;
	bool bCanSpawn = true;
};

struct TileSet {
	int id;
	int x;
	int y;
};

struct MapPack {
	int size;
	int height;
	Tile2* tiles;
	vector <TileSet> tileSet;
	vector <Sprite*> TilesSetSprite;

	Sprite* GetSpriteByID(int id)
	{
		if (id != -1)
			return TilesSetSprite.at(id);
		return nullptr;
	}

	Tile2* GetTile(int x, int y)
	{
		return (tiles + x + y * size);
	}
};

class TileMap2
{
private:

	static TileMap2* _instance;

	vector <MapPack> mapList;

	void LoadTilesData(LPCWSTR filePath, LPCWSTR tileSetLocation, int mapId);
	void LoadSpawnData(LPCWSTR filePath, int mapId);

	const vector<int> _BrickStage_1{ 10, 11, 12, 33, 41, 64, 91, 92, 95, 96 };
	const vector<int> _BrickStage_2{ 4, 10, 11, 12, 13, 14, 20, 21, 53, 54, 55, 56, 57, 75, 76, 77, 78, 79, 93, 97, 118, 125, 126, 127, 238, 239, 240, 241, 242, 251, 252 };
	const vector<int> _BrickStage_BOSS_1{ 0, 1, 6, 7, 8, 10 };

	const vector<int> _RopeSwingStage_2{ 60, 61, 73 };

	const vector<int> _WallStage_2{ 32, 33, 44, 45, 65, 66, 67, 95, 96, 98, 99, 100, 101, 102, 103, 109, 112, 113, 114, 115, 116, 117, 133, 137, 172, 173, 215, 218, 222, 223, 224, 225, 226, 248, 249, 250, 261, 262, 263, 264, 265, 276 };

public:
	static TileMap2* GetInstance();
	MapPack* currentMap;

	void SetCurrentMap(int mapID);

	void Render(int x, int y);
	void Render(Tile2* itile);
};