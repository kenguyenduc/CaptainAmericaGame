#include "TileMap2.h"

TileMap2* TileMap2::_instance = nullptr;

TileMap2 * TileMap2::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = new TileMap2();

		_instance->LoadTilesData(TILES_MATRIX_STAGE_1, TILES_SET_MATRIX_STAGE_1, MAP_1_ID);
		_instance->LoadSpawnData(ENEMIES_MATRIX_STAGE_1, MAP_1_ID);
		_instance->LoadTilesData(TILES_MATRIX_STAGE_BOSS_1, TILES_SET_STAGE_BOSS_1, MAP_BOSS_1_ID);
		_instance->LoadTilesData(TILES_MATRIX_STAGE_2, TILES_SET_MATRIX_STAGE_2, MAP_2_ID);
		_instance->LoadSpawnData(ENEMIES_MATRIX_STAGE_2, MAP_2_ID);
		_instance->LoadTilesData(TILES_MATRIX_STAGE_BOSS_2, TILES_SET_STAGE_BOSS_2, MAP_BOSS_2_ID);
	}
	return _instance;
}

void TileMap2::LoadTilesData(LPCWSTR filePath, LPCWSTR tileSetLocation, int mapId)
{
	MapPack map;

	ifstream tilesData;
	tilesData.open(filePath);

	string data;

	tilesData >> data;
	int size = stoi(data);

	map.size = size;

	tilesData >> data;
	map.height = stoi(data);

	map.tiles = new Tile2[size*size];

	for (int y = map.height - 1; y >= 0; y--)
		for (int x = 0; x < map.size; x++)
		{
			tilesData >> data;
			(map.tiles + x + y * size)->tileId = stoi(data);

			switch (mapId)
			{
			case MAP_1_ID:
			{
				if (find(_BrickStage_1.begin(), _BrickStage_1.end(), (map.tiles + x + y * size)->tileId) != _BrickStage_1.end())
				{
					(map.tiles + x + y * size)->type = ObjectType::BRICK;
				}
				if ((map.tiles + x + y * size)->tileId == 100)
				{
					(map.tiles + x + y * size)->type = ObjectType::RIVER;
				}
				if ((map.tiles + x + y * size)->tileId == 52 || (map.tiles + x + y * size)->tileId == 53)
				{
					(map.tiles + x + y * size)->type = ObjectType::WALL;
				}
			}
			break;
			case MAP_BOSS_1_ID:
			{
				if (find(_BrickStage_BOSS_1.begin(), _BrickStage_BOSS_1.end(), (map.tiles + x + y * size)->tileId) != _BrickStage_BOSS_1.end())
				{
					(map.tiles + x + y * size)->type = ObjectType::BRICK;
				}
			}
			break;
			case MAP_2_ID:
			{
				if (find(_BrickStage_2.begin(), _BrickStage_2.end(), (map.tiles + x + y * size)->tileId) != _BrickStage_2.end())
				{
					(map.tiles + x + y * size)->type = ObjectType::BRICK;
				}
				if (find(_RopeSwingStage_2.begin(), _RopeSwingStage_2.end(), (map.tiles + x + y * size)->tileId) != _RopeSwingStage_2.end())
				{
					(map.tiles + x + y * size)->type = ObjectType::ROPE_SWING;
				}
				if ((map.tiles + x + y * size)->tileId == 161 || (map.tiles + x + y * size)->tileId == 162 || (map.tiles + x + y * size)->tileId == 163)
				{
					(map.tiles + x + y * size)->type = ObjectType::THORN;
				}
				if (find(_WallStage_2.begin(), _WallStage_2.end(), (map.tiles + x + y * size)->tileId) != _WallStage_2.end())
				{
					(map.tiles + x + y * size)->type = ObjectType::WALL;
				}
			}
			break;
			case MAP_BOSS_2_ID:
			{
				if ((map.tiles + x + y * size)->tileId == 1)
				{
					(map.tiles + x + y * size)->type = ObjectType::BRICK;
				}
			}
			break;
			}

			(map.tiles + x + y * size)->x = x;
			(map.tiles + x + y * size)->y = y;
		}

	for (int y = map.size - 1; y > map.height - 1; y--)
		for (int x = 0; x < map.size; x++)
		{
			(map.tiles + x + y * size)->tileId = -1;
			(map.tiles + x + y * size)->x = x;
			(map.tiles + x + y * size)->y = y;
		}

	tilesData.close();

	// Load Tile Set
	D3DXIMAGE_INFO info;

	D3DXGetImageInfoFromFile(tileSetLocation, &info);

	for (int i = 0; i < info.Width / TILE_SIZE; i++)
	{
		RECT rect;
		rect.left = i * TILE_SIZE;
		rect.right = rect.left + TILE_SIZE;
		rect.top = 0;
		rect.bottom = rect.top + TILE_SIZE;

		Sprite *tempTile = new Sprite(tileSetLocation, rect, TILES_TRANSCOLOR);
		map.TilesSetSprite.push_back(tempTile);
	}
	mapList.push_back(map);
	//currentMap = &mapList.at(0);
}

void TileMap2::LoadSpawnData(LPCWSTR filePath, int mapId)
{
	ifstream tilesData;
	tilesData.open(filePath);

	string data;

	//Lấy kích thước map. Dư có thể bỏ
	tilesData >> data;
	//int size = stoi(data);

	//
	//map.size = size;

	//Lấy kích thước map. Dư có thể bỏ//
	tilesData >> data;
	//map.height = stoi(data);

	for (int y = mapList[mapId].height - 1; y >= 0; y--)
		for (int x = 0; x < mapList[mapId].size; x++)
		{
			tilesData >> data;
			(mapList[mapId].tiles + x + y * mapList[mapId].size)->SpawnObjectID = stoi(data);
		}

	tilesData.close();
}

void TileMap2::SetCurrentMap(int mapID)
{
	currentMap = &mapList[mapID];
}

void TileMap2::Render(int x, int y)
{
	if (currentMap->GetTile(x, y)->tileId == -1)
		return;

	SpriteData spriteData;
	spriteData.width = TILE_SIZE;
	spriteData.height = TILE_SIZE;
	spriteData.x = x * TILE_SIZE;
	spriteData.y = y * TILE_SIZE;
	spriteData.isLeft = true;


	currentMap->GetSpriteByID(currentMap->GetTile(x, y)->tileId)->SetData(spriteData);

	Graphics::GetInstance()->Draw(currentMap->GetSpriteByID(currentMap->GetTile(x, y)->tileId));
}

void TileMap2::Render(Tile2* itile)
{
	if (itile->tileId == -1)
		return;

	SpriteData spriteData;
	spriteData.width = TILE_SIZE;
	spriteData.height = TILE_SIZE;
	spriteData.x = itile->x * TILE_SIZE;
	spriteData.y = itile->y * TILE_SIZE;

	spriteData.isLeft = true;


	Sprite* temp = currentMap->GetSpriteByID(itile->tileId);
	temp->SetData(spriteData);


	Graphics::GetInstance()->Draw(temp);
}


