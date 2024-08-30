#include "Bomb.h"
#include "Bomberman.h"


Bomb::Bomb(BombType bombType, float playerX, float playerY) : bombMode(bombType)
{
	uint gridX = static_cast<uint>(playerX / 16);
	uint gridY = static_cast<uint>((playerY + 8 - Bomberman::scoreboard->Height()) / 16);
	bombs = new TileSet("Resources/bombs.png", 16, 16, 8, 64);
	anim = new Animation(bombs, 0.320f, true);

	type = BOMB;
	fuseTime = 3.0f;
	state = FUSING;

	timer.Start();

	uint normalBomb[4] = { 0, 1, 2, 3 };
	uint spikeBomb[4] = { 60, 61, 62, 63 };

	anim->Add(NORMAL, normalBomb, 4);
	anim->Add(SPIKE, spikeBomb, 4);

	MoveTo((gridX * 16.0f) + 8, (gridY * 16.0f) + 8 + Bomberman::scoreboard->Height(), Layer::LOWER);
}

Bomb::~Bomb()
{
	delete anim;
	delete bombs;
}

void Bomb::CheckPlayerPosition()
{
	Rect* playerBox = (Rect*)Bomberman::player->BBox();
	int gridX = static_cast<int>(x / 16);
	int gridY = static_cast<int>((y - (Bomberman::scoreboard->Height())) / 16);

	if (
		(static_cast<int>((playerBox->Right() - 1)/16) - gridX > 1 ||
		gridX - static_cast<int>((playerBox->Left() + 1)/ 16) > 1) ||
		static_cast<int>((playerBox->Bottom() - Bomberman::scoreboard->Height() - 1) / 16) - gridY > 1 ||
		gridY - static_cast<int>((playerBox->Top() - Bomberman::scoreboard->Height() + 1) / 16) > 1
	) {
		hasCollision = true;

		BBox(new Rect(
			-1.0f * bombs->TileHeight() / 2.0f,
			-1.0f * bombs->TileWidth() / 2.0f,
			bombs->TileHeight() / 2.0f,
			bombs->TileWidth() / 2.0f
		));

		MoveTo((gridX * 16.0f) + 8, (gridY * 16.0f) + 8 + Bomberman::scoreboard->Height(), Layer::LOWER);
	}
}

void Bomb::Update()
{
	if (!hasCollision)
		CheckPlayerPosition();

	if (timer.Elapsed(fuseTime))
		state = READY;

	anim->Select(bombMode);
	anim->NextFrame();
}

void Bomb::Explode(uint power)
{
	Explosion* explosion = new Explosion(x, y, power);
	Stage1::scene->Add(explosion, MOVING);
	Stage1::scene->Delete(this, STATIC);
}

void Bomb::OnCollision(Object* obj)
{
	switch (obj->Type())
	{
	case EXPLOSION:
		state = READY;
		break;
	}
}