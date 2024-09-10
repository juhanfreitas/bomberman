#include "Bomb.h"
#include "Bomberman.h"
#include "Stage1.h"


Bomb::Bomb(Player* owner, BombType bombType, float playerX, float playerY, uint power)
{
	explosionPWR = power;
	playerOwner = owner;
	bombMode = bombType;
	bombKicked = false;
	int gridX = (int)(playerX / 16);
	int gridY = (int)((playerY + 8 - Bomberman::scoreboard->Height()) / 16);
	bombs = new TileSet("Resources/bombs.png", 16, 16, 12, 120);
	anim = new Animation(bombs, 0.250f, true);

	type = BOMB;
	fuseTime = 3.0f;
	state = FUSING;

	timer.Start();

	uint normalBomb[4] = { 0, 1, 2, 3 };
	uint redBomb[4] = { 12, 13, 14, 15 };
	uint timedBomb[2] = { 10, 11 };

	anim->Add(NORMAL, normalBomb, 4);
	anim->Add(R_BOMB, redBomb, 4);
	anim->Add(TIMED, timedBomb, 2);

	MoveTo((gridX * 16) + 8, (gridY * 16) + 8 + Bomberman::scoreboard->Height(), Layer::UPPER);
}

Bomb::~Bomb()
{
	delete anim;
	delete bombs;
}

void Bomb::CheckPlayerPosition()
{
	Rect* playerBox = (Rect*)playerOwner->BBox();
	if ((abs(playerBox->Left() - (x - 8)) >= 16) || (
		abs(playerBox->Top() - (y - 8)) >= 16))
	{
		BBox(
			new Rect(
				-1.0f * bombs->TileHeight() / 2.0f + 1,
				-1.0f * bombs->TileWidth() / 2.0f  + 1 ,
				bombs->TileHeight() / 2.0f - 1,
				bombs->TileWidth() / 2.0f - 1)
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

	if ((state == READY) && (bombMode != TIMED))
		Explode();

	if (bombKicked)
		MoveBomb();

	anim->Select(bombMode);
	anim->NextFrame();
}



void Bomb::Explode()
{
	Explosion* explosion = new Explosion(x, y, BASE);
	Stage1::scene->Add(explosion, MOVING);
	CreateExplosionRange();
	playerOwner->availableBombs += 1;
	Stage1::scene->Delete(this, MOVING);
}



void Bomb::OnCollision(Object* obj)
{
	Rect* objBox = (Rect*)obj->BBox();
	Rect* bmbBox = (Rect*)BBox();
	float diffUp = objBox->Top() - bmbBox->Bottom();
	float diffDn = bmbBox->Top() - objBox->Bottom();
	float diffLt = objBox->Left() - bmbBox->Right();
	float diffRt = bmbBox->Left() - objBox->Right();
	
	switch (obj->Type())
	{
	case EXPLOSION:
		Explode();
		break;
	}
}

void Bomb::MoveBomb()
{
	switch (dirKicked)
	{
	case UP:
		if (Stage1::backg->CheckGridPosition(x, y-9, MPT))
			Translate(0, -speed * gameTime);
		else bombKicked = false;
		break;
	case DOWN:
		if (Stage1::backg->CheckGridPosition(x, y+8, MPT))
			Translate(0, speed * gameTime);
		else bombKicked = false;
		break;
	case LEFT:
		if (Stage1::backg->CheckGridPosition(x-9, y, MPT))
			Translate(-speed * gameTime, 0);
		else bombKicked = false;
		break;
	case RIGHT:
		if (Stage1::backg->CheckGridPosition(x+8, y, MPT))
			Translate(speed * gameTime, 0);
		else bombKicked = false;
		break;
	default:
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

		if (Stage1::backg->CheckGridPosition(xpsX, xpsY, MPT))
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
	// -----------------------------------------------------------------

	// right explosions
	for (auto i = 1; i <= explosionPWR; i++)
	{
		xpsX = posX + (i * 16); xpsY = posY;

		if (Stage1::backg->CheckGridPosition(xpsX, xpsY, MPT))
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
	// -----------------------------------------------------------------

	// bottom explosions
	for (auto i = 1; i <= explosionPWR; i++)
	{
		xpsY = posY + (i * 16); xpsX = posX;

		if (Stage1::backg->CheckGridPosition(xpsX, xpsY, MPT))
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
	// -----------------------------------------------------------------

	// left explosions
	for (auto i = 1; i <= explosionPWR; i++)
	{
		xpsX = posX - (i * 16); xpsY = posY;

		if (Stage1::backg->CheckGridPosition(xpsX, xpsY, MPT))
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
	// -----------------------------------------------------------------
}