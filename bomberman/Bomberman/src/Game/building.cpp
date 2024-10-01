#include "Building.h"
#include "Stage1.h"


Building::Building(float x, float y, Image* buildingImage, Image* shadowImage) :
	buildingImage(buildingImage),
	shadowImage(shadowImage)
{
	type = BUILDING;
	if (buildingImage != nullptr) {
		building = new Sprite(buildingImage);
		shadow = new Sprite(shadowImage);
	}

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