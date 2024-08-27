#pragma once

#ifndef _BUILDING_H_
#define _BUILDING_H_

#include "../Engine/Object.h"
#include "../Engine/Types.h"

class Building : public Object
{
public:
	Building(float x, float y);
	~Building();

	void Draw();
	void Update();
};


#endif // !_BUILDING_H_