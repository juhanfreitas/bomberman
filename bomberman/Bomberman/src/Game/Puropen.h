/**********************************************************************************
// Puropen (Arquivo de Cabeçalho)
//
// Criação:     26 Set 2024
// Atualização: 26 Set 2024
// Compilador:  Visual C++ 2022
//
// Descrição:   Inimigo Puropen
//
**********************************************************************************/
#pragma once
#ifndef _PUROPEN_H_
#define _PUROPEN_H_

// -------------------------------------------------------------------------------
// Inclusões

#include "Enemy.h"

// -------------------------------------------------------------------------------

class Puropen : public Enemy
{
public:
    Puropen(float initialX, float initialY, Scene* scene, bool invulnerableSpawn = false);
    ~Puropen();

    using Enemy::Draw;
    void Update();
    using Enemy::OnCollision;
};

// -------------------------------------------------------------------------------

#endif