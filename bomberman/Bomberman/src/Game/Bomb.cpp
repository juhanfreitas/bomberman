#include "Bomb.h"

Bomb::Bomb(BombType bombType, float x, float y)
{
	MoveTo(x, y, Layer::FRONT);
	
	bombs = new TileSet("Resources/bombs.png", 16, 16, 8, 8);
	anim = new Animation(bombs, 120.0f, true, 2.0f);
	type = bombType;

	uint normalBomb[4] = {0, 1, 2, 3};
	uint spikeBomb[4] = {60, 61, 62, 63};

	anim->Add(NORMAL, normalBomb, 4);
	anim->Add(SPIKE, spikeBomb, 4);

}

Bomb::~Bomb()
{
	delete anim;
	delete bombs;
}


