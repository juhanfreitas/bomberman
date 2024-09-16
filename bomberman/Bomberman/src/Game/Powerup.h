#pragma once

#ifndef _POWERUP_H_
#define _POWERUP_H_

#include "../Engine/Object.h"
#include "../Engine/TileSet.h"
#include "../Engine/Animation.h"
#include "../Game/Stage1.h"


class Powerup : public Object
{
private:
	TileSet* powerUps;
	TileSet* explosion;
	Animation* anim;
	Timer visibleTime;
	uint PWRXPLD = 0;
	
public:
	bool destroy_collect;
	bool exploded;
	PowerUpType powerType;

	Powerup(float x, float y, PowerUpType pType);
	~Powerup();

	void Update();
	void Draw();
	void ExplosionState();
	void PowerUpActions(Player* player);
};


inline void Powerup::Draw()
{
	anim->Draw(x, y, Layer::LOWER);
}


#endif _POWERUP_H_