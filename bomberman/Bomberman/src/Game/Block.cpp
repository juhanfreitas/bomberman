#include "Block.h"
#include "Bomberman.h"
#include "Stage1.h"

Block::Block(float x, float y)
{
	type = BLOCK;
	blockTiles = new TileSet("Resources/stage/block1.png", 16, 16, 7, 14);
	shadow = new Sprite("Resources/stage/block1_shadow.png");
	anim = new Animation(blockTiles, .150f, true);
	blkState = DEFAULT;

	uint stillseq[4] = { 0, 1, 2, 3 };
	uint explodeseq[7] = { 7, 8, 9, 10, 11, 12, 13 };

	anim->Add(DEFAULT, stillseq, 4);
	anim->Add(EXPLODING, explodeseq, 7);

	BBox(new Rect(-8, -8, 8, 8));
	MoveTo(x + 8, y + 8, Layer::MIDDLE);
}

Block::~Block()
{
	delete shadow;
	delete anim;
	delete blockTiles;
}

void Block::Update()
{
	if (blkState == DEFAULT)
		anim->ChangeLoop(true);


	if (blkState == EXPLODING)
	{
		anim->ChangeDelay(.120f);
		anim->ChangeLoop(false);
	}


	if (y >= 16 * 13)
	{
		shadow = nullptr;
	}

	if (anim->Inactive())
	{
		Bomberman::player->IncreaseScore(10);
		Stage1::backg->ClearGridPosition(x, y);
		Stage1::scene->Delete(this, STATIC);
	}

	anim->Select(blkState);
	anim->NextFrame();
}