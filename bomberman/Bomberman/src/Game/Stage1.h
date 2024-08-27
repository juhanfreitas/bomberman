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

// ------------------------------------------------------------------------------

class Stage1 : public Game
{
private:
    Background* backg = nullptr;        // plano de fundo do jogo
    Scoreboard* scoreboard = nullptr;

    Timer timer;

    bool viewBBox = false;              // visualiza as bounding box na cena
    bool viewScene = true;              // visualiza os sprites em cena
    bool timeUp = false;

    friend class Player;

public:
    static Scene* scene;                // cena do jogo


    void Init();                        // inicialização
    void Update();                      // atualização
    void Draw();                        // desenho
    void Finalize();                    // finalização
    void CreateBoxes();
    void CreateBlocks();
};

// ---------------------------------------------------------------------------------

#endif _STAGE1_H_