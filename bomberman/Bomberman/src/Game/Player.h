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

#ifndef _ANIMAWALK_PLAYER_H_
#define _ANIMAWALK_PLAYER_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "../Engine/Types.h"                      // tipos espec�ficos da engine
#include "../Engine/Object.h"                     // interface de Object
#include "../Engine/Animation.h"                  // anima��o de sprites

// ------------------------------------------------------------------------------

enum PlayerState { STILL, WALKUP, WALKDOWN, WALKLEFT, WALKRIGHT };

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
    TileSet   * walking;                // folha de sprites do personagem
    Animation * anim;                   // anima��o do personagem
    float       speed;                  // velocidade do personagem

public:
    uint state;                         // estado atual do personagem

    Player();                             // construtor
    ~Player();                            // destrutor

    void Update();                      // atualiza��o do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------
// Fun��o Membro Inline

inline void Player::Draw()
{ anim->Draw(x, y, z); }

// ---------------------------------------------------------------------------------

#endif