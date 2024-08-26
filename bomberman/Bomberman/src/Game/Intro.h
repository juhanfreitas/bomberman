/**********************************************************************************
// Home (Arquivo de Cabe�alho)
//
// Cria��o:     18 Jan 2013
// Atualiza��o: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Tela de abertura do jogo PacMan
//
**********************************************************************************/

#ifndef _BOMBERMAN_INTRO_H_
#define _BOMBERMAN_INTRO_H_

// ------------------------------------------------------------------------------
// Inclus�es

#include "../Engine/Engine.h"
#include "../Engine/Game.h"
#include "../Engine/Audio.h"
#include "../Engine/Sprite.h"
#include "Resources.h"

// ------------------------------------------------------------------------------

enum IntroSounds { INTRO };

// ------------------------------------------------------------------------------

class Intro : public Game
{
private:
    Audio * audio = nullptr;    // sistema de �udio
    Sprite * bgImage = nullptr;

public:
    void Init();                    // inicializa��o
    void Update();                  // atualiza��o
    void Draw();                    // desenho
    void Finalize();                // finaliza��o
};

// -----------------------------------------------------------------------------

#endif