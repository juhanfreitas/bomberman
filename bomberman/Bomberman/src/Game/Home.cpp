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
#include <math.h>

#include "Home.h"
#include "Intro.h"
#include "Stage1.h"
#include "Bomberman.h"

// ------------------------------------------------------------------------------

void Home::Init()
{
    sky = new Sprite("Resources/Sprites/title/BgTitle1.png");
    title = new Sprite("Resources/Sprites/title/BgTitle2.png");

    timer.Start();

    bgSpeed = 4;

    titleYOffset = window->Height() - (title->Height() * Bomberman::screenScale);
    screenBorder = 15 * Bomberman::screenScale;

    // inicia tocando uma música 
    Bomberman::audioManager->Play(MUS_TITLE, true);
    Bomberman::audioManager->Volume(MUS_TITLE, Bomberman::MUSVolume);
}

// ------------------------------------------------------------------------------

void Home::Update()
{
    bool controllerOn = Bomberman::ctrlActive;
    bool pressedStart;
    if (controllerOn)
    {
        Bomberman::gamepad->XboxUpdateState();
        pressedStart = Bomberman::gamepad->XboxButton(ButtonStart);
    }



    // anima o título
    yT = sin(timer.Elapsed() * 1.0f) * bgSpeed;

    // sai com pressionamento do ESC
    if (window->KeyPress(VK_ESCAPE))
        window->Close();


    // avança com pressionamento do ENTER
    if (window->KeyPress(VK_RETURN) || (controllerOn && pressedStart)) {
        Bomberman::audioManager->FadeOut(MUS_TITLE, 2.5f);
        Bomberman::audioManager->Play(SE_SELECT);
        Bomberman::audioManager->Volume(SE_SELECT, Bomberman::SEVolume);
        readyForNextLevel = true;
    }

    if (!Bomberman::audioManager->Playing(SE_SELECT) && readyForNextLevel)
        Bomberman::NextLevel<Stage1>();
}

// ------------------------------------------------------------------------------

void Home::Draw()
{
    sky->Draw(
        window->CenterX() / Bomberman::screenScale,
        window->CenterY() / Bomberman::screenScale
    );
    title->Draw(
        window->CenterX() / Bomberman::screenScale,
        window->CenterY() / Bomberman::screenScale + yT
    );
}

// ------------------------------------------------------------------------------

void Home::Finalize()
{
    Bomberman::audioManager->Stop(MUS_TITLE);
    delete sky;
    delete title;
}