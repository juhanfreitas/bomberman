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

enum BombType { NORMAL, SPIKE };
enum BombState { FUSING, READY };

class Bomb : public Object
{
private:
	TileSet * bombs = nullptr;
	Animation * anim = nullptr;

	float fuseTime;
	bool playerIn = true;
	uint explosionPWR;

	list<Explosion*> expUp;
	list<Explosion*> expDn;
	list<Explosion*> expLt;
	list<Explosion*> expRt;

public:
	Timer timer;
	BombType bombMode;
	BombState state;

	Bomb(BombType Bombtype, float playerX, float playerY, uint power = 1);
	~Bomb();

	void Update();
	void Draw();
	void OnCollision(Object* obj);

	void CheckPlayerPosition();
	void CreateExplosionRange();
	void Explode();
};

inline void Bomb::Draw() 
{ anim->Draw(x, y, Layer::UPPER); }

#endif _BOMB_H_