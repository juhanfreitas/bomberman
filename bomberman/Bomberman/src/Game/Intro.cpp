/**********************************************************************************
// Bomberman
//
// Criação:     25 Ago 2024
// Atualização: 25 Ago 2024
// Compilador:  Visual C++ 2022
//
// Descrição:   Tela de abertura do Bomberman
//
**********************************************************************************/

// ------------------------------------------------------------------------------

#include "Intro.h"
#include "Home.h"

// ------------------------------------------------------------------------------

void Intro::Init()
{
    audio = new Audio();

    bgImage = new Sprite("Resources/HudsonGroup.png");

    audio->Add(INTRO, "Resources/Sounds/Voices/By Hudson.wav");

    // inicia tocando uma música 
    audio->Play(INTRO);
}

// ------------------------------------------------------------------------------

void Intro::Update()
{

    // sai com pressionamento do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    else if (window->KeyDown(VK_RETURN))
        Engine::Next<Home>();
}

// ------------------------------------------------------------------------------

void Intro::Draw()
{
    bgImage->Draw(window->CenterX(), window->CenterY(), Layer::BACK, 2.0f);
}

// ------------------------------------------------------------------------------

void Intro::Finalize()
{
    delete audio;
    delete bgImage;
}