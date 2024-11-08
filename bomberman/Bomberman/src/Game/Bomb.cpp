#include "Bomb.h"
#include "Stage1.h"
#include "Bomberman.h"
#include "math.h"


Bomb::Bomb(Player* owner, BombType bombType, float playerX, float playerY, uint power) : playerOwner(owner)
{
	explosionPWR = power;
	bombMode = bombType;
	bombKicked = false;
	bombs = Bomberman::tiles->GetTilesOf(TS_BOMB);
	anim = new Animation(bombs, 0.250f, true);
	type = ObjTypes::BOMB;
	fuseTime = 3.0f;
	state = FUSING;

	timer.Start();

	uint normalBomb[4] = { 0, 1, 2, 3 };
	uint redBomb[4] = { 9, 10, 11, 12};
	uint timedBomb[2] = { 5, 6 };

	anim->Add(NORMAL, normalBomb, 4);
	anim->Add(R_BOMB, redBomb, 4);
	anim->Add(TIMED, timedBomb, 2);

	float start = Stage1::gameview.left;
	int firstBlockGrid = (int)(start / 16);
	float diff = (firstBlockGrid * 16) - start;
	
	if (trunc(diff) != 0)
	{
		if (abs(diff) >= 8)	diff = start - ((firstBlockGrid * 16) + 16);
		else diff = abs(diff);
	}

	int gridX = (int)(owner->X() / 16);
	int gridY = (int)((owner->Y() + 8 - 32) / 16);

	float posX = (gridX * 16) + 8 - diff;
	float posY = ((gridY * 16) + 8 + 32);
	MoveTo(posX, posY);
}


Bomb::~Bomb()
{
	delete anim;
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

	Translate(Bomberman::xdiff, 0);

	anim->Select(bombMode);
	anim->NextFrame();
}


void Bomb::Explode()
{
	Explosion* explosion = new Explosion(x, y, BASE);
	Stage1::scene->Add(explosion, MOVING);
	Bomberman::audioManager->Play(SE_BOMBEXPLOSION);
	Bomberman::audioManager->Volume(SE_BOMBEXPLOSION, Bomberman::SEVolume);
	CreateExplosionRange();
	playerOwner->bombStack.remove(this);
	playerOwner->availableBombs += 1;
	Stage1::scene->Delete(this, MOVING);
}


void Bomb::OnCollision(Object* obj)
{	
	switch (obj->Type())
	{
	case EXPLOSION:
		Explode();
		break;
	case BOMB:
		Rect* bmbBox = (Rect*)obj->BBox();
		Rect* thisBox = (Rect*)BBox();
		float diffUp = bmbBox->Top() - thisBox->Bottom();
		float diffDn = thisBox->Top() - bmbBox->Bottom();
		float diffLt = bmbBox->Left() - thisBox->Right();
		float diffRt = thisBox->Left() - bmbBox->Right();

		// colis�o pela esquerda
		if (diffLt <= 0 && diffLt >= -3)
			obj->MoveTo(x + 16, y);
		
		// colis�o por cima
		if (diffUp <= 0 && diffUp >= -3)
			obj->MoveTo(x, y + 16);
		
		// colis�o pela direita
		if (diffRt <= 0 && diffRt >= -3)
			obj->MoveTo(x - 16, y);
		
		// colis�o por baixo
		if (diffDn <= 0 && diffDn >= -3)
			obj->MoveTo(x, y - 16);

		Bomb* bomb = dynamic_cast<Bomb*>(obj);
		bomb->bombKicked = false;
		break;
	}
}


void Bomb::MoveBomb()
{
	switch (dirKicked)
	{
	case UP:
		if (Stage1::bGrid->CheckGridPosition(x, y-9, MPT))
			Translate(0, -speed * gameTime);
		else bombKicked = false;
		break;
	case DOWN:
		if (Stage1::bGrid->CheckGridPosition(x, y+8, MPT))
			Translate(0, speed * gameTime);
		else bombKicked = false;
		break;
	case LEFT:
		if (Stage1::bGrid->CheckGridPosition(x-9, y, MPT))
			Translate(-speed * gameTime, 0);
		else bombKicked = false;
		break;
	case RIGHT:
		if (Stage1::bGrid->CheckGridPosition(x+8, y, MPT))
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

		if ((Stage1::bGrid->CheckGridPosition(xpsX, xpsY, MPT)) ||
			((bombMode == R_BOMB) && !(Stage1::bGrid->CheckGridPosition(xpsX, xpsY, WLL))))
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

		if ((Stage1::bGrid->CheckGridPosition(xpsX, xpsY, MPT)) ||
			((bombMode == R_BOMB) && !(Stage1::bGrid->CheckGridPosition(xpsX, xpsY, WLL))))
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

		if ((Stage1::bGrid->CheckGridPosition(xpsX, xpsY, MPT)) ||
			((bombMode == R_BOMB) && !(Stage1::bGrid->CheckGridPosition(xpsX, xpsY, WLL))))
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

		if ((Stage1::bGrid->CheckGridPosition(xpsX, xpsY, MPT)) ||
			((bombMode == R_BOMB) && !(Stage1::bGrid->CheckGridPosition(xpsX, xpsY, WLL))))
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