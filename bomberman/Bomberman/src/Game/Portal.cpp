#include "Portal.h"
#include "Enums.h"

Portal::Portal(float x, float y)
{
	type = PORTAL;
	frames = new TileSet("Resources/portal.png", 16, 16, 4, 4);
	anim = new Animation(frames, .180f, true);

	uint portalseq[4] = { 0, 1, 2, 3 };
	anim->Add(0, portalseq, 4);
	
	anim->Select(0);

	BBox(new Rect(-8,-8,8,8));
	MoveTo(x+8, y+8, Layer::LOWER);
}

Portal::~Portal()
{
	delete anim;
	delete frames;
}