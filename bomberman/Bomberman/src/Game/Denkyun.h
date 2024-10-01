/**********************************************************************************
// Denkyun (Arquivo de Cabeçalho)
//
// Criação:     26 Set 2024
// Atualização: 26 Set 2024
// Compilador:  Visual C++ 2022
//
// Descrição:   Inimigo Denkyun
//
**********************************************************************************/
#pragma once
#ifndef _DENKYUN_H_
#define _DENKYUN_H_

// -------------------------------------------------------------------------------
// Inclusões

#include "Enemy.h"

// -------------------------------------------------------------------------------

class Denkyun : public Enemy
{
public:
    Denkyun(float initialX, float initialY, Scene* scene, bool invulnerableSpawn = false);
    ~Denkyun();

    using Enemy::Draw;
    void Update();
    using Enemy::OnCollision;
};

// -------------------------------------------------------------------------------

#endif