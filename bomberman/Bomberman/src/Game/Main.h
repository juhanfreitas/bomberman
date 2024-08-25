/**********************************************************************************
// Bomber Man (Arquivo de Cabe�alho)
//
// Cria��o:     18 Abr 2012
// Atualiza��o: 12 Mar 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Usando a classe Animation para animar um personagem
//
**********************************************************************************/

#ifndef _BOMBERMAN_H_
#define _BOMBERMAN_H_

// ---------------------------------------------------------------------------------
// Inclus�es


#include "../Engine/Audio.h"
#include "../Engine/Font.h"
#include "../Engine/Game.h"
#include "../Engine/Sprite.h"
#include "Player.h"

// ------------------------------------------------------------------------------

class Bomberman : public Game
{
private:
    Sprite * backg = nullptr;       // sprite de fundo
    Player * player = nullptr;          // objeto com anima��o

public:
    void Init();                    // inicializa��o
    void Update();                  // atualiza��o
    void Draw();                    // desenho
    void Finalize();                // finaliza��o
};

// ---------------------------------------------------------------------------------

#endif