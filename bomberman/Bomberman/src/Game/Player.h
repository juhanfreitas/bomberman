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
#include "../Engine/Random.h"
#include "Explosion.h"
#include "Bomb.h"

using namespace std;

// ------------------------------------------------------------------------------

//enum PlayerState { STILL, BORED, WALKUP, WALKDOWN, WALKLEFT, WALKRIGHT, WINNING, LOSING, DYING };

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
    TileSet* playerTiles;                   // folha de sprites do personagem
    Animation* anim;                        // anima��o do personagem

    Timer timer;                            // medidor de tempo entre quadros da anima��o

    list<PlayerState> stateBuffer;
    float bored_timing;                     // tempo para ficar entediado
    uint startX, startY;
    bool createBomb, createBombPrev;
    const int playerNumber;

    float bored_timing = 5.0f;              // tempo para ficar entediado
    float transparencyDuration = 2.0f;      // dura��o da invulnerabilidade
    bool conOn;
    bool crtBmb;                   bool dtnBmb;
    bool moveUp, notmoveUp;        bool moveDn, notmoveDn;
    bool moveRt, notmoveRt;        bool moveLt, notmoveLt;

    // coordenadas iniciais do player no mapa
    float startX = 40;
    float startY = 48;


public:
    list<Bomb*> bombStack;
    int score;
    int maxBombs;
    int bombPower;
    int lives;
    BombType bombType;
    uint availableBombs;
    uint score;             uint lives;
    uint maxBombs;          uint bombPower;
    bool invincible;        bool bombKick;
    bool bombPass;          bool blockPass;
    float speed;                            // velocidade do personagem
    bool alive = true;
    int availableBombs;

    // temporário até encontrar solução melhor
    Timer transparencyTimer;

    Player(int plrNum);                     // construtor
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
    void Die();
    void State(uint type);

    bool IsAlive() const;
};

// ---------------------------------------------------------------------------------
// Fun��o Membro Inline

inline void Player::Draw()
{
    Color color = { 1, 1, 1, 1 };

    // aplica uma transpar�ncia aleat�ria no player caso este esteja no timer de transpar�ncia
    if (!transparencyTimer.Elapsed(transparencyDuration)) {
        RandF alphaDist{ .5f, 0.8f };
        RandI BWDist{ 0, 1 };
        float isWhite = BWDist.Rand();
        color = { isWhite, isWhite, isWhite, alphaDist.Rand() };
    }

    anim->Draw(x, y, Layer::FRONT, scale, rotation, color);
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

inline void Player::ClearPowerUps() 
{
    bombType = NORMAL;
    maxBombs = 1;
    bombPower = 1;
    bombPass = false;
    bombKick = false;
    blockPass = false;
}

// ---------------------------------------------------------------------------------

#endif _PLAYER_H_