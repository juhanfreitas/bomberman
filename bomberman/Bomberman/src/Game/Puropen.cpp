/**********************************************************************************
// Puropen (Código Fonte)
//
// Criação:     26 Set 2024
// Atualização: 26 Set 2024
// Compilador:  Visual C++ 2022
//
// Descrição:   
//
**********************************************************************************/

#include "../Engine/Random.h"

#include "Puropen.h"
#include "Bomberman.h"
#include "Stage1.h"

// ---------------------------------------------------------------------------------

Puropen::Puropen(float initialX, float initialY, Scene* scene, bool invulnerableSpawn)
{
    hits = 1;
    score = 100;
    speedLevel = 2;

    this->scene = scene;
    
    if (invulnerableSpawn)
        lastDamage = enemyTimer.Stamp();

    uint Up     [3] = { 25, 26, 27 };
    uint Down   [3] = { 16, 17, 18 };
    uint Left   [3] = { 22, 23, 24 };
    uint Right  [3] = { 19, 20, 21 };

    enemyAnimation->Add(DYING,  Dying, 8);
    enemyAnimation->Add(UP,     Up, 3);
    enemyAnimation->Add(DOWN, Down, 3);
    enemyAnimation->Add(LEFT, Left, 3);
    enemyAnimation->Add(RIGHT, Right, 3);

    enemyAnimation->Select(state);

    Speed(speedLevel);

    MoveTo(initialX, initialY);
}

Puropen::~Puropen() {
    delete enemyAnimation;
}

void Puropen::Update() {

    if (state != DYING)
        Wander();

    if (enemyAnimation->Inactive())
        scene->Delete(this, MOVING);
    
    enemyAnimation->NextFrame();
    if (enemyTimer.Elapsed(lastCollision, 0.15f))
        enemyAnimation->Select(state);
}