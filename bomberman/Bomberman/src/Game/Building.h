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
	Image* buildingImage = nullptr;
	Image* shadowImage = nullptr;
	Sprite* building = nullptr;
	Sprite* shadow = nullptr;
	bool hasShadow = true;

public:
	Building(float x, float y, Image* buildingImage = nullptr, Image* shadowImage = nullptr);
	~Building();

	void Draw();
	void Update();
};

inline void Building::Draw()
{
	if (building != nullptr)
		building->Draw(x, y, Layer::MIDDLE);

	if (hasShadow && shadow != nullptr)
		shadow->Draw(x, y + 16, Layer::LOWER);
}

#endif // !_BUILDING_H_