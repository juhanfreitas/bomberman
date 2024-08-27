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

#include <stack>
#include "../Engine/Types.h"                      // tipos espec�ficos da engine
#include "../Engine/Object.h"                     // interface de Object
#include "../Engine/Animation.h"                  // anima��o de sprites
#include "../Engine/Timer.h"                      // anima��o de sprites
#include "../Engine/Scene.h"
#include "Stage1.h"
#include "Bomb.h"
#include "Explosion.h"

using namespace std;

// ------------------------------------------------------------------------------

enum PlayerState { STILL, BORED, WALKUP, WALKDOWN, WALKLEFT, WALKRIGHT, WINNING, DYING };

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
    TileSet   * playerTiles;                // folha de sprites do personagem
    Animation * anim;                       // anima��o do personagem
    Timer timer;                            // medidor de tempo entre quadros da anima��o
    stack<Bomb*> bombStack;
    stack<Explosion*> explosionStack;
    float       bored_timing;               // tempo para ficar entediado

    uint startX, startY;

    uint score;
    uint maxBombs;
    uint bombPower;
    uint lives;
    uint availableBombs;
    float       speed;                      // velocidade do personagem

public:
    uint state;                             // estado atual do personagem
    uint lastState;

    Player();                               // construtor
    ~Player();                              // destrutor

    void Draw();                            // desenho do objeto
    void Update();                          // atualiza��o do objeto
    void OnCollision(Object* obj);

    Geometry* CreateBBox();
    void CreateBomb(BombType bombType);
    void HandleBombs();
    void HandleExplosions();
    void IncreaseScore(int points);
};

// ---------------------------------------------------------------------------------
// Fun��o Membro Inline

inline void Player::Draw()
{ anim->Draw(x, y, z); }

inline void Player::IncreaseScore(int points)
{ score += points; }

// ---------------------------------------------------------------------------------

#endif _PLAYER_H_