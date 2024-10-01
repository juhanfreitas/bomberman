/**********************************************************************************
// AnimaWalk (Arquivo de Cabe�alho)
//
// Cria��o:     18 Abr 2012
// Atualiza��o: 12 Mar 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Usando a classe Animation para animar um personagem
//
**********************************************************************************/
#pragma once
#ifndef _STAGE1_H_
#define _STAGE1_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include <stack>
#include "../Engine/Audio.h"
#include "../Engine/Font.h"
#include "../Engine/Game.h"
#include "../Engine/Sprite.h"
#include "../Engine/Scene.h"
#include "../Engine/Timer.h"
#include "../Engine/Object.h"
#include "Building.h"
#include "Block.h"
#include "Background.h"
#include "Player.h"
#include "Scoreboard.h"
#include "Portal.h"

// ------------------------------------------------------------------------------

class Stage1 : public Game
{
private:
    Scoreboard* scoreboard = nullptr;   // placar do jogo
    Portal* portal = nullptr;           // portal do mapa atual

    Image* buildingImage = nullptr;
    Image* shadowImage = nullptr;

    Timer timer;
    Timer transitionTimer;
    
    bool timeUp = false;
    bool enemiesCleared = false;
    bool transitioning = false;

    std::list<pair<int, int>> enemyPositions;
    std::vector<uint> enemypool;

public:
    static Scene* scene;                // cena do jogo
    static Background* backg;           // plano de fundo do jogo

    void Init();                        // inicializa��o
    void Update();                      // atualiza��o
    void Draw();                        // desenho
    void Finalize();                    // finaliza��o

    void CreateWalls();
    void CreateBlocks();
    void CreatePortal();
    void CreateExtraWalls();
    void ValidateEnemyStatus();

    void CreateEnemies(uint enemyType, int ammount);
};


// ---------------------------------------------------------------------------------

#endif _STAGE1_H_