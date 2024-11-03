/**********************************************************************************
// AnimaWalk (Arquivo de Cabe�alho)
//
// Cria��o:     18 Abr 2012
// Atualiza��o: 12 Mar 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Usando a classe Animation para animar um personagem
//
**********************************************************************************/
#pragma once
#ifndef _BOMBERMAN_H_
#define _BOMBERMAN_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "../Engine/Font.h"
#include "../Engine/Game.h"
#include "../Engine/Controller.h"
#include "../Engine/Sprite.h"
#include "../Engine/Scene.h"
#include "../Engine/Timer.h"
#include "AudioManager.h"
#include "TilesManager.h"
#include "Background.h"
#include "Player.h"
#include "Scoreboard.h"
#include "EnemyFactory.h"

// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------

class Bomberman : public Game
{
private:
    static Game * level;
    bool gamePaused;
    Timer ctrlInitializer;
    int playerCount = 0;

public:
    static Controller* gamepad;
    static Player* player1;
    static Player* player2;
    static Player* player3;
    static Player* player4;
    static Scoreboard* scoreboard;
    static TilesManager* tiles;
    static Timer levelTime;
    static bool ctrlActive;
    static AudioManager * audioManager;
    static EnemyFactory * enemyFactory;
    static bool viewBBox;
    static bool viewScene;
    static float timeLimit;
    static float screenScale;
    static list<bool> players;
    static float xdiff;
    static float ydiff;


    void Init();                                // inicialização
    void Update();                              // atualização
    void Draw();                                // desenho
    void Finalize();                            // finalização
    void CheckControllers();                    // verifica a situação dos controles
    static bool PlayerActive(int playerNum);    // verifica se determinado Player está ativo

    template<class T>
    static void NextLevel()
    {
        level->Finalize();
        delete level;
        level = new T();
        level->Init();
    }
};


inline bool Bomberman::PlayerActive(int playerNum) 
{
    auto plrIt = players.begin();
    std::advance(plrIt, playerNum);
    return *plrIt;
}


// ---------------------------------------------------------------------------------

#endif _BOMBERMAN_H_