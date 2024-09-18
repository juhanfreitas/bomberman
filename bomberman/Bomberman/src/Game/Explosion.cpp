#include "Explosion.h"
#include "Bomberman.h"
#include "Stage1.h"
#include "Powerup.h"
#include <iostream>

Explosion::Explosion(float posX, float posY, ExplosionPart part)
{
	type = ObjTypes::EXPLOSION;

	frames = Bomberman::tiles->GetTilesOf(TilesType::TS_EXPLOSION);
	anim = new Animation(frames, 0.090f, false);

	uint baseSeq[5] = { 0, 1, 2, 3, 4 };
	uint bodyVSeq[5] = { 5, 6, 7, 8, 9 };
	uint bodyHSeq[5] = { 10, 11, 12, 13, 14 };
	uint tipUpSeq[5] = { 15, 16, 17, 18, 19 };
	uint tipDnSeq[5] = { 20, 21, 22, 23, 24 };
	uint tipRtSeq[5] = { 25, 26, 27, 28, 29 };
	uint tipLtSeq[5] = { 30, 31, 32, 33, 34 };

	anim->Add(BASE,		baseSeq,	5);
	anim->Add(BODY_V,	bodyVSeq,	5);
	anim->Add(BODY_H,	bodyHSeq,	5);
	anim->Add(TIP_UP,	tipUpSeq,	5);
	anim->Add(TIP_DN,	tipDnSeq,	5);
	anim->Add(TIP_LT,	tipLtSeq,	5);
	anim->Add(TIP_RT,	tipRtSeq,	5);
	anim->Select(part);

	Mixed* collisionBox = createCollision(part);

	BBox(collisionBox);
	MoveTo(posX, posY);
}

Explosion::~Explosion()
{
	delete anim;
}

void Explosion::Update()
{
	anim->NextFrame();
	if (anim->Inactive())
		Stage1::scene->Delete();
}

void Explosion::OnCollision(Object * obj) {
	switch (obj->Type()) {
	case PORTAL:
		break;
	case POWERUPS:
		Powerup* pwr;
		pwr = dynamic_cast<Powerup*>(obj);
		pwr->ExplosionState();
		break;
	case BLOCK:
		Block* blk;
		blk = static_cast<Block*>(obj);
		blk->ChangeState(BlockState::EXPLODING);
		break;
	}
}

Mixed* Explosion::createCollision(ExplosionPart part)
{
	Mixed * mixed = new Mixed();

	switch (part)
	{
	case BASE:
		mixed->Insert(new Rect(-8, -6, 8, 6));
		mixed->Insert(new Rect(-6, -8, 6, 8));
		break;
	case BODY_V:
		mixed->Insert(new Rect(-6, -8, 6, 8));
		break;
	case BODY_H:
		mixed->Insert(new Rect(-8, -6, 8, 6));
		break;
	case TIP_UP:
		mixed->Insert(new Rect(-6, -6, 6, 8));
		break;
	case TIP_DN:
		mixed->Insert(new Rect(-6, -8, 6, 6));
		break;
	case TIP_LT:
		mixed->Insert(new Rect(-6, -6, 8, 6));
		break;
	case TIP_RT:
		mixed->Insert(new Rect(-8, -6, 6, 6));
		break;
	}

	return mixed;
}
