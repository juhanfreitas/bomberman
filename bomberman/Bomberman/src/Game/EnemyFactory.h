/**********************************************************************************
// EnemyFactory (Arquivo de Cabe�alho)
//
// Cria��o:     17 Set 2024
// Atualiza��o: 19 Set 2024
// Compilador:  Visual C++ 2022
//
// Descri��o:   Criador de inimigos
//
**********************************************************************************/

#pragma once
#ifndef _ENEMYFACTORY_H_
#define _ENEMYFACTORY_H_

// -------------------------------------------------------------------------------
// Inclus�es

#include "../Engine/Types.h"
#include "../Engine/Scene.h"

#include "Enemy.h"
#include "Puropen.h"
#include "Denkyun.h"

// -------------------------------------------------------------------------------

enum EnemyTypes { PUROPEN, DENKYUN };

class EnemyFactory
{
public:
    EnemyFactory();
    ~EnemyFactory();

    template<class T>
    void CreateEnemy(float x, float y, Scene* scene, bool invulnerable = false);

    void CreateEnemy(uint enemyType, float x, float y, Scene* scene, bool invulnerable = false);
};

// -------------------------------------------------------------------------------

#endif