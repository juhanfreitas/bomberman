#include "Block.h"
#include "Bomberman.h"

Block::Block(float x, float y)
{
	type = BLOCK;
	blockTiles = new TileSet("Resources/stage/block1.png", 16, 16, 6, 10);
	shadow = new Sprite("Resources/stage/block1_shadow.png");
	anim = new Animation(blockTiles, 120.0f, true);
	blkState = DEFAULT;

	uint stillseq[4] = { 0, 1, 2, 3 };
	uint explodeseq[6] = { 6, 7, 8, 9, 10, 11 };

	anim->Add(DEFAULT, stillseq, 4);
	anim->Add(EXPLODING, explodeseq, 4);

	BBox(new Rect(-8, -8, 8, 8));
	MoveTo(x + 8, y + 8, Layer::MIDDLE);
}

Block::~Block()
{
	delete anim;
	delete blockTiles;
}

void Block::Update()
{
	if (blkState == DEFAULT)
		anim->ChangeLoop(true);


	if (blkState == EXPLODING)
		anim->ChangeLoop(false);


	if (y >= 16 * 13)
	{
		shadow = nullptr;
	}

	if (anim->Inactive())
	{
		delete shadow;
		Stage1::scene->Delete(this, STATIC);
	}

	anim->Select(blkState);
	anim->NextFrame();
}