#include "Powerup.h"
#include "Bomberman.h"

Powerup::Powerup(float x, float y, PowerUpType pType)
{
	type = ObjTypes::POWERUPS;
    powerUps = Bomberman::tiles->GetTilesOf(TS_POWERUP);
	anim = new Animation(powerUps, .100f, true);

	powerType = pType;

	uint bombFrame[2] = { 0, 8 };
	uint fireFrame[2] = { 1, 9 };
	uint redBFrame[2] = { 2, 10};
	uint mxPWRFrame[2] = { 3, 11 };
	uint bmbPssFrame[2] = { 4, 12 };
	uint skullFrame[2] = { 5, 13 };
	uint invcbFrame[2] = { 6, 14 };
	uint tBmbFrame[2] = { 7, 15 };
	uint wpssFrame[2] = { 16, 24 };
	uint speedFrame[2] = { 17, 25 };
	uint kickFrame[2] = { 18, 26 };
	uint riceFrame[2] = { 19, 27 };
	uint gloveFrame[2] = { 20, 28 };
	uint oneUpFrame[2] = { 21, 29 };
	uint timeFrame[2] = { 22, 30 };
	uint livesFrame[2] = { 32, 40 };
	uint cakeFrame[2] = { 33, 41 };
	uint randFrame[2] = { 34, 42 };
	uint hammFrame[2] = { 35, 43 };
	uint appleFrame[2] = { 36, 44 };
	uint extingFrame[2] = { 37, 45 };
	uint popSFrame[2] = { 38, 46 };
	uint iceCFrame[2] = { 39, 47 };
    uint xpldFrame[7] = { 48, 49, 50, 51, 52, 53, 54 };

	anim->Add(BOMBS, bombFrame, 2);
	anim->Add(FIRE, fireFrame, 2);
	anim->Add(RED_BOMB, redBFrame, 2);
	anim->Add(MAX_PWR, mxPWRFrame, 2);
	anim->Add(BOMBPASS, bmbPssFrame, 2);
	anim->Add(SKULL, skullFrame, 2);
	anim->Add(INVINCIBLE, invcbFrame, 2);
	anim->Add(T_BOMB, tBmbFrame, 2);
	anim->Add(WALLPASS, wpssFrame, 2);
	anim->Add(SPD_UP, speedFrame, 2);
	anim->Add(KICK, kickFrame, 2);
	anim->Add(RICE, riceFrame, 2);
	anim->Add(GLOVE, gloveFrame, 2);
	anim->Add(ONE_UP, oneUpFrame, 2);
	anim->Add(TIME, timeFrame, 2);
	anim->Add(LIVES, livesFrame, 2);
	anim->Add(CAKE, cakeFrame, 2);
	anim->Add(RANDOM, randFrame, 2);
	anim->Add(HAMMER, hammFrame, 2);
	anim->Add(APPLE, appleFrame, 2);
	anim->Add(EXTINGUISH, extingFrame, 2);
	anim->Add(POPSICLE, popSFrame, 2);
	anim->Add(ICE_CREAM, iceCFrame, 2);
    anim->Add(powerXPD, xpldFrame, 7);

	anim->Select(pType);

	MoveTo(x+8, y+8);
}

Powerup::~Powerup()
{
	Stage1::backg->ClearGridPosition(x, y);
	delete anim;
}


void Powerup::Update()
{
    if (Stage1::backg->CheckGridPosition(x, y, MPT))
	{
	    BBox(new Rect( -8, -8, 8, 8));
		Stage1::backg->OccupyGridPosition(x, y, PWR);
        visible = true;
        visibleTime.Start();
	}

	if (exploded)
		anim->Select(powerXPD);
	
	anim->NextFrame();

	if (anim->Inactive())
		Stage1::scene->Delete();
}


void Powerup::ExplosionState()
{
    if (visibleTime.Elapsed(.500f))
    {
        anim->ChangeLoop(false);
	    exploded = true;
    }
}


void Powerup::PowerUpActions(Player* player)
{
    if (!exploded)
    {
        switch (powerType)
        {
        case BOMBS:
            player->maxBombs += 1;
            player->availableBombs += 1;
            break;
        case FIRE:
            if (player->bombPower != 9)
                player->bombPower++;
            break;
        case RED_BOMB:
            player->bombType = R_BOMB;
            break;
        case MAX_PWR:
            player->bombPower = 9;
            break;
        case BOMBPASS:
            player->bombPass = true;
            break;
        case SKULL:
            player->IncreaseScore(-150);
            break;
        case INVINCIBLE:
            break;
        case T_BOMB:
            player->bombType = TIMED;
            break;
        case WALLPASS:
            player->blockPass = true;
            break;
        case SPD_UP:
            player->speed += 10.f;
            break;
        case KICK:
            player->bombKick = true;
            break;
        case RICE:
            player->IncreaseScore(5000);
            break;
        case GLOVE:
            break;
        case ONE_UP:
            break;
        case TIME:
            Bomberman::timeLimit += 60;
            break;
        case LIVES:
            if (player->lives != 9)
                player->lives++;
            break;
        case CAKE:
            player->lives += 4;
            player->IncreaseScore(100000);
            break;
        case RANDOM:
            break;
        case HAMMER:
            player->IncreaseScore(100);
            break;
        case APPLE:
            player->IncreaseScore(8000);
            break;
        case EXTINGUISH:
            player->IncreaseScore(9000);
            player->lives = 9;
            break;
        case POPSICLE:
            player->IncreaseScore(500);
            break;
        case ICE_CREAM:
            player->lives += 4;
            player->IncreaseScore(50000);
            break;
        }
        Stage1::scene->Delete(this, STATIC);
    }
}
