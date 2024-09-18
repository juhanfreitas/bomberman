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

Game*           Bomberman::level = nullptr;
Player*         Bomberman::player = nullptr;
AudioManager*   Bomberman::audioManager = nullptr;
Scoreboard*     Bomberman::scoreboard = nullptr;
float           Bomberman::timeLimit = 0;
float           Bomberman::screenScale = 2.0f;          // define a escala inicial
float           Bomberman::MUSVolume = 0.8f;
float           Bomberman::SEVolume = 0.8f;
bool            Bomberman::viewBBox = false;
bool            Bomberman::viewScene = true;

// -----------------------------------------------------------------------------

void Bomberman::Init()
{
    audioManager = new AudioManager();

    viewBBox = false;
    
    timeLimit = 180.0f;

    player = new Player();
    scoreboard = new Scoreboard();

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

    level->Update();

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

    delete player;
    delete audioManager;
    delete level;
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

    // destrói engine e jogo
    delete engine;
}

// ----------------------------------------------------------------------------

