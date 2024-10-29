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
#include "Stage1.h"
#include "Bomberman.h"

// ------------------------------------------------------------------------------

void Home::Init()
{
    sky = new Sprite("Resources/BgTitle1.png");
    title = new Sprite("Resources/BgTitle2.png");

    bgSpeed = 3;

    titleYOffset = window->Height() - (title->Height()*2.0f);
    screenBorder = 15 * Bomberman::screenScale;

    // inicia tocando uma música 
    Bomberman::audio->Play(MUS_MENU);
    timer.Start();
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



    if (yT < screenBorder - titleYOffset || yT > titleYOffset - screenBorder) {
        bgSpeed *= -1;
    }
    
    yT += bgSpeed * gameTime;    

    // sai com pressionamento do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // avança com pressionamento do ENTER
    if (window->KeyDown(VK_RETURN) || (controllerOn && pressedStart)) {
        Bomberman::audio->Play(SE_SELECT);
        Bomberman::audio->Stop(MUS_MENU);
        Bomberman::NextLevel<Stage1>();
    }

    // verifica se a duração da musica ja passou e toca novamente
    if (timer.Elapsed(21.0f)) {
        Bomberman::audio->Play(MUS_MENU);
        timer.Reset();
    }
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
    delete sky;
    delete title;
}