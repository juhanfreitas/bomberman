#include "Building.h"
#include "Stage1.h"


Building::Building(float x, float y)
{
	type = BUILDING;
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

void Building::Update() 
{
	// verificação para o desenho da sombra
	FillType fill = Stage1::backg->CheckGridPosition(x, y+16);
	if (fill == BLK || fill == MPT)
		hasShadow = true;
	else hasShadow = false;
}