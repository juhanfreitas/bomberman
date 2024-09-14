/**********************************************************************************
// Bomberman
//
// Cria��o:     25 Ago 2024
// Atualiza��o: 25 Ago 2024
// Compilador:  Visual C++ 2022
//
// Descri��o:   Tela de abertura do Bomberman
//
**********************************************************************************/

// ------------------------------------------------------------------------------

#include "Intro.h"
#include "Home.h"
#include "Bomberman.h"

// ------------------------------------------------------------------------------

void Intro::Init()
{
    bgImage = new Sprite("Resources/Sprites/title/HudsonGroup.png");
    timer.Start();

    // inicia tocando uma m�sica 
    Bomberman::audio->Play(VO_INTRO);
}

// ------------------------------------------------------------------------------

void Intro::Update()
{

    // sai com pressionamento do ESC
    if (window->KeyPress(VK_ESCAPE))
        window->Close();

    // avan�a ao fim do som
    if (timer.Elapsed(1))
        Bomberman::NextLevel<Home>();
}

// ------------------------------------------------------------------------------

void Intro::Draw()
{
    bgImage->Draw(
        window->CenterX() / Bomberman::screenScale,
        window->CenterY() / Bomberman::screenScale
    );
}

// ------------------------------------------------------------------------------

void Intro::Finalize()
{
    delete bgImage;
}