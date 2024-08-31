#pragma once

#ifndef _PORTAL_H
#define _PORTAL_H

// ---------------------------------------------------

#include "../Engine/Sprite.h"
#include "../Engine/Object.h"

class Portal : public Object
{
private:
	Sprite* sprite = nullptr;

public:
	bool canPass = false;

	Portal(float x, float y);
	~Portal();

	void Update();
	void Draw();
};

inline void Portal::Draw() 
{
	sprite->Draw(x, y, Layer::MIDDLE);
}
#endif // !_PORTAL_H