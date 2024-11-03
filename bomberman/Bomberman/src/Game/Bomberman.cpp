/**********************************************************************************
// Game (C�digo Fonte)
//
// Cria��o:     20 Ago 2024
// Atualiza��o: 20 Ago 2024
// Compilador:  Visual C++ 2022
//
// Descri��o:   Usando a classe Animation para animar um personagem
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
Scoreboard*     Bomberman::scoreboard = nullptr;
AudioManager*   Bomberman::audioManager = nullptr;
EnemyFactory*   Bomberman::enemyFactory = nullptr;
Timer           Bomberman::levelTime = Timer();
float           Bomberman::timeLimit = 0;
float           Bomberman::screenScale = 2.0f;
float           Bomberman::xdiff = 0;
float           Bomberman::ydiff = 0;
float           Bomberman::MUSVolume = 0.8f;
float           Bomberman::SEVolume = 0.8f;
bool            Bomberman::viewBBox = false;
bool            Bomberman::viewScene = true;
bool            Bomberman::ctrlActive = false;
list<bool>      Bomberman::players = {false, false, false, false};

// -----------------------------------------------------------------------------

void Bomberman::Init()
{
    audioManager = new AudioManager();
    gamePaused = false;

    viewBBox = false;

    timeLimit = 600.0f;

    player1 = new Player(playerCount++);
    scoreboard = new Scoreboard();
    tiles = new TilesManager();
    gamepad = new Controller();
    enemyFactory = new EnemyFactory();

    CheckControllers();
    ctrlInitializer = Timer();
    ctrlInitializer.Start();

    level = new Intro();
    level->Init();
}

// ------------------------------------------------------------------------------

void Bomberman::Update()
{
    if (window->KeyPress(VK_F1))
        viewBBox = !viewBBox;

    if (window->KeyPress(VK_F2))
        viewScene = !viewScene;
    
    if (window->KeyPress(VK_PRIOR)) {
        if (screenScale < 5.0f) {
            screenScale += 1.0f;
            window->Size(272 * screenScale, 240 * screenScale);
        }
    }
    if (window->KeyPress(VK_NEXT)) {
        if (screenScale > 1.0f){
            screenScale -= 1.0f;
            window->Size(272 * screenScale, 240 * screenScale);
        }
    }

    audioManager->HandleAudio();

    if (ctrlInitializer.Elapsed() >= 2.5f)
    {
        CheckControllers();
        ctrlInitializer.Reset();
    }
    

    if (window->KeyPress('P'))
        gamePaused = !gamePaused;
    
    if (gamePaused) 
    {
        levelTime.Stop();
        level->OnPause();
    }
    else 
    {
        levelTime.Stop();
        levelTime.Start();
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
    delete audioManager;
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
    engine->window->Size(272 * Bomberman::screenScale, 240 * Bomberman::screenScale);
    engine->window->Color(0, 0, 0);
    engine->window->Title("Bomberman");
    engine->window->Icon(IDI_ICON);
    //engine->window->Cursor(IDC_CURSOR);
    //engine->graphics->VSync(true);

    // inicia o jogo
    engine->Start(new Bomberman());

    // destr�i engine e jogo
    delete engine;
}

// ----------------------------------------------------------------------------

