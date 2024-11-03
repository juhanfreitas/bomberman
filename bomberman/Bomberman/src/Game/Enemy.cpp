/**********************************************************************************
// Enemy (C�digo Fonte)
//
// Cria��o:     17 Set 2024
// Atualiza��o: 19 Set 2024
// Compilador:  Visual C++ 2022
//
// Descri��o:   Super classe de inimigos
//
**********************************************************************************/

#include "Enemy.h"
#include "Bomberman.h"

TileSet* Enemy::enemiesTileset = nullptr;

Enemy::Enemy() :
	hits(1),
	speedLevel(1),
    score(0)
{
    Enemy::enemiesTileset = new TileSet("Resources/Sprites/general/enemies.png", 16, 32, 16, 80);

    enemyAnimation = new Animation(Enemy::enemiesTileset, 0.12f, true);
    BBox(new Rect(-7, -7, 7, 7));

	type = ENEMY;
    enemyTimer.Start();

    speed = Vector(270.0f, speedThreshold[speedLevel]);
}

Enemy::~Enemy() {}

void Enemy::Draw() {
    float posX = x;
    float posY = y;
    Color color = { 1, 1, 1, 1 };

    // volta o inimigo para o grid caso ele ainda esteja tentando encontrar uma dire��o para ir
    if (!enemyTimer.Elapsed(lastCollision, 0.15f)) {
        posX = lastX;
        posY = lastY;
    }

    // aplica uma transpar�ncia aleat�ria no inimigo caso este esteja no timer de transpar�ncia
    if (!enemyTimer.Elapsed(lastDamage, 1.5f)) {
        RandF alphaDist{ .5f, 0.8f };
        RandI BWDist{ 0, 1 };
        float isWhite = BWDist.Rand();
        color = { isWhite, isWhite, isWhite, alphaDist.Rand() };
    }

    enemyAnimation->Draw(posX, posY, z, scale, rotation, color);
}

void Enemy::OnCollision(Object* obj)
{
    if (state == DYING)
        return;

    switch (obj->Type())
    {
    case BLOCK:
    case BUILDING:
    case BOMB:
    case ENEMY: {
        MoveTo(lastX + Bomberman::xdiff, lastY);
        state = ChangeDirection();

        lastCollision = enemyTimer.Stamp();

        break;
    }
    case EXPLOSION:
        OnHit();
        break;
    case PLAYER:
        Player* player = (Player*)obj;
        player->Die();
        break;
    }
}

void Enemy::Wander() {
    lastX = x;
    lastY = y;
    float screenDelta = Bomberman::xdiff;
    screenDelta * speed.XComponent() >= 0 ? screenDelta *= -1.0f : screenDelta;
    Translate((speed.XComponent() * gameTime) + Bomberman::xdiff, -speed.YComponent() * gameTime);
}

void Enemy::Speed(uint speedLevel)
{
    speed.ScaleTo(speedThreshold[speedLevel] / 2.0f);
}

float Enemy::Speed()
{
    return speedLevel;
}

Enemy::State Enemy::ChangeDirection() {
    // define uma dire��o aleat�ria para vagar
    State direction;

    RandI dist{ UP, RIGHT };
    direction = State(dist.Rand());

    while (direction == state)
    {
        direction = State(dist.Rand());
    }

    // normaliza a dire��o para obter o �ngulo
    float angle = (direction % 4) * 90.0f;
    speed.RotateTo(angle);

    return direction;
}

void Enemy::OnHit()
{
    if (enemyTimer.Elapsed(lastDamage, 1.5f)) {
        hits -= 1;
        if (hits <= 0) {
            Die();
        }
        else {
            lastDamage = enemyTimer.Stamp();
        }
    }
}

void Enemy::Die()
{
    if (state != DYING) {
        state = DYING;
        Bomberman::audioManager->Play(SE_ENEMYDEATH);
        Bomberman::audioManager->Volume(SE_ENEMYDEATH, Bomberman::SEVolume);
        Bomberman::player1->IncreaseScore(score);
        enemyAnimation->ChangeLoop(false);
        enemyAnimation->Delay(0.24f);
    }
}

// -------------------------------------------------------------------------------

void Enemy::MoveTo(float px, float py)
{
    MoveTo(px, py, z);

    if (BBox())
        BBox()->MoveTo(px, py + 8);
}