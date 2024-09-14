/**********************************************************************************
// Player (Arquivo de Cabeçalho)
//
// Criação:     23 Ago 2013
// Atualização: 14 Set 2023
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
    Animation* anim;                        // animação do personagem
    Timer timer;                            // medidor de tempo entre quadros da animação
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
    void Update();                          // atualização do objeto
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
// Função Membro Inline

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