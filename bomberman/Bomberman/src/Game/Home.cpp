/**********************************************************************************
// Bomberman
//
// Cria��o:     25 Ago 2024
// Atualiza��o: 25 Ago 2024
// Compilador:  Visual C++ 2022
//
// Descri��o:   Tela de menu do Bomberman
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

    titleYOffset = window->Height() - (title->Height() * Bomberman::screenScale);
    screenBorder = 15 * Bomberman::screenScale;

    // inicia tocando uma m�sica 
    Bomberman::audio->Play(MUS_MENU, true);
    Bomberman::audio->Volume(MUS_MENU, Bomberman::MUSVolume);
}

// ------------------------------------------------------------------------------

void Home::Update()
{

    // anima o t�tulo
    if (yT < screenBorder - titleYOffset || yT > titleYOffset - screenBorder) {
        bgSpeed *= -1;
    }
    
    yT += bgSpeed * gameTime;    

    // sai com pressionamento do ESC
    if (window->KeyPress(VK_ESCAPE))
        window->Close();

    // avan�a com pressionamento do ENTER
    if (window->KeyPress(VK_RETURN)) {
        Bomberman::audio->Play(SE_SELECT);
        Bomberman::audio->Stop(MUS_MENU);
        Bomberman::NextLevel<Stage1>();
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