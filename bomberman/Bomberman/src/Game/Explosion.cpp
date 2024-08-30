#include "Explosion.h"
#include "Bomberman.h"
#include "Stage1.h"

Explosion::Explosion(float bombX, float bombY, uint explosionPower)
{
	int gridX = static_cast<int>(bombX / 16);
	int gridY = static_cast<int>((bombY - Bomberman::scoreboard->Height()) / 16);

	frames = new TileSet("Resources/explosion.png", 48, 48, 12, 12);
	anim = new Animation(frames, 0.100f, false);

	type = EXPLOSION;

	Mixed* mixed = new Mixed();
	Rect* rect1 = new Rect(
		-0.9f * frames->TileWidth()/6.0f,
		-(0.4f + explosionPower) * frames->TileHeight()/3.0f,
		0.9f * frames->TileWidth() / 6.0f,
		(0.4f + explosionPower) * frames->TileHeight()/3.0f);

	Rect* rect2 = new Rect(
		-(0.4f + explosionPower) * frames->TileWidth() / 3.0f,
		-0.9f * frames->TileHeight() / 6.0f,
		(0.4f + explosionPower) * frames->TileWidth() / 3.0f,
		0.9f * frames->TileHeight() / 6.0f);

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

void Explosion::Update()
{
	anim->NextFrame();
	if (anim->Inactive())
		Stage1::scene->Delete(this, MOVING);
}

void Explosion::OnCollision(Object * obj) {
	switch (obj->Type()) {
	case BLOCK:
		Stage1::scene->Delete(obj, MOVING);
		break;
	}
}