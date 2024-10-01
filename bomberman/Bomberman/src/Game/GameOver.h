/**********************************************************************************
// Bomberman
//
// Cria��o:     14 Set 2024
// Atualiza��o: 14 Set 2024
// Compilador:  Visual C++ 2022
//
// Descri��o:   Tela de game over do Bomberman
//
**********************************************************************************/

#ifndef _BOMBERMAN_GAMEOVER_H_
#define _BOMBERMAN_GAMEOVER_H_

// ------------------------------------------------------------------------------
// Inclus�es

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
    void Init();                    // inicializa��o
    void Update();                  // atualiza��o
    void Draw();                    // desenho
    void Finalize();                // finaliza��o
};

// -----------------------------------------------------------------------------

#endif