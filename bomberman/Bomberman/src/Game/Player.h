/**********************************************************************************
// Player (Arquivo de Cabe�alho)
//
// Cria��o:     27 Jan 2013
// Atualiza��o: 12 Mar 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Objeto animado
//
**********************************************************************************/

#ifndef _BOMBERMAN_PLAYER_H_
#define _BOMBERMAN_PLAYER_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "../Engine/Types.h"                      // tipos espec�ficos da engine
#include "../Engine/Object.h"                     // interface de Object
#include "../Engine/Animation.h"                  // anima��o de sprites
#include "../Engine/Timer.h"                  // anima��o de sprites

// ------------------------------------------------------------------------------

enum PlayerState { STILL, BORED, WALKUP, WALKDOWN, WALKLEFT, WALKRIGHT, WINNING, DYING };

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
    TileSet   * playerTiles;                // folha de sprites do personagem
    Animation * anim;                   // anima��o do personagem
    Timer timer;                        // medidor de tempo entre quadros da anima��o
    float       speed;                  // velocidade do personagem
    float       bored_timing;           // tempo para ficar entediado

public:
    uint state;                         // estado atual do personagem

    Player();                             // construtor
    ~Player();                            // destrutor

    void Update();                      // atualiza��o do objeto
    void Draw();                        // desenho do objeto
    void CreateBBox();
};

// ---------------------------------------------------------------------------------
// Fun��o Membro Inline

inline void Player::Draw()
{ anim->Draw(x, y, z); }

// ---------------------------------------------------------------------------------

#endif