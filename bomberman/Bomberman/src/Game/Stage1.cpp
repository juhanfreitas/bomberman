#include "../Engine/Engine.h"
#include "Resources.h"
#include "Player.h"
#include "Bomberman.h"
#include "Home.h"
#include "Stage1.h"
#include "Explosion.h"


Scene* Stage1::scene = nullptr;

// -----------------------------------------------------------------------------

void Stage1::Init()
{
    scene = new Scene();

    //backg = new Sprite("Resources/BgStage.png");
    backg = new Background();
    scoreboard = new Scoreboard();

    timer.Start();

    scene->Add(backg, STATIC);
    scene->Add(Bomberman::player, MOVING);
    scene->Add(Bomberman::scoreboard, STATIC);

    Bomberman::audio->Play(MUS_STAGE1);
}

// ------------------------------------------------------------------------------

void Stage1::Update()
{

    Bomberman::scoreboard->UpdateTimer(Bomberman::timeLimit, timer.Elapsed());

    // sai com o pressionar do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    if (window->KeyPress(VK_F1))
        viewBBox = !viewBBox;

    if (window->KeyPress(VK_F2))
        viewScene = !viewScene;

    if (window->KeyPress(VK_F3))
        Bomberman::NextLevel<Home>();

    // toca um sinal de aviso quando o tempo est� acabando
    if (timer.Elapsed(Bomberman::timeLimit))
    {
        timeUp = true;
        timer.Reset();
        Bomberman::audio->Play(SE_TIMER);
    }

    // encerra o jogo ao encerrar o tempo
    if (timer.Elapsed(2) && timeUp)
        window->Close();
        

    // atualiza a cena do jogo;
    scene->Update();

    // detecta as colis�es na cena
    scene->CollisionDetection();

}

// ------------------------------------------------------------------------------

void Stage1::Draw()
{
    
    if (viewScene)
        scene->Draw();
    // if (viewBBox)
    scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Stage1::Finalize()
{
    delete scene;
    //delete backg;
}