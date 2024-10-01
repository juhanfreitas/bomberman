#pragma once

#ifndef _PORTAL_H
#define _PORTAL_H

// ---------------------------------------------------

#include "../Engine/Sprite.h"
#include "../Engine/Object.h"
#include "../Engine/Scene.h"
#include "../Engine/Timer.h"

#include <vector>

class Portal : public Object
{
private:
	Sprite* sprite = nullptr;
	Scene* scene = nullptr;

	std::vector<uint> enemyPool;

	float creationCooldown = 2.0f;
	Timer enemyCreationTimer;

	bool active = false;
	bool canTransition = false;

public:

	Portal(float x, float y, Scene* scene, const std::vector<uint> * enemypool);
	~Portal();

	void Update();
	void HandleCollision(Object * obj);
	void Draw();

	void Activate(bool activationFlag);
	bool Transition();
	void Transition(bool transition);

	void CreateEnemy();
};

inline void Portal::Draw() 
{
	sprite->Draw(x, y, Layer::LOWER);
}
inline void Portal::Activate(bool activationFlag)
{
	active = activationFlag;
}
inline bool Portal::Transition()
{
	return canTransition;
}

inline void Portal::Transition(bool transition)
{
	if (active)
		canTransition = transition;
}

#endif // !_PORTAL_H