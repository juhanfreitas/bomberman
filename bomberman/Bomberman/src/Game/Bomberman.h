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
#include "../Engine/Sprite.h"
#include "../Engine/Scene.h"
#include "../Engine/Timer.h"
#include "Background.h"
#include "Player.h"
#include "Scoreboard.h"

// ------------------------------------------------------------------------------

enum Sounds { VO_INTRO, MUS_MENU, SE_SELECT, MUS_STAGE1, SE_TIMER };
//enum ObjTypes { 
//    PLAYER,
//    BOMB,
//    BUILDING,
//    BLOCK,
//    EXPLOSION,
//    PORTAL,
//    POWERUPS,
//    ENEMY
//};

// ------------------------------------------------------------------------------

class Bomberman : public Game
{
private:
    static Game * level;
    bool paused;

public:
    static Player * player;
    static Audio * audio;
    static Scoreboard * scoreboard;
    static bool viewBBox;
    static float timeLimit;
    static float screenScale;


    void Init();                        // inicializa��o
    void Update();                      // atualiza��o
    void Draw();                        // desenho
    void Finalize();                    // finaliza��o

    template<class T>
    static void NextLevel()
    {
        level->Finalize();
        delete level;
        level = new T();
        level->Init();
    }
};

// ---------------------------------------------------------------------------------

#endif _BOMBERMAN_H_