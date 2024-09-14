/**********************************************************************************
// Player (Arquivo de Cabe�alho)
//
// Cria��o:     23 Ago 2013
// Atualiza��o: 14 Set 2023
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
#include "Bomb.h"
#include "Explosion.h"

using namespace std;

// ------------------------------------------------------------------------------

enum PlayerState { STILL, BORED, WALKUP, WALKDOWN, WALKLEFT, WALKRIGHT, WINNING, LOSING, DYING };

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
    TileSet* playerTiles;                   // folha de sprites do personagem
    Animation* anim;                        // anima��o do personagem
    Timer timer;                            // medidor de tempo entre quadros da anima��o
    list<Bomb*> bombStack;
    list<PlayerState> stateBuffer;
    float bored_timing;                     // tempo para ficar entediado

    // coordenadas iniciais do player no mapa
    float startX = 40;
    float startY = 48;

    int score;
    int maxBombs;
    int bombPower;
    int lives;
    int availableBombs;
    bool alive = true;
    float speed;                            // velocidade do personagem

public:

    Player();                               // construtor
    ~Player();                              // destrutor

    void Draw();                            // desenho do objeto
    void Update();                          // atualiza��o do objeto
    void OnCollision(Object* obj);

    Geometry* CreateBBox();
    void CreateBomb(BombType bombType);
    void HandleBombs();
    void IncreaseScore(int points);
    void Reset();
    void SoftReset();
    void Die();
    void Die(uint type);
    bool IsAlive() const;
};

// ---------------------------------------------------------------------------------
// Fun��o Membro Inline

inline void Player::Draw()
{
    anim->Draw(x, y, Layer::FRONT);
}

inline void Player::IncreaseScore(int points)
{
    if (score + points >= 0)
        score + points <= 999999 ? score += points : 999999;
    else score = 0;
}

inline bool Player::IsAlive() const
{
    return alive;
}

// ---------------------------------------------------------------------------------

#endif _PLAYER_H_