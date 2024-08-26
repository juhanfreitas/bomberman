/**********************************************************************************
// Home (Arquivo de Cabeçalho)
//
// Criação:     18 Jan 2013
// Atualização: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Tela de menu do jogo PacMan
//
**********************************************************************************/

#ifndef _BOMBERMAN_HOME_H_
#define _BOMBERMAN_HOME_H_

// ------------------------------------------------------------------------------
// Inclusões

#include "../Engine/Engine.h"
#include "../Engine/Game.h"
#include "../Engine/Audio.h"
#include "../Engine/Sprite.h"
#include "../Engine/Timer.h"
#include "Resources.h"

// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------

class Home : public Game
{
private:
    Sprite * sky = nullptr;
    Sprite * title = nullptr;

    Timer timer;

    float titleYOffset = 0;

    int bgSpeed = 0;
    float yT = 0;
    float screenBorder = 0;

public:
    void Init();                    // inicialização
    void Update();                  // atualização
    void Draw();                    // desenho
    void Finalize();                // finalização
};

// -----------------------------------------------------------------------------

#endif