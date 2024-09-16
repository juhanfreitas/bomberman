#pragma once
#ifndef _TILES_MANAGER_H_
#define _TILES_MANAGER_H_

#include "../Engine/Types.h"
#include "../Engine/TileSet.h"
#include <unordered_map>

using std::unordered_map;
using TilesHashTable = unordered_map<uint, TileSet*>;

enum TilesType { TS_BLOCK, TS_BOMB, TS_EXPLOSION, TS_POWERUP };

class TilesManager
{
private:

	TilesHashTable tiles;

	void Add(TilesType type, TileSet* tileSet);

public:

	TilesManager();
	~TilesManager();

	TileSet* GetTilesOf(TilesType type);
};

inline void TilesManager::Add(TilesType type, TileSet* tileSet)
{
	tiles[type] = tileSet;
}

inline TileSet* TilesManager::GetTilesOf(TilesType type)
{
	return tiles[type];
}
#endif