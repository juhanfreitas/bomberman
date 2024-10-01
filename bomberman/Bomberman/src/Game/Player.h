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
#include "Explosion.h"
#include "Bomb.h"

using namespace std;

// ------------------------------------------------------------------------------

//enum PlayerState { STILL, BORED, WALKUP, WALKDOWN, WALKLEFT, WALKRIGHT, WINNING, DYING };

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
    TileSet* playerTiles;                   // folha de sprites do personagem
    Animation* anim;                        // anima��o do personagem
    Timer timer;                            // medidor de tempo entre quadros da anima��o
    list<PlayerState> stateBuffer;
    float       bored_timing;               // tempo para ficar entediado
    uint startX, startY;


public:
    list<Bomb*> bombStack;
    uint score;
    uint maxBombs;
    uint bombPower;
    uint lives;
    BombType bombType;
    bool bombKick;
    bool bombPass;
    bool blockPass;
    float speed;                            // velocidade do personagem
    uint availableBombs;

    Player();                               // construtor
    ~Player();                              // destrutor

    void Draw();                            // desenho do objeto
    void Update();                          // atualiza��o do objeto
    void OnCollision(Object* obj);
    void DefaultCollision(Object* obj);

    Geometry* CreateBBox();
    void CreateBomb(BombType bombType);
    void IncreaseScore(int points);
    void DetonateBombs();
    void ClearPowerUps();
    void Reset();
    void SoftReset();
    Directions CollisionDirection(Object* obj);
};

// ---------------------------------------------------------------------------------
// Fun��o Membro Inline

inline void Player::Draw()
{
    anim->Draw(x, y, Layer::FRONT);
}

inline void Player::IncreaseScore(int points)
{
    score += points;
}

inline void Player::ClearPowerUps() 
{
    bombType = NORMAL;
    bombPass = false;
    bombKick = false;
    blockPass = false;   
}

// ---------------------------------------------------------------------------------

#endif _PLAYER_H_