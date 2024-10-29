/**********************************************************************************
// Game (Código Fonte)
//
// Criação:     20 Ago 2024
// Atualização: 20 Ago 2024
// Compilador:  Visual C++ 2022
//
// Descrição:   Usando a classe Animation para animar um personagem
//
**********************************************************************************/

#include "../Engine/Engine.h"
#include "Resources.h"
#include "Player.h"
#include "Bomberman.h"
#include "Intro.h"

Controller*     Bomberman::gamepad = nullptr;
TilesManager*   Bomberman::tiles = nullptr;
Game*           Bomberman::level = nullptr;
Player*         Bomberman::player1 = nullptr;
Player*         Bomberman::player2 = nullptr;
Player*         Bomberman::player3 = nullptr;
Player*         Bomberman::player4 = nullptr;
Audio*          Bomberman::audio = nullptr;
Scoreboard*     Bomberman::scoreboard = nullptr;
float           Bomberman::timeLimit = 0;
float           Bomberman::screenScale = 2.0f;
bool            Bomberman::viewBBox = false;
bool            Bomberman::ctrlActive = false;
list<bool>      Bomberman::players = {false, false, false, false};

// -----------------------------------------------------------------------------

void Bomberman::Init()
{
    audio = new Audio();
    gamePaused = false;

    audio->Add(VO_INTRO, "Resources/Sounds/Voices/By Hudson.wav");
    audio->Add(MUS_MENU, "Resources/Sounds/Music/Title Theme.wav");
    audio->Add(MUS_STAGE1, "Resources/Sounds/Music/Stage 1.wav");
    audio->Add(SE_TIMER, "Resources/Sounds/Sound Effects/Timer.wav");
    audio->Add(SE_SELECT, "Resources/Sounds/Sound Effects/Menu Select.wav");

    viewBBox = false;

    timeLimit = 180.0f;

    player1 = new Player(playerCount++);
    scoreboard = new Scoreboard();
    tiles = new TilesManager();
    gamepad = new Controller();


    CheckControllers();
    ctrlInitializer.Start();

    level = new Intro();
    level->Init();
}

// ------------------------------------------------------------------------------

void Bomberman::Update()
{
    if (ctrlInitializer.Elapsed(2.5))
    {
        CheckControllers();
        ctrlInitializer.Reset();
    }
    

    if (window->KeyPress('P'))
        gamePaused = !gamePaused;
    
    if (gamePaused) 
    {
        level->OnPause();
    }
    else 
    {
        level->Update();
    }

}

// ------------------------------------------------------------------------------

void Bomberman::Draw()
{
    level->Draw();
}

// ------------------------------------------------------------------------------

void Bomberman::Finalize()
{
    level->Finalize();

    delete player1;
    delete player2;
    delete player3;
    delete player4;
    delete gamepad;
    delete audio;
    delete level;
}

// ------------------------------------------------------------------------------


void Bomberman::CheckControllers() 
{
    bool fstCtrl;
    bool sndCtrl;
    bool trdCtrl;
    bool fthCtrl;
    ctrlActive = false;

    fstCtrl = gamepad->XboxInitialize(0);
    if (fstCtrl == false)
        return;
    sndCtrl = gamepad->XboxInitialize(1);
    trdCtrl = gamepad->XboxInitialize(2);
    fthCtrl = gamepad->XboxInitialize(3);

    auto it = players.begin();

    *it++ = fstCtrl;
    *it++ = sndCtrl;
    *it++ = trdCtrl;
    *it = fthCtrl;

    ctrlActive = (fstCtrl || sndCtrl || trdCtrl || fthCtrl);
}



// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    // cria engine
    Engine* engine = new Engine();

    // configura a engine
    engine->window->Mode(WINDOWED);
    engine->window->Size(544, 480);
    engine->window->Color(0, 0, 0);
    engine->window->Title("Bomberman");
    engine->window->Icon(IDI_ICON);
    //engine->window->Cursor(IDC_CURSOR);
    //engine->graphics->VSync(true);

    // inicia o jogo
    engine->Start(new Bomberman());

    // destrói engine e jogo
    delete engine;
}

// ----------------------------------------------------------------------------

