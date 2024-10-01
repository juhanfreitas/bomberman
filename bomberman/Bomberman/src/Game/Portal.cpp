#include "Portal.h"
#include "Bomberman.h"
#include "Enemy.h"

Portal::Portal(float x, float y, Scene* scene, const std::vector<uint> * enemypool) : enemyPool(*enemypool)
{
	this->scene = scene;
	
	enemyCreationTimer.Start();

	type = PORTAL;
	sprite = new Sprite("Resources/Sprites/general/portal.png");
	BBox(new Rect(-4,-4,4,4));
	MoveTo(x+8, y+8, Layer::LOWER);
}

Portal::~Portal()
{
	delete sprite;
}

void Portal::Update()
{

}

void Portal::HandleCollision(Object* obj)
{
	switch (obj->Type())
	{
	case PLAYER:
		Transition(true);
		// se for passar de fase, centraliza o player no portal
		if (Transition())
			obj->MoveTo(x, y - 8);
		break;

	case EXPLOSION:
		if (!active)
			CreateEnemy();
		break;
	}
}

void Portal::CreateEnemy()
{
	if (!enemyCreationTimer.Elapsed(creationCooldown))
		return;

	enemyCreationTimer.Reset();
	int distLimit = enemyPool.size() - 1;
	RandI enemyDist{ 0, distLimit };
	uint enemyType = enemyPool[enemyDist.Rand()];

	Bomberman::enemyFactory->CreateEnemy(enemyType, x, y - 8, scene, true);
}