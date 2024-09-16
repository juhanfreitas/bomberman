#pragma once

#ifndef _BUILDING_H_
#define _BUILDING_H_

#include "../Engine/Object.h"
#include "../Engine/Types.h"
#include "../Engine/Sprite.h"
#include "Enums.h"

class Building : public Object
{
private:
	Sprite* building;
	Sprite* shadow;
	bool hasShadow = true;

public:
	Building(float x, float y);
	~Building();

	void Draw();
	void Update();
};

inline void Building::Draw()
{
	building->Draw(x, y, Layer::MIDDLE);
	if (hasShadow)
		shadow->Draw(x, y + 16, Layer::LOWER);
}

#endif // !_BUILDING_H_