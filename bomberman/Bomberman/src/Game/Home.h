/**********************************************************************************
// Home (Arquivo de Cabe�alho)
//
// Cria��o:     18 Jan 2013
// Atualiza��o: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Tela de menu do jogo PacMan
//
**********************************************************************************/

#ifndef _BOMBERMAN_HOME_H_
#define _BOMBERMAN_HOME_H_

// ------------------------------------------------------------------------------
// Inclus�es

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
    Audio * audio = nullptr;    // sistema de �udio
    Sprite * sky = nullptr;
    Sprite * title = nullptr;

    Timer timer;

    int titleYOffset;

    int bgSpeed;
    float yT;

public:
    void Init();                    // inicializa��o
    void Update();                  // atualiza��o
    void Draw();                    // desenho
    void Finalize();                // finaliza��o
};

// -----------------------------------------------------------------------------

#endif