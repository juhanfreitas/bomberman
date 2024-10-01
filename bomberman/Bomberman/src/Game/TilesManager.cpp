#include "TilesManager.h"


TilesManager::TilesManager()
{
	TileSet* blockTiles = new TileSet("Resources/stage/block1.png", 16, 16, 7, 14);
	TileSet* powerTiles = new TileSet("Resources/Sprites/general/power-ups.png", 16, 16, 8, 48);
	TileSet* expldTiles = new TileSet("Resources/Sprites/general/explosions.png", 16, 16, 5, 35);
	TileSet* bombTiles = new TileSet("Resources/Sprites/general/bombs.png", 16, 16, 9, 81);
	TileSet* portTiles = new TileSet("Resources/Sprites/general/portal.png", 16, 16, 4, 4);

	Add(TilesType::TS_BLOCK, blockTiles);
	Add(TilesType::TS_BOMB, bombTiles);
	Add(TilesType::TS_EXPLOSION, expldTiles);
	Add(TilesType::TS_PORTAL, portTiles);
	Add(TilesType::TS_POWERUP, powerTiles);
}

TilesManager::~TilesManager()
{
	delete tiles[TS_BLOCK];
	delete tiles[TS_BOMB];
	delete tiles[TS_EXPLOSION];
	delete tiles[TS_PORTAL];
	delete tiles[TS_POWERUP];
}