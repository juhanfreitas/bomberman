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

	Explosion(float bombX, float bombY, uint power=1);
	~Explosion();

	void Update();
	void Draw();
	void OnCollision(Object * obj);
};

inline void Explosion::Draw()
{ anim->Draw(x, y, z); }

#endif _EXPLOSION_H_