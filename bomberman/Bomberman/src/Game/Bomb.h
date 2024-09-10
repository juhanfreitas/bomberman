// ---------------------------------------------------------
#pragma once
#ifndef _BOMB_H_
#define _BOMB_H_

// ---------------------------------------------------------

#include "../Engine/Object.h"
#include "../Engine/Sprite.h"
#include "../Engine/TileSet.h"
#include "../Engine/Animation.h"
#include "../Engine/Timer.h"
#include "Explosion.h"

// ---------------------------------------------------------

//enum BombType { NORMAL, R_BOMB, TIMED };
//enum BombState { FUSING, READY };
//enum Directions { UP, DOWN, LEFT, RIGHT };

class Player;

class Bomb : public Object
{
private:
	const float speed = 120.f;
	TileSet * bombs = nullptr;
	Animation * anim = nullptr;

	float fuseTime;
	bool playerIn = true;
	uint explosionPWR;
	Player* playerOwner;

public:
	Timer timer;
	BombType bombMode;
	BombState state;
	bool bombKicked;
	Directions dirKicked;

	Bomb(Player* owner, BombType bombType, float playerX, float playerY, uint power = 1);
	~Bomb();

	void Update();
	void Draw();
	void OnCollision(Object* obj);

	void CheckPlayerPosition();
	void CreateExplosionRange();
	void Explode();
	void MoveBomb();
};

inline void Bomb::Draw() 
{ anim->Draw(x, y, Layer::UPPER); }

#endif _BOMB_H_