#include "../Engine/Engine.h"
#include "Resources.h"
#include "Player.h"
#include "Bomberman.h"
#include "Home.h"
#include "Stage1.h"


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
    Bomberman::scoreboard->UpdateBombs(2);
    Bomberman::scoreboard->UpdatePower(2);
    Bomberman::scoreboard->UpdateLives(3);

    // sai com o pressionar do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    if (window->KeyPress(VK_F1))
        viewBBox = !viewBBox;

    if (window->KeyPress(VK_F2))
        viewScene = !viewScene;

    if (window->KeyPress(VK_F3))
        Bomberman::NextLevel<Home>();

    // toca um sinal de aviso quando o tempo está acabando
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

    // detecta as colisões na cena
    //scene->CollisionDetection();

}

// ------------------------------------------------------------------------------

void Stage1::Draw()
{
    //backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK, 2.0f);

    if (Stage1::viewScene)
        scene->Draw();
    if (Stage1::viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Stage1::Finalize()
{
    delete scene;
    //delete backg;
}