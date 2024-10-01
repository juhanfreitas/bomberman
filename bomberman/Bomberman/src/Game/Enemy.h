/**********************************************************************************
// Enemy (Arquivo de Cabeçalho)
//
// Criação:     17 Set 2024
// Atualização: 19 Set 2024
// Compilador:  Visual C++ 2022
//
// Descrição:   Super classe de inimigos
//
**********************************************************************************/
#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_

// -------------------------------------------------------------------------------
// Inclusões

#include "../Engine/Object.h"
#include "../Engine/Animation.h"
#include "../Engine/Random.h"
#include "../Engine/Vector.h"
#include "../Engine/Scene.h"

// -------------------------------------------------------------------------------

class Enemy : public Object
{
protected:
    // ------------------------------------------------
    // useful constants
    // ------------------------------------------------
    float speedThreshold[10] = { 0.0f, 50.0f, 55.0f, 60.0f, 65.0f, 70.0f, 75.0f, 80.0f, 85.0f, 90.0f };
    
    uint Damaged[1] = { 0 };
    uint Dying[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };

    enum State {
        DYING,
        UP,         // SPEED ANGLE - 90 degrees
        LEFT,       // SPEED ANGLE - 180 degrees
        DOWN,       // SPEED ANGLE - 270 degrees
        RIGHT       // SPEED ANGLE - 0 degrees
    };

    // ------------------------------------------------
    // variables
    // ------------------------------------------------

    Scene * scene;
    static TileSet* enemiesTileset;

    int hits;
    int score;
    State state = DOWN;
    uint speedLevel;
    Vector speed;

    Timer enemyTimer;
    llong lastCollision;
    llong lastDamage;
    Animation* enemyAnimation;

public:
    Enemy();                   // construtor
    virtual ~Enemy();          // destrutor virtual

    virtual void Wander();

    virtual void Draw();
    virtual void Update() = 0;
    virtual void OnCollision(Object* obj);

    // move o inimigo para as coordenadas (x,y) indicadas
    virtual void MoveTo(float px, float py) override;
    using Object::MoveTo;
    
    virtual void Speed(uint speedLevel);
    virtual float Speed();

    virtual State ChangeDirection();
    virtual void Die();
    virtual void OnHit();
};


// -------------------------------------------------------------------------------

#endif