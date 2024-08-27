
#include "Block.h"
#include "Bomberman.h"

Block::Block(float x, float y)
{
	type = BLOCK;
	blkState = DEFAULT;
	blockTiles = new TileSet("Resources/block_stg 1.png", 16, 16, 2, 2);
	anim = new Animation(blockTiles, 120.0f, false);
	
	uint stillseq[1] = {3};
	uint explodeseq[4] = {1};
	
	anim->Add(DEFAULT, stillseq, 1);
	anim->Add(EXPLODE, explodeseq, 4);

	BBox(new Rect(-8, -8, 8, 8));
	MoveTo(x+8, y+8); 
}

Block::~Block()
{
	delete anim;
	delete blockTiles;
}

void Block::Update()
{
	if (blkState == DEFAULT)
		anim->Select(DEFAULT);


	if (blkState == EXPLODE)
	{
		anim->Select(EXPLODE);
		anim->ChangeLoop(true);
	}

	anim->NextFrame();
}