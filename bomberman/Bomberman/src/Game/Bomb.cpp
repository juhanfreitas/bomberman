#include "Bomb.h"
#include "Bomberman.h"
#include "Stage1.h"


Bomb::Bomb(BombType bombType, float playerX, float playerY, uint power) : bombMode(bombType)
{
	explosionPWR = power;
	uint gridX = static_cast<uint>(playerX / 16);
	uint gridY = static_cast<uint>((playerY + 8 - Bomberman::scoreboard->Height()) / 16);
	bombs = new TileSet("Resources/bombs.png", 16, 16, 12, 120);
	anim = new Animation(bombs, 0.250f, true);

	type = BOMB;
	fuseTime = 3.0f;
	state = FUSING;

	timer.Start();

	uint normalBomb[4] = { 0, 1, 2, 3 };
	uint spikeBomb[4] = { 60, 61, 62, 63 };

	anim->Add(NORMAL, normalBomb, 4);
	anim->Add(SPIKE, spikeBomb, 4);

	MoveTo((gridX * 16) + 8, (gridY * 16) + 8 + Bomberman::scoreboard->Height(), Layer::UPPER);
}

Bomb::~Bomb()
{
	delete anim;
	delete bombs;
}

void Bomb::CheckPlayerPosition()
{
	Rect* playerBox = (Rect*)Bomberman::player->BBox();
	if ((abs(playerBox->Left() - (x - 8)) >= 16) || (
		abs(playerBox->Top() - (y - 8)) >= 16))
	{
		BBox(
			new Rect(
				-1.0f * bombs->TileHeight() / 2.0f,
				-1.0f * bombs->TileWidth() / 2.0f,
				bombs->TileHeight() / 2.0f,
				bombs->TileWidth() / 2.0f)
		);
		MoveTo(x, y, Layer::UPPER);
		playerIn = !playerIn;
	}
}

void Bomb::Update()
{
	if (playerIn)
		CheckPlayerPosition();

	if (timer.Elapsed(fuseTime))
		state = READY;

	anim->Select(bombMode);
	anim->NextFrame();
}

void Bomb::Explode()
{
	Explosion* explosion = new Explosion(x, y, BASE);
	Stage1::scene->Add(explosion, MOVING);
	CreateExplosionRange();
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

void Bomb::CreateExplosionRange()
{
	const float posX = x;
	const float posY = y;
	float xpsX = 0, xpsY = 0;

	// top explosions
	for (auto i = 1; i <= explosionPWR; i++)
	{
		xpsY = posY - (i * 16); xpsX = posX;

		if (Stage1::backg->CheckGridPosition(xpsX, xpsY))
		{
			Explosion* explo;
			if (i == explosionPWR)
				explo = new Explosion(xpsX, xpsY, TIP_UP);
			else 
				explo = new Explosion(xpsX, xpsY, BODY_V);
			
			Stage1::scene->Add(explo, MOVING);
		}
		else break;
	}


	// right explosions
	for (auto i = 1; i <= explosionPWR; i++)
	{
		xpsX = posX + (i * 16); xpsY = posY;

		if (Stage1::backg->CheckGridPosition(xpsX, xpsY))
		{
			Explosion* explo;
			if (i == explosionPWR)
				explo = new Explosion(xpsX, xpsY, TIP_RT);
			else
				explo = new Explosion(xpsX, xpsY, BODY_H);

			Stage1::scene->Add(explo, MOVING);
		}
		else break;
	}

	// bottom explosions
	for (auto i = 1; i <= explosionPWR; i++)
	{
		xpsY = posY + (i * 16); xpsX = posX;

		if (Stage1::backg->CheckGridPosition(xpsX, xpsY))
		{
			Explosion* explo;
			if (i == explosionPWR)
				explo = new Explosion(xpsX, xpsY, TIP_DN);
			else
				explo = new Explosion(xpsX, xpsY, BODY_V);

			Stage1::scene->Add(explo, MOVING);
		}
		else break;
	}


	// left explosions
	for (auto i = 1; i <= explosionPWR; i++)
	{
		xpsX = posX - (i * 16); xpsY = posY;

		if (Stage1::backg->CheckGridPosition(xpsX, xpsY))
		{
			Explosion* explo;
			if (i == explosionPWR)
				explo = new Explosion(xpsX, xpsY, TIP_LT);
			else
				explo = new Explosion(xpsX, xpsY, BODY_H);

			Stage1::scene->Add(explo, MOVING);
		}
		else break;
	}
}