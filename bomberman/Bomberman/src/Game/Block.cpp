
#include "Block.h"

Block::Block(float x, float y)
{
	float posX;
	float posY;
	blkState = STILL;
	blockTiles = new TileSet("Resources/block_stg 1.png", 1, 1, 1, 1);
	anim = new Animation(blockTiles, 120.0f, false, 2.0f);
	
	uint stillseq[1] = {0};
	uint explodeseq[4] = {};
	
	anim->Add(STILL, stillseq, 1);
	anim->Add(EXPLODE, explodeseq, 4);

	BBox(new Rect());
	MoveTo(x, y);
}

Block::~Block()
{
	delete anim;
	delete blockTiles;
}

void Block::Update()
{
	if (blkState == STILL)
		anim->Select(STILL);


	if (blkState == EXPLODE)
	{
		anim->Select(EXPLODE);
		anim->ChangeLoop(true);
	}

	anim->NextFrame();
}