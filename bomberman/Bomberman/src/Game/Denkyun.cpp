/**********************************************************************************
// Denkyun (Código Fonte)
//
// Criação:     30 Set 2024
// Atualização: 30 Set 2024
// Compilador:  Visual C++ 2022
//
// Descrição:
//
**********************************************************************************/

#include "../Engine/Random.h"

#include "Denkyun.h"
#include "Bomberman.h"
#include "Stage1.h"

// ---------------------------------------------------------------------------------

Denkyun::Denkyun(float initialX, float initialY, Scene* scene, bool invulnerableSpawn)
{
    hits = 2;
    score = 400;
    speedLevel = 2;

    if (invulnerableSpawn)
        lastDamage = enemyTimer.Stamp();

    this->scene = scene;

    // inimigo olha apenas para baixo
    uint Walking[10] = { 48, 49, 50, 51, 52, 53, 52, 51, 50, 49 };

    enemyAnimation->Add(DYING, Dying, 8);
    enemyAnimation->Add(DOWN, Walking, 10);      // animação olhando para baixo

    enemyAnimation->Select(state);

    Speed(speedLevel);

    MoveTo(initialX, initialY);
}

Denkyun::~Denkyun() {
    delete enemyAnimation;
}

void Denkyun::Update() {

    if (state != DYING)
        Wander();

    if (enemyAnimation->Inactive())
        scene->Delete(this, MOVING);

    enemyAnimation->NextFrame();
    if (state != DYING)
        enemyAnimation->Select(DOWN);
    else
        enemyAnimation->Select(state);
}