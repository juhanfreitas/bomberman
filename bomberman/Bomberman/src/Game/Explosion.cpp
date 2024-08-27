#include "Explosion.h"
#include "Bomberman.h"

Explosion::Explosion(float bombX, float bombY)
{
	uint gridX = static_cast<uint>(bombX / 16);
	uint gridY = static_cast<uint>((bombY - Bomberman::scoreboard->Height()) / 16);

	frames = new TileSet("Resources/explosion.png", 48, 48, 13, 13);
	anim = new Animation(frames, 0.120f, false);

	timer.Start();

	type = EXPLOSION;

	Mixed* mixed = new Mixed();
	Rect* rect1 = new Rect(
		-1.0f * frames->TileWidth()/6.0f,
		-1.5f * frames->TileHeight()/3.0f, 
		1.0f * frames->TileWidth() / 6.0f,
		1.5f * frames->TileHeight()/3.0f);

	Rect* rect2 = new Rect(
		-1.5f * frames->TileWidth() / 3.0f,
		-1.0f * frames->TileHeight() / 6.0f,
		1.5f * frames->TileWidth() / 3.0f,
		1.0f * frames->TileHeight() / 6.0f);

	mixed->Insert(rect1);
	mixed->Insert(rect2);

	BBox(mixed);

	MoveTo((gridX * 16.0f) + 8, (gridY * 16.0f) + 8 + Bomberman::scoreboard->Height(), Layer::MIDDLE);
}

Explosion::~Explosion()
{
	delete anim;
	delete frames;
}