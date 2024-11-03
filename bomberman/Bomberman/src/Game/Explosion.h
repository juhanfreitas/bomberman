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
#include "Bomb.h"
#include "Enums.h"

// ---------------------------------------------------------


class Explosion : public Object
{
private:
	TileSet* frames = nullptr;
	Animation* anim = nullptr;

public:
	//Bomb* bombOrigin;

	Explosion(float bombX, float bombY, ExplosionPart part);
	~Explosion();

	void Update();
	void Draw();
	void OnCollision(Object * obj);
	Mixed * createCollision(ExplosionPart);
};

inline void Explosion::Draw()
{ anim->Draw(x, y, Layer::UPPER); }

#endif _EXPLOSION_H_