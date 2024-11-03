#include "Block.h"
#include "Bomberman.h"
#include "Stage1.h"

Block::Block(float x, float y)
{
	type = ObjTypes::BLOCK;
	blockTiles = Bomberman::tiles->GetTilesOf(TS_BLOCK);
	shadow = new Sprite("Resources/stage/block1_shadow.png");
	anim = new Animation(blockTiles, .150f, true);
	blkState = BlockState::DEFAULT;

	uint stillseq[4] = { 0, 1, 2, 3 };
	uint explodeseq[7] = { 7, 8, 9, 10, 11, 12, 13 };

	anim->Add(DEFAULT, stillseq, 4);
	anim->Add(EXPLODING, explodeseq, 7);

	BBox(new Rect(-8, -8, 8, 8));
	MoveTo(x+8, y+8);

}

Block::~Block()
{
	delete shadow;
	delete anim;
}

void Block::Update()
{
	Translate(Bomberman::xdiff, 0);

	if (Stage1::bGrid->CheckGridPosition(x, y + 16, MPT))
		hasShadow = true;
	else hasShadow = false;

	if (blkState == BlockState::DEFAULT)
		anim->ChangeLoop(true);

	if (blkState == BlockState::EXPLODING)
	{
		hasShadow = false;
		anim->ChangeDelay(.120f);
		anim->ChangeLoop(false);
		DeleteBBox();
	}

	if (anim->Inactive())
	{
		Bomberman::player1->IncreaseScore(10);
		Stage1::bGrid->ClearGridPosition(x, y);
		Stage1::scene->Delete();
	}

	anim->Select(blkState);
	anim->NextFrame();
}