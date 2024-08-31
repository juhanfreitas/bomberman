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
    TileSet   *         playerTiles;        // folha de sprites do personagem
    Animation *         anim;               // animação do personagem
    list<Bomb*>         bombStack;

    Timer               timer;              // medidor de tempo entre quadros da animação
    float               bored_timing;       // tempo para ficar entediado

    int                 score;
    int                 lives;
    uint                bombPower;
    uint                maxBombs;
    uint                availableBombs;

    float               speed;              // velocidade do personagem

public:
    list<PlayerState>   stateBuffer;        // estado atual do personagem

    Player();                               // construtor
    ~Player();                              // destrutor

    void Update();                          // atualização do objeto
    void Draw();                            // desenho do objeto
    void OnCollision(Object* obj);
    void Reset();

    Geometry* CreateBBox();
    void CreateBomb(BombType bombType);
    void HandleBombs();
    void IncreaseScore(int points);
};

// ---------------------------------------------------------------------------------
// Função Membro Inline

inline void Player::Draw()
{ anim->Draw(x, y, Layer::FRONT); }

inline void Player::IncreaseScore(int points)
{ score += points; }

// ---------------------------------------------------------------------------------

#endif _PLAYER_H_