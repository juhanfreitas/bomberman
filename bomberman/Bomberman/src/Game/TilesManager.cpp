#include "TilesManager.h"


TilesManager::TilesManager()
{
	TileSet* blockTiles = new TileSet("Resources/stage/block1.png", 16, 16, 7, 14);
	TileSet* powerTiles = new TileSet("Resources/power-ups.png", 16, 16, 8, 48);
	TileSet* bombTiles = new TileSet("Resources/bombs.png", 16, 16, 12, 120);

	Add(TilesType::TS_BLOCK, blockTiles);
	Add(TilesType::TS_BOMB, bombTiles);
	Add(TilesType::TS_EXPLOSION, bombTiles);
	Add(TilesType::TS_POWERUP, powerTiles);
}

TilesManager::~TilesManager()
{
	delete tiles[TS_BLOCK];
	delete tiles[TS_BOMB];
	delete tiles[TS_EXPLOSION];
	delete tiles[TS_POWERUP];
}