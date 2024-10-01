#include "Explosion.h"
#include "Bomberman.h"
#include "Stage1.h"
#include <iostream>

Explosion::Explosion(float posX, float posY, ExplosionPart part)
{
	frames = new TileSet("Resources/Sprites/general/bombs.png", 16, 16, 12, 120);
	anim = new Animation(frames, 0.100f, false);

	type = EXPLOSION;

	uint baseSeq[5]	 = { 24, 25, 26, 27, 28 };
	uint bodyVSeq[5] = { 36 ,37, 38, 39, 40 };
	uint bodyHSeq[5] = { 48, 49, 50, 51, 52 };
	uint tipUpSeq[5] = { 60, 61, 62, 63, 64 };
	uint tipDnSeq[5] = { 72, 73, 74, 75, 76 };
	uint tipRtSeq[5] = { 84, 85, 86, 87, 88 };
	uint tipLtSeq[5] = { 96, 97, 98, 99, 100};

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
	MoveTo(posX, posY, Layer::UPPER);
}

Explosion::~Explosion()
{
	delete anim;
	delete frames;
}

void Explosion::Update()
{
	anim->NextFrame();
	if (anim->Inactive())
		Stage1::scene->Delete(this, MOVING);
}

void Explosion::OnCollision(Object * obj) {
	switch (obj->Type()) {
	case BLOCK: {
		Block* blk = dynamic_cast<Block*>(obj);
		blk->ChangeState(EXPLODING);
		break;
	}
	case PORTAL: {
		Portal* portal = (Portal*)obj;
		portal->HandleCollision(this);
		break;
	}
	}
}

Mixed* Explosion::createCollision(ExplosionPart part)
{
	Mixed * mixed = new Mixed();

	switch (part)
	{
	case BASE:
		mixed->Insert(new Rect(-8, -7, 8, 7));
		mixed->Insert(new Rect(-7, -8, 7, 8));
		break;
	case BODY_V:
		mixed->Insert(new Rect(-7, -8, 7, 8));
		break;
	case BODY_H:
		mixed->Insert(new Rect(-8, -7, 8, 7));
		break;
	case TIP_UP:
		mixed->Insert(new Rect(-7, -7, 7, 8));
		break;
	case TIP_DN:
		mixed->Insert(new Rect(-7, -8, 7, 7));
		break;
	case TIP_LT:
		mixed->Insert(new Rect(-7, -7, 8, 7));
		break;
	case TIP_RT:
		mixed->Insert(new Rect(-8, -7, 7, 7));
		break;
	}

	return mixed;
}
