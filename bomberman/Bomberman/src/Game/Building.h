#pragma once

#ifndef _BUILDING_H_
#define _BUILDING_H_

#include "../Engine/Object.h"
#include "../Engine/Types.h"
#include "../Engine/Sprite.h"

class Building : public Object
{
private:
	Sprite* building;
	Sprite* shadow;
public:
	Building(float x, float y);
	~Building();

	void Draw();
	void Update();
};

inline void Building::Draw()
{
	building->Draw(x, y, Layer::MIDDLE);
	if (shadow != nullptr)
	{
		shadow->Draw(x, y + 16, Layer::LOWER);
	}
}

inline void Building::Update()
{
	if (y >= 16 * 13)
	{
		shadow = nullptr;
	}
}
#endif // !_BUILDING_H_