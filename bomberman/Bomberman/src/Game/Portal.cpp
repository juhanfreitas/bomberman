#include "Portal.h"
#include "Bomberman.h"

Portal::Portal(float x, float y)
{
	type = PORTAL;
	sprite = new Sprite("Resources/portal.png");
	BBox(new Rect(-8,-8,8,8));
	MoveTo(x+8, y+8, Layer::LOWER);
}

Portal::~Portal()
{
	delete sprite;
}

void Portal::Update()
{

}