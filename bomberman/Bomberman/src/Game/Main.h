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

#ifndef _ANIMAWALK_H_
#define _ANIMAWALK_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "../Engine/Audio.h"
#include "../Engine/Font.h"
#include "../Engine/Game.h"
#include "../Engine/Sprite.h"
#include "../Engine/Scene.h"
#include "Background.h"
#include "Player.h"

// ------------------------------------------------------------------------------

class AnimaWalk : public Game
{
private:
    Background * backg = nullptr;       // plano de fundo do jogo
    Player * player = nullptr;          // objeto com anima��o

    bool viewBBox = false;          // visualiza as bounding box na cena
    bool viewScene = true;          // visualiza os sprites em cena

public:
    static Scene * scene;           // cena do jogo

    void Init();                    // inicializa��o
    void Update();                  // atualiza��o
    void Draw();                    // desenho
    void Finalize();                // finaliza��o
};

// ---------------------------------------------------------------------------------

#endif