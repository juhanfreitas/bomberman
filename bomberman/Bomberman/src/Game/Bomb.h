// ---------------------------------------------------------
#pragma once
#ifndef _BOMB_H_
#define _BOMB_H_

// ---------------------------------------------------------

#include "../Engine/Object.h"
#include "../Engine/Sprite.h"
#include "../Engine/TileSet.h"
#include "../Engine/Animation.h"

// ---------------------------------------------------------

enum BombType {NORMAL, SPIKE};

class Bomb : public Object
{
private:
	TileSet * bombs = nullptr;
	Animation * anim = nullptr;

public:

	BombType type;

	Bomb(BombType Bombtype, float x, float y);
	~Bomb();

	void Update();
	void Draw();
};

inline void Bomb::Update()
{
	anim->NextFrame();
}

inline void Bomb::Draw() 
{anim->Draw(x, y);}

#endif _BOMB_H_