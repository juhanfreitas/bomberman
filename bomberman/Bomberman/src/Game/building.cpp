#include "Building.h"
//#include "Bomberman.h"

Building::Building(float x, float y)
{
	type = 2;
	BBox(new Rect(-1.0f * X()/2.0f, -1.0f * Y()/2.0f, X()+16, Y()+16));
	MoveTo(x, y);
}

Building::~Building()
{
}

void Building::Draw()
{
}

void Building::Update()
{
}