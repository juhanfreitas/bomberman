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
#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include <list>
#include "../Engine/Types.h"                      // tipos espec�ficos da engine
#include "../Engine/Object.h"                     // interface de Object
#include "../Engine/Animation.h"                  // anima��o de sprites
#include "../Engine/Timer.h"                      // anima��o de sprites
#include "../Engine/Scene.h"
#include "Stage1.h"
#include "Bomb.h"

// ------------------------------------------------------------------------------

enum PlayerState { STILL, BORED, WALKUP, WALKDOWN, WALKLEFT, WALKRIGHT, WINNING, DYING };

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
    TileSet   * playerTiles;                // folha de sprites do personagem
    Animation * anim;                       // anima��o do personagem
    Timer timer;                            // medidor de tempo entre quadros da anima��o
    list<Bomb> * bombs;
    float       speed;                      // velocidade do personagem
    float       bored_timing;               // tempo para ficar entediado
    uint score;

public:
    uint state;                             // estado atual do personagem
    uint lastState;

    Player();                               // construtor
    ~Player();                              // destrutor

    void Draw();                            // desenho do objeto
    void Update();                          // atualiza��o do objeto
    void CreateBBox();
    void OnCollision(Object* obj);
    void CreateBomb(BombType bombType);
};

// ---------------------------------------------------------------------------------
// Fun��o Membro Inline

inline void Player::Draw()
{anim->Draw(x, y, z);}

inline void Player::CreateBomb(BombType bombType)
{
    Bomb* bomb = new Bomb(bombType, x, y);
    bombs->push_front(*bomb);
    //Stage1::scene->Add(bomb, STATIC);
}

// ---------------------------------------------------------------------------------

#endif _PLAYER_H_