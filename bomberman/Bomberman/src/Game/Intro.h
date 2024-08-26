/**********************************************************************************
// Home (Arquivo de Cabeçalho)
//
// Criação:     18 Jan 2013
// Atualização: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Tela de abertura do jogo PacMan
//
**********************************************************************************/

#ifndef _BOMBERMAN_INTRO_H_
#define _BOMBERMAN_INTRO_H_

// ------------------------------------------------------------------------------
// Inclusões

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
    Audio * audio = nullptr;    // sistema de áudio
    Sprite * bgImage = nullptr;

public:
    void Init();                    // inicialização
    void Update();                  // atualização
    void Draw();                    // desenho
    void Finalize();                // finalização
};

// -----------------------------------------------------------------------------

#endif