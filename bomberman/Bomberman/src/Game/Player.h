/**********************************************************************************
// Player (Arquivo de Cabeçalho)
//
// Criação:     27 Jan 2013
// Atualização: 12 Mar 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Objeto animado
//
**********************************************************************************/

#ifndef _ANIMAWALK_PLAYER_H_
#define _ANIMAWALK_PLAYER_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "../Engine/Types.h"                      // tipos específicos da engine
#include "../Engine/Object.h"                     // interface de Object
#include "../Engine/Animation.h"                  // animação de sprites

// ------------------------------------------------------------------------------

enum PlayerState { STILL, WALKUP, WALKDOWN, WALKLEFT, WALKRIGHT };

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
    TileSet   * walking;                // folha de sprites do personagem
    Animation * anim;                   // animação do personagem
    float       speed;                  // velocidade do personagem

public:
    uint state;                         // estado atual do personagem

    Player();                             // construtor
    ~Player();                            // destrutor

    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------
// Função Membro Inline

inline void Player::Draw()
{ anim->Draw(x, y, z); }

// ---------------------------------------------------------------------------------

#endif