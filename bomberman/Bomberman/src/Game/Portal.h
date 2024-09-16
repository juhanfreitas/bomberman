#pragma once

#ifndef _PORTAL_H
#define _PORTAL_H

// ---------------------------------------------------

#include "../Engine/Object.h"
#include "../Engine/TileSet.h"
#include "../Engine/Animation.h"

class Portal : public Object
{
private:
	TileSet* frames;
	Animation* anim;

public:
	bool canPass = false;

	Portal(float x, float y);
	~Portal();

	void Update();
	void Draw();
};


inline void Portal::Update()
{
	anim->Select(0);
	anim->NextFrame();
}

inline void Portal::Draw() 
{
	anim->Draw(x, y, Layer::LOWER);
}
#endif // !_PORTAL_H