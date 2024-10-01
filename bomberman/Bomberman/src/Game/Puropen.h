/**********************************************************************************
// Puropen (Arquivo de Cabe�alho)
//
// Cria��o:     26 Set 2024
// Atualiza��o: 26 Set 2024
// Compilador:  Visual C++ 2022
//
// Descri��o:   Inimigo Puropen
//
**********************************************************************************/
#pragma once
#ifndef _PUROPEN_H_
#define _PUROPEN_H_

// -------------------------------------------------------------------------------
// Inclus�es

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