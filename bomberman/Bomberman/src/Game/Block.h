#pragma once
#ifndef _BLOCK_H_
#define _BLOCK_H_

// ----------------------------------------------------------
#include "../Engine/Object.h"
#include "../Engine/Sprite.h"
#include "../Engine/TileSet.h"
#include "../Engine/Animation.h"

// ----------------------------------------------------------

enum BlockState {DEFAULT, EXPLODE};

// ----------------------------------------------------------

class Block : public Object
{
private:

	TileSet * blockTiles;
	Animation * anim;
	BlockState blkState;

public:

	Block(float x, float y);
	~Block();

	void Update();
	void Draw();
	void ChangeState(BlockState state);
};

inline void Block::Draw()
{
	anim->Draw(x, y, z);
}

inline void Block::ChangeState(BlockState state)
{blkState = state;}

#endif _BLOCK_H_