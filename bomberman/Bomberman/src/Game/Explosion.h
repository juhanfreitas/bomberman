// ---------------------------------------------------------
#pragma once
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

// ---------------------------------------------------------

#include "../Engine/Object.h"
#include "../Engine/Sprite.h"
#include "../Engine/TileSet.h"
#include "../Engine/Animation.h"
#include "../Engine/Timer.h"

// ---------------------------------------------------------

class Explosion : public Object
{
private:
	TileSet* frames = nullptr;
	Animation* anim = nullptr;

public:

	Timer timer;

	Explosion(float bombX, float bombY);
	~Explosion();

	void Update();
	void Draw();
};

inline void Explosion::Draw()
{ anim->Draw(x, y, z); }

inline void Explosion::Update()
{ anim->NextFrame(); }

#endif _EXPLOSION_H_