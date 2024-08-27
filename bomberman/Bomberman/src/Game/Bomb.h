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

// ---------------------------------------------------------

enum BombType { NORMAL, SPIKE };

class Bomb : public Object
{
private:
	TileSet * bombs = nullptr;
	Animation * anim = nullptr;
	bool hasCollision = false;

public:

	Timer timer;
	BombType bombMode;

	Bomb(BombType Bombtype, float playerX, float playerY);
	~Bomb();

	void Update();
	void Draw();
	void CheckPlayerPosition();
};

inline void Bomb::Draw() 
{ anim->Draw(x, y, z); }

#endif _BOMB_H_