#include "Portal.h"
#include "Stage1.h"
#include "Enums.h"

Portal::Portal(float x, float y)
{
	type = PORTAL;
	frames = new TileSet("Resources/portal.png", 16, 16, 4, 4);
	anim = new Animation(frames, .180f, true);

	uint portalseq[4] = { 0, 1, 2, 3 };
	anim->Add(0, portalseq, 4);
	
	anim->Select(0);

	MoveTo(x+8, y+8);
}

Portal::~Portal()
{
	delete anim;
	delete frames;
}

void Portal::Update()
{
	if (Stage1::backg->CheckGridPosition(x, y, MPT))
	{
		BBox(new Rect(-8,-8,8,8));
		Stage1::backg->OccupyGridPosition(x, y, PTL);
		visible = true;
	}

	anim->Select(0);
	anim->NextFrame();
}