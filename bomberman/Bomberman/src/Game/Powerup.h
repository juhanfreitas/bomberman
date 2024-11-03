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
	Animation* anim;
	Timer visibleTime;
	uint powerXPD = 100;
	
public:
	bool visible = false;
	bool exploded = false;
	PowerUpType powerType;

	Powerup(float x, float y, PowerUpType pType);
	~Powerup();

	void Update();
	void Draw();
	void ExplosionState();
	void PowerUpActions(Player* player);
};


inline void Powerup::Draw()
{if (visible) anim->Draw(x, y, Layer::LOWER);}


#endif _POWERUP_H_