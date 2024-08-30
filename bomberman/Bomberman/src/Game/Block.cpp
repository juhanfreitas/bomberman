
#include "Block.h"
#include "Bomberman.h"

Block::Block(float x, float y)
{
	type = BLOCK;
	blkState = DEFAULT;
	blockTiles = new TileSet("Resources/block_stg 1.png", 16, 16, 6, 12);
	anim = new Animation(blockTiles, 120.0f, true);
	
	uint SeqStill[4] = { 0, 1, 2, 3 };
	uint SeqExploding[6] = { 6, 7, 8, 9, 10, 11 };
	
	anim->Add(DEFAULT, SeqStill, 4);
	anim->Add(EXPLODING, SeqExploding, 6);

	BBox(new Rect(-8, -8, 8, 8));
	MoveTo(x+8, y+8, Layer::LOWER); 
}

Block::~Block()
{
	delete anim;
	delete blockTiles;
}

void Block::Update()
{
	if (blkState == EXPLODING)
	{
		anim->ChangeLoop(false);
	}

	if (anim->Inactive())
		Stage1::scene->Delete(this, STATIC);

	anim->Select(blkState);
	anim->NextFrame();
}