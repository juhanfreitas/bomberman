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


Scene* Bomberman::scene = nullptr;

// -----------------------------------------------------------------------------

void Bomberman::Init()
{
    scene = new Scene();

    //backg = new Sprite("Resources/BgStage.png");
    backg = new Background();
    player = new Player();

    scene->Add(backg, STATIC);
    scene->Add(player, MOVING);
}

// ------------------------------------------------------------------------------

void Bomberman::Update()
{
    // sai com o pressionar do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    if (window->KeyPress(VK_F1))
        viewBBox = !viewBBox;

    if (window->KeyPress(VK_F2))
        viewScene = !viewScene;

    // atualiza a cena do jogo;
    scene->Update();

    // detecta as colisões na cena
    //scene->CollisionDetection();

}

// ------------------------------------------------------------------------------

void Bomberman::Draw()
{
    //backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK, 2.0f);

    if (Bomberman::viewScene)
        scene->Draw();
    if (Bomberman::viewBBox)
        scene->DrawBBox();

}

// ------------------------------------------------------------------------------

void Bomberman::Finalize()
{
    delete scene;
    //delete backg;
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
    engine->window->Size(544, 416);
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

