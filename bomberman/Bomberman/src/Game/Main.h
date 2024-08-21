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

#ifndef _ANIMAWALK_H_
#define _ANIMAWALK_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "../Engine/Game.h"
#include "../Engine/Sprite.h"
#include "Player.h"

// ------------------------------------------------------------------------------

class AnimaWalk : public Game
{
private:
    Sprite * backg = nullptr;       // sprite de fundo
    Player * player = nullptr;          // objeto com animação    

public:
    void Init();                    // inicialização
    void Update();                  // atualização
    void Draw();                    // desenho
    void Finalize();                // finalização
};

// ---------------------------------------------------------------------------------

#endif