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
    Player * player = nullptr;          // objeto com animação

    bool viewBBox = false;          // visualiza as bounding box na cena
    bool viewScene = true;          // visualiza os sprites em cena

public:
    static Scene * scene;           // cena do jogo

    void Init();                    // inicialização
    void Update();                  // atualização
    void Draw();                    // desenho
    void Finalize();                // finalização
};

// ---------------------------------------------------------------------------------

#endif