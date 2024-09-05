#include "Explosion.h"
#include "Bomberman.h"
#include "Stage1.h"
#include <iostream>

Explosion::Explosion(float posX, float posY, ExplosionPart part)
{
	frames = new TileSet("Resources/bombs.png", 16, 16, 12, 120);
	anim = new Animation(frames, 0.100f, false);

	type = EXPLOSION;

	uint baseSeq[5] = { 24, 25, 26, 27, 28 };
	uint bodyVSeq[5] = { 32 ,33, 34, 35, 36 };
	uint bodyHSeq[5] = { 48, 49, 50, 51, 52 };
	uint tipUpSeq[5] = { 60, 61, 62, 63, 64 };
	uint tipDnSeq[5] = { 72, 73, 74, 75, 76 };
	uint tipRtSeq[5] = { 84, 85, 86, 87, 88 };
	uint tipLtSeq[5] = { 96, 97, 98, 99, 100};

	anim->Add(BASE,		baseSeq, 5);
	anim->Add(BODY_V,	bodyVSeq, 5);
	anim->Add(BODY_H,	bodyHSeq, 5);
	anim->Add(TIP_UP,	tipUpSeq, 5);
	anim->Add(TIP_DN,	tipDnSeq, 5);
	anim->Add(TIP_LT,	tipLtSeq, 5);
	anim->Add(TIP_RT,	tipRtSeq, 5);
	anim->Select(part);

	BBox(new Rect(-8, -8, 8, 8));
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
	case BLOCK:
		Block* blk = dynamic_cast<Block*>(obj);
		blk->ChangeState(EXPLODING);
		break;
	}
}