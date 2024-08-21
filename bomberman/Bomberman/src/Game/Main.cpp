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
#include "Main.h"
#include "Resources.h"
#include "Player.h"

// -----------------------------------------------------------------------------

void AnimaWalk::Init()
{
    backg = new Sprite("Resources/Background.jpg");
    player  = new Player();
}

// ------------------------------------------------------------------------------

void AnimaWalk::Update()
{
    // sai com o pressionar do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // atualiza objeto
    player->Update();
} 

// ------------------------------------------------------------------------------

void AnimaWalk::Draw()
{
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    player->Draw();
} 

// ------------------------------------------------------------------------------

void AnimaWalk::Finalize()
{
    delete player;
    delete backg;
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, 
                     _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    // cria engine
    Engine * engine = new Engine();

    // configura a engine
    engine->window->Mode(WINDOWED);
    engine->window->Size(960, 540);
    engine->window->Color(0, 0, 0);
    engine->window->Title("AnimaWalk");
    engine->window->Icon(IDI_ICON);
    //engine->window->Cursor(IDC_CURSOR);
    //engine->graphics->VSync(true);
    
    // inicia o jogo
    engine->Start(new AnimaWalk());

    // destr�i engine e jogo
    delete engine;
}

// ----------------------------------------------------------------------------

