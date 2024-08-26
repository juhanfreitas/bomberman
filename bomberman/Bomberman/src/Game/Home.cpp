/**********************************************************************************
// Bomberman
//
// Criação:     25 Ago 2024
// Atualização: 25 Ago 2024
// Compilador:  Visual C++ 2022
//
// Descrição:   Tela de menu do Bomberman
//
**********************************************************************************/

// ------------------------------------------------------------------------------

#include "Home.h"
#include "Intro.h"

// ------------------------------------------------------------------------------

void Home::Init()
{
    audio = new Audio();

    sky = new Sprite("Resources/BgTitle1.png");
    title = new Sprite("Resources/BgTitle2.png");

    bgSpeed = 8;

    titleYOffset = window->Height() - (title->Height()*2.0f);

    audio->Add(MENUMUSIC, "Resources/Sounds/Music/Title Theme.wav");

    // inicia tocando uma música 
    audio->Play(MENUMUSIC);
    timer.Start();
}

// ------------------------------------------------------------------------------

void Home::Update()
{

    if (yT < 25 - titleYOffset || yT > titleYOffset - 25 ) {
        bgSpeed *= -1;
    }
    
    yT += bgSpeed * gameTime;    

    // sai com pressionamento do ESC
    if (window->KeyDown(VK_ESCAPE))
        Engine::Next<Intro>();

    if (timer.Elapsed(21.0f)) {
        audio->Play(MENUMUSIC);
        timer.Reset();
    }
}

// ------------------------------------------------------------------------------

void Home::Draw()
{
    sky->Draw(window->CenterX(), window->CenterY(), Layer::BACK, 2.0f);
    title->Draw(window->CenterX(), window->CenterY() + yT, Layer::FRONT, 2.0f);
}

// ------------------------------------------------------------------------------

void Home::Finalize()
{
    delete audio;
    delete sky;
    delete title;
}