/**********************************************************************************
// Bomberman
//
// Criação:     14 Set 2024
// Atualização: 14 Set 2024
// Compilador:  Visual C++ 2022
//
// Descrição:   Tela de game over do Bomberman
//
**********************************************************************************/

#ifndef _BOMBERMAN_GAMEOVER_H_
#define _BOMBERMAN_GAMEOVER_H_

// ------------------------------------------------------------------------------
// Inclusões

#include "../Engine/Engine.h"
#include "../Engine/Game.h"
#include "../Engine/Sprite.h"
#include "../Engine/TileSet.h"
#include "../Engine/Animation.h"
#include "Resources.h"

// ------------------------------------------------------------------------------

class GameOver : public Game
{
private:

    enum { DEFEAT, PERSIST, SURRENDER };
    enum { LEFT, RIGHT };

    Sprite* bgImage = nullptr;

    TileSet* bombermanAsset = nullptr;
    Animation* assetAnimation = nullptr;

    TileSet* arrowAsset = nullptr;
    Animation* arrowAnimation = nullptr;

    uint choice = DEFEAT;
    uint selected = LEFT;
    float yPos;
    float xPos;
    float assetSpeed = .0f;

public:
    void Init();                    // inicialização
    void Update();                  // atualização
    void Draw();                    // desenho
    void Finalize();                // finalização
};

// -----------------------------------------------------------------------------

#endif