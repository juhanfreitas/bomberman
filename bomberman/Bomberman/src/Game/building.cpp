#include "Building.h"
//#include "Bomberman.h"

Building::Building(float x, float y)
{
	type = 2;
	building = new Sprite("Resources/stage/building1.png");
	shadow = new Sprite("Resources/stage/building1_shadow.png");
	BBox(new Rect(-8, -8, 8, 8));
	MoveTo(x + 8, y + 8);
}

Building::~Building()
{
	delete building;
	delete shadow;
}