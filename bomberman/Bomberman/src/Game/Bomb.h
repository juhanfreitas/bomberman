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
enum BombState { FUSING, READY };

class Bomb : public Object
{
private:
	TileSet * bombs = nullptr;
	Animation * anim = nullptr;

	float fuseTime;

	bool hasCollision = false;

public:
	Timer timer;
	BombType bombMode;
	BombState state;

	Bomb(BombType Bombtype, float playerX, float playerY);
	~Bomb();

	void Update();
	void Draw();
	void OnCollision(Object* obj);

	void CheckPlayerPosition();
	void Explode(uint power);
};

inline void Bomb::Draw() 
{ anim->Draw(x, y, z); }

#endif _BOMB_H_