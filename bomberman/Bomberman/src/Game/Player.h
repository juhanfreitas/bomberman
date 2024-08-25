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

#ifndef _BOMBERMAN_PLAYER_H_
#define _BOMBERMAN_PLAYER_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "../Engine/Types.h"                      // tipos específicos da engine
#include "../Engine/Object.h"                     // interface de Object
#include "../Engine/Animation.h"                  // animação de sprites
#include "../Engine/Timer.h"                  // animação de sprites

// ------------------------------------------------------------------------------

enum PlayerState { STILL, BORED, WALKUP, WALKDOWN, WALKLEFT, WALKRIGHT, WINNING, DYING };

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
    TileSet   * playerTiles;                // folha de sprites do personagem
    Animation * anim;                   // animação do personagem
    Timer timer;                        // medidor de tempo entre quadros da animação
    float       speed;                  // velocidade do personagem
    float       bored_timing;           // tempo para ficar entediado

public:
    uint state;                         // estado atual do personagem

    Player();                             // construtor
    ~Player();                            // destrutor

    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto
    void CreateBBox();
};

// ---------------------------------------------------------------------------------
// Função Membro Inline

inline void Player::Draw()
{ anim->Draw(x, y, z); }

// ---------------------------------------------------------------------------------

#endif