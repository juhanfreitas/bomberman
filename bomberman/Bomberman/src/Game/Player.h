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
#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include <stack>
#include "../Engine/Types.h"                      // tipos específicos da engine
#include "../Engine/Object.h"                     // interface de Object
#include "../Engine/Animation.h"                  // animação de sprites
#include "../Engine/Timer.h"                      // animação de sprites
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
    Animation* anim;                        // animação do personagem
    Timer timer;                            // medidor de tempo entre quadros da animação
    list<PlayerState> stateBuffer;
    float       bored_timing;               // tempo para ficar entediado
    uint startX, startY;
    bool createBomb;
    bool createBombPrev;
    const int playerNumber;

public:
    list<Bomb*> bombStack;
    uint score;
    uint maxBombs;
    uint bombPower;
    uint lives;
    BombType bombType;
    Timer invcbTimer;
    bool invincible;
    bool bombKick;
    bool bombPass;
    bool blockPass;
    float speed;                            // velocidade do personagem
    uint availableBombs;

    Player(int plrNum);                     // construtor
    ~Player();                              // destrutor

    void Draw();                            // desenho do objeto
    void Update();                          // atualização do objeto
    void OnCollision(Object* obj);
    void DefaultCollision(Object* obj);

    Geometry* CreateBBox();
    Directions CollisionDirection(Object* obj);
    void CreateBomb(BombType bombType);
    void DetonateBombs();
    void IncreaseScore(int points);
    void Reset();
    void ClearPowerUps();
};

// ---------------------------------------------------------------------------------
// Função Membro Inline

inline void Player::Draw()
{anim->Draw(x, y, Layer::FRONT);}

inline void Player::IncreaseScore(int points)
{score += points;}

inline void Player::ClearPowerUps() 
{
    bombType = NORMAL;
    bombPass = false;
    bombKick = false;
    blockPass = false;   
    invincible = false;
}

// ---------------------------------------------------------------------------------

#endif _PLAYER_H_