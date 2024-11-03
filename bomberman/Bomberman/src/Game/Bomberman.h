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

#include "../Engine/Audio.h"
#include "../Engine/Font.h"
#include "../Engine/Game.h"
#include "../Engine/Controller.h"
#include "../Engine/Sprite.h"
#include "../Engine/Scene.h"
#include "../Engine/Timer.h"
#include "TilesManager.h"
#include "Background.h"
#include "Player.h"
#include "Scoreboard.h"

// ------------------------------------------------------------------------------

enum Sounds { VO_INTRO, MUS_MENU, SE_SELECT, MUS_STAGE1, SE_TIMER };


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
    static Audio* audio;
    static Player* player1;
    static Player* player2;
    static Player* player3;
    static Player* player4;
    static Scoreboard* scoreboard;
    static TilesManager* tiles;
    static Timer levelTime;
    static bool ctrlActive;
    static bool viewBBox;
    static float timeLimit;
    static float screenScale;
    static list<bool> players;
    static float xdiff;
    static float ydiff;


    void Init();                                // inicializa��o
    void Update();                              // atualiza��o
    void Draw();                                // desenho
    void Finalize();                            // finaliza��o
    void CheckControllers();                    // verifica a situa��o dos controles
    static bool PlayerActive(int playerNum);    // verifica se determinado Player est� ativo

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