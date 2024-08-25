// ---------------------------------------------------------

#ifndef _BOMBERMAN_BOMB_H_
#define _BOMBERMAN_BOMB_H_

// ---------------------------------------------------------

#include "../Engine/Object.h"
#include "../Engine/Sprite.h"
#include "../Engine/TileSet.h"
#include "../Engine/Animation.h"
#include "Player.h"

// ---------------------------------------------------------

enum BombType {NORMAL, SPIKE};

class Bomb : public Object
{
private:
	TileSet * bombs = nullptr;
	Animation * anim = nullptr;
	//Player *player = nullptr;

public:

	BombType type;
	float playerX = 10.0f;
	float playerY = 10.0f;

	Bomb(BombType Bombtype);
	~Bomb();

	void ChangeType(BombType bombType);
	void Update();
	void Draw();
};


inline void Bomb::Draw() 
{anim->Draw(playerX, playerY, Layer::FRONT); }

#endif