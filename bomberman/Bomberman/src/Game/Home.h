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

enum HomeSounds { MENUMUSIC };

// ------------------------------------------------------------------------------

class Home : public Game
{
private:
    Audio * audio = nullptr;    // sistema de áudio
    Sprite * sky = nullptr;
    Sprite * title = nullptr;

    Timer timer;

    int titleYOffset;

    int bgSpeed;
    float yT;

public:
    void Init();                    // inicialização
    void Update();                  // atualização
    void Draw();                    // desenho
    void Finalize();                // finalização
};

// -----------------------------------------------------------------------------

#endif