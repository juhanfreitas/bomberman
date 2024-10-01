#include "Portal.h"
#include "Bomberman.h"
#include "Stage1.h"
#include "Enums.h"
#include "Enemy.h"

Portal::Portal(float x, float y, Scene* scene, const std::vector<uint> * enemypool) : enemyPool(*enemypool)
{
	this->scene = scene;
	
	enemyCreationTimer.Start();

	type = PORTAL;
	frames = new TileSet("Resources/Sprites/general/portal.png", 16, 16, 4, 4);
	anim = new Animation(frames, .180f, true);

	MoveTo(x+8, y+8, Layer::LOWER);
}

Portal::~Portal()
{
	delete anim;
	delete frames;
}

void Portal::Update()
{
	if (Stage1::backg->CheckGridPosition(x, y, MPT))
	{
		BBox(new Rect(-3,-3,3,3));
		Stage1::backg->OccupyGridPosition(x, y, PTL);
		visible = true;
	}
	
	anim->NextFrame();
}

void Portal::HandleCollision(Object* obj)
{
	switch (obj->Type())
	{
	case PLAYER:
		// se for passar de fase, centraliza o player no portal
		if (active && !Transition()) {
			Transition(true);
			obj->MoveTo(x, y - 8);
		}
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