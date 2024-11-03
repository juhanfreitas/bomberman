/**********************************************************************************
// AnimaWalk (Arquivo de Cabeçalho)
//
// Criação:     18 Abr 2012
// Atualização: 12 Mar 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Usando a classe Animation para animar um personagem
//
**********************************************************************************/
#pragma once
#ifndef _STAGE1_H_
#define _STAGE1_H_

// ---------------------------------------------------------------------------------
// Inclusões

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
#include "MapGrid.h"

// ------------------------------------------------------------------------------

class Stage1 : public Game
{
private:
    Scoreboard* scoreboard = nullptr;   // placar do jogo
    Portal* portal = nullptr;           // portal do mapa atual
    Image* buildingImage = nullptr;
    Image* shadowImage = nullptr;

    bool viewBBox = false;              // visualiza as bounding box na cena
    bool viewScene = true;              // visualiza os sprites em cena
    bool timeUp = false;

public:
    static Scene* scene;                // cena do jogo
    static Background* backg;           // plano de fundo do jogo
    static MapGrid* bGrid;
    static Directions viewDirMove;
    static ViewPort gameview;
    static float delta;
    static float speed;
    static bool canMove;

    void Init();                        // inicialização
    void Update();                      // atualização
    void Draw();                        // desenho
    void Finalize();                    // finalização
    static void MoveView();
    void CreateWalls();
    void CreateBlocks();
    void CreatePortal();
    void CreateExtraWalls();
    void CreatePowerUp(float posX, float posY);
};


// ---------------------------------------------------------------------------------

#endif _STAGE1_H_